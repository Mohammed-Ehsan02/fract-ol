/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhan <mkhan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 10:16:28 by mkhan             #+#    #+#             */
/*   Updated: 2022/08/31 14:16:12 by mkhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "./mlx/mlx.h"
#include "fractol.h"

char	*ft_strchr(const char *s, int c)
{
	char	*a;

	a = (char *) s;
	while (*a != (unsigned char) c)
	{
		if (!*a)
			return (0);
		a++;
	}
	return (a);
}

int	ft_exit(void)
{
	exit (1);
	return (0);
}

void	ft_error(void)
{
	write(1, "Wrong/Invalid arguments\n", 25);
	write(1, "For Mandelbrot set: Run -> ./fractol 1\n", 39);
	write(1, "For Julia set: Run -> ./fractol -0.8 0.156\n", 43);
	write(1, "For Extra Fractol/ Burning Ship set: Run -> ./fractol 2\n", 57);
	exit(1);
}

void	init_fractol(t_data *img, int argc, char **argv)
{
	img->height = 1000;
	img->width = 1600;
	img->base_color = 0x12345678;
	img->trgb = 0;
	img->flag = 0;
	img->mlx = mlx_init();
	img->mlx_win = mlx_new_window(img->mlx, img->width,
			img->height, "Fractol");
	img->img = mlx_new_image(img->mlx, img->width, img->height);
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel,
			&img->line_length, &img->endian);
	if (argc == 3)
	{
		img->jx = ft_atof(argv[1], img);
		img->jy = ft_atof(argv[2], img);
		img->flag = 0;
	}
	else if (argc == 2 && ft_atoi(argv[1]) == 1 && !ft_strchr(argv[1], '.'))
		img->flag = 1;
	else if (argc == 2 && ft_atoi(argv[1]) == 2 && !ft_strchr(argv[1], '.'))
		img->flag = 2;
	else
		ft_error();
}

void	plot_fractol(t_data *img)
{
	if (img->flag == 0)
	{
		img->view = 0.8;
		plot_julia(img);
	}
	else if (img->flag == 1)
	{
		img->view = (img->height + img->width) / 6;
		plot_mandel(img);
	}
	else if (img->flag == 2)
	{
		img->view = (img->height + img->width) / 6;
		plot_bship(img);
	}
}

int	main(int argc, char **argv)
{
	t_data	img;

	if (argc <= 3 && argc > 1)
	{
		init_fractol(&img, argc, argv);
		plot_fractol(&img);
		mlx_put_image_to_window(img.mlx, img.mlx_win, img.img, 0, 0);
		mlx_hook(img.mlx_win, 2, 0, move, &img);
		mlx_hook(img.mlx_win, 17, 1L << 17, ft_exit, 0);
		mlx_hook(img.mlx_win, 4, 0, mouse, &img);
		mlx_loop(img.mlx);
	}
	else
		ft_error();
	return (0);
}
