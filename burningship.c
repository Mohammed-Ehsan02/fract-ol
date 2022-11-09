/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   burningship.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhan <mkhan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 09:41:37 by mkhan             #+#    #+#             */
/*   Updated: 2022/08/28 14:20:02 by mkhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./mlx/mlx.h"
#include "fractol.h"

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

void	init_b(t_data *img, double x, double y)
{
	img->iteration = 0;
	img->max_iteration = 100;
	img->trgb = 0;
	img->xtemp = 0.0;
	x = img->m;
	y = img->m1;
	while (x * x + y * y < 4 && img->iteration < img->max_iteration)
	{
		img->xtemp = x * x - y * y + img->m;
		y = fabs(2 * x * y) + img->m1;
		x = img->xtemp;
		img->iteration = img->iteration + 1;
	}
}

void	plot_bship(t_data *img)
{
	int		i;
	int		j;
	double	k[2];
	double	pts[2];

	i = 0;
	pts[0] = 0.0;
	pts[1] = 0.0;
	k[0] = 0.0;
	k[1] = 0.0;
	while (++i < img->width)
	{
		img->m = map(img, i, 0);
		j = 0;
		while (++j < img->height)
		{
			img->m1 = map(img, 0, j);
			pts[0] = k[0] + img->trans_x;
			pts[1] = k[1] + img->trans_y;
			init_b(img, pts[0], pts[1]);
			img->trgb = img->base_color * (img->iteration
					/ (float)(img->max_iteration));
			my_mlx_pixel_put(img, i, j, img->trgb);
		}
	}			
}
