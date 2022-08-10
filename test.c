/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhan <mkhan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 10:16:28 by mkhan             #+#    #+#             */
/*   Updated: 2022/08/10 12:23:42 by mkhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "./mlx/mlx.h"

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	void	*mlx;
	void	*mlx_win;
	int 	height;
	int		width;
	int		base_color;
	int		trgb;
	int		max_iter;
	int		i;
	double	view;
	double	trans_x;
	double	trans_y;
	double	jx;
	double	jy;
	int		flag;
	double	zoom;
}				t_data;

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

static double	map(t_data *img, int x, int y)
{
	double	map;

	map = 0;
	if (x && !y)
		map = (x - (img->width >> 1)) / img->view + img->trans_x;
	else if (!x && y)
		map = (y - (img->height >> 1)) / img->view + img->trans_y;
	return (map);
}

void	plot_mandel(t_data *img)
{
	int i = 1;
	int j = 1;
	while (i < img->width)
	{
		double m = map(img, i, 0);
		j = 1;
		while (j < img->height)
		{
			double m1 = map(img, 0, j);
			double x = 0.0;
			double y = 0.0;
			int iteration = 0;
			int max_iteration = 100;
			img->trgb = 0;
			
			while (x*x + y*y <= 2*2 && iteration < max_iteration)
			{
				double xtemp = x*x - y*y + m;
				y = 2*x*y + m1;
				x = xtemp;
				iteration = iteration + 1;
			}
			img->trgb = img->base_color * (iteration / (float)(max_iteration));
			my_mlx_pixel_put(img, i, j, img->trgb);
			j++;
		}
		i++;
	}			
}

void	plot_julia(t_data *img)
{
	int i = 0;
	int j = 0;
	while (i < img->width)
	{
		double	temp1;
		double	temp2;
		double x;
		double y;
		
		j = 0;
		while (j < img->height)
		{
			if (img->jx != 0)
			{
				temp1 = 1.5 * (i - img->width / 2);
				temp2 = (0.5 * img->view * img->width);
				x = temp1 / temp2;
			}
			if (img->jy != 0)
			{
				temp1 = (j - img->height / 2);
				temp2 = (0.5 * img->view * img->height);
				y = temp1 / temp2;
			}
			int iteration = 0;
			int max_iteration = 100;
			img->trgb = 0;
			
			while (x*x + y*y < 4 && iteration < max_iteration)
			{
				double xtemp = x*x - y*y;
				y = 2*x*y + img->jy;
				x = xtemp + img->jx;
				iteration = iteration + 1;
			}
			img->trgb = img->base_color * (iteration / (float)(max_iteration));
			my_mlx_pixel_put(img, i, j, img->trgb);
			j++;
		}
		i++;
	}			
}

int	mouse(int mouse_code, int x, int y, t_data *img)
{
	(void)x;
	(void)y;
	img->trans_x = 0;
	img->trans_y = 0;
	if (mouse_code == 5)
	{
		img->view *= 1.1;
	}
	else if (mouse_code == 4)
	{
		img->view /= 1.1;
	}
	if (img->flag)
		plot_mandel(img);
	else
		plot_julia(img);
	mlx_put_image_to_window(img->mlx, img->mlx_win, img->img, 0, 0);

	return (0);
}

void	color_shift(t_data *img, int color)
{
	img->base_color = color;
}

int	move(int keycode, t_data *img)
{
	if (keycode == 53)
	{
		mlx_destroy_window(img->mlx, img->mlx_win);
		exit(0);
	}
	else if (keycode == 18)
		color_shift(img, 0x3456789a);
	else if (keycode == 19)
		color_shift(img, 0x12563478);
	if (keycode == 2 || keycode == 124)
		img->trans_x += 0.1;
	if (keycode == 0 || keycode == 123)
		img->trans_x += -0.1;
	if (keycode == 13 || keycode == 126)
		img->trans_y += -0.1; 
	if (keycode == 1 || keycode == 125)
		img->trans_y += 0.1;
	if (img->flag)
		plot_mandel(img);
	else
		plot_julia(img);
	mlx_put_image_to_window(img->mlx, img->mlx_win, img->img, 0, 0);
	return (0);
}

int	main(void)
{
	t_data	img;

	img.height = 560;
	img.width = 640;
	img.base_color = 0x12345678;
	img.trgb = 0;
	img.view = (img.height + img.width) / 6;
	img.zoom = 1.5;
	img.jx = -0.8;
	img.jy = 0.156;
	img.flag = 0;
	img.mlx = mlx_init();
	img.mlx_win = mlx_new_window(img.mlx, img.width, img.height, "Hello world!");
	img.img = mlx_new_image(img.mlx, img.width, img.height);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
								&img.endian);
	if (img.flag)
		plot_mandel(&img);
	else
		plot_julia(&img);
	mlx_put_image_to_window(img.mlx, img.mlx_win, img.img, 0, 0);
	mlx_hook(img.mlx_win, 2, 0, move, &img);
	mlx_hook(img.mlx_win, 4, 0, mouse, &img);
	mlx_loop(img.mlx);
}