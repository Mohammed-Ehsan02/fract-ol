/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhan <mkhan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 10:16:28 by mkhan             #+#    #+#             */
/*   Updated: 2022/08/11 10:25:17 by mkhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "./mlx/mlx.h"
#include "fractol.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *) dst = color;
}

int	ft_exit(void)
{
	exit (1);
	return (0);
}

void	ft_error(void)
{
	write(1, "Wrong/Invalid arguments\n", 25);
	write(1, "For Mandelbrot set: Run -> ./fractol\n", 37);
	write(1, "For Julia set: Run -> ./fractol -0.8 0.156\n", 43);
	exit(1);
}

void	init_fractol(t_data *img, int argc, char **argv)
{
	img->height = 560;
	img->width = 640;
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
	else if (argc == 1)
	{
		img->flag = 1;
	}
}

int	main(int argc, char **argv)
{
	t_data	img;

	if (argc <= 3 && argc > 0 && argc != 2)
	{
		init_fractol(&img, argc, argv);
		if (img.flag)
		{
			img.view = (img.height + img.width) / 6;
			plot_mandel(&img);
		}
		else
		{
			img.view = 0.8;
			plot_julia(&img);
		}
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
