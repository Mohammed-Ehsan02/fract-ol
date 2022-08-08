/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhan <mkhan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 10:16:28 by mkhan             #+#    #+#             */
/*   Updated: 2022/08/08 16:30:22 by mkhan            ###   ########.fr       */
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
	int 	height;
	int		width;
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

	int i =  0;
	int j =  0;
	img.height = 1080;
	img.width = 1920;
	img.mlx = mlx_init();
	img.mlx_win = mlx_new_window(img.mlx, img.width, img.height, "Hello world!");
	img.img = mlx_new_image(img.mlx, img.width, img.height);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
								&img.endian);

	while (i < img.width)
	{
		double m = (i / (img.height * 1.0)) * (4.0) - 2.0;
		j = 0;
		while (j < img.height)
		{
			double m1 = (j / (img.height * 1.0)) * (4.0) - 2.0;
			double x = 0.0;
			double y = 0.0;
			int iteration = 0;
			int max_iteration = 1000;
			
			while (x*x + y*y <= 2*2 && iteration < max_iteration)
			{
				double xtemp = x*x - y*y + m;
				y = 2*x*y + m1;
				x = xtemp;
				iteration = iteration + 1;
			}
			// printf("%d %f %f %f %f\n", iteration, x, y, m, m1);
			my_mlx_pixel_put(&img, i, j, iteration);
			j++;
		}
		i++;
	}
	
	mlx_put_image_to_window(img.mlx, img.mlx_win, img.img, 0, 0);
	mlx_hook(img.mlx_win, 2, 0, close, &img);
	// mlx_loop_hook(img.mlx, render_next_frame, &img);
	mlx_loop(img.mlx);
}