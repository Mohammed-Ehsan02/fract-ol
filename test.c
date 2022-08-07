/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhan <mkhan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 10:16:28 by mkhan             #+#    #+#             */
/*   Updated: 2022/07/28 16:27:05 by mkhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "./mlx/mlx.h"

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	void	*mlx;
	void	*mlx_win;
}				t_data;

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int	close(int keycode, t_data *img)
{
	if (keycode == 1)
	{
		mlx_destroy_window(img->mlx, img->mlx_win);
		exit(0);
	}
	return (0);
}

// int	render_next_frame(void *img)
// {
	
// }
int	main(void)
{
	t_data	img;

	img.mlx = mlx_init();
	img.mlx_win = mlx_new_window(img.mlx, 1920, 1080, "Hello world!");
	img.img = mlx_new_image(img.mlx, 1920, 1080);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
								&img.endian);
	int x = 300;
	int y = 300;
	while (x <= 400 && y <= 400)
	{
		my_mlx_pixel_put(&img, x, y, 0x00FF0000);
		x++;
		y++;
	}
	x = 300;
	y = 300;
	while (x >= 200 && y <= 400)
	{
		my_mlx_pixel_put(&img, x, y, 0x00FF0000);
		x--;
		y++;
	}
	x = 200;
	y = 400;
	while (x <= 400 && y <= 400)
	{
		my_mlx_pixel_put(&img, x, y, 0x00FF0000);
		x++;
		
	}
	mlx_put_image_to_window(img.mlx, img.mlx_win, img.img, 0, 0);
	mlx_hook(img.mlx_win, 2, 0, close, &img);
	// mlx_loop_hook(img.mlx, render_next_frame, &img);
	mlx_loop(img.mlx);
}