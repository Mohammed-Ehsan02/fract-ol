/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhan <mkhan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 13:27:51 by mkhan             #+#    #+#             */
/*   Updated: 2022/08/10 18:10:43 by mkhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./mlx/mlx.h"
#include "fractol.h"

void	init_j(t_data *img, double x, double y)
{
	img->iteration = 0;
	img->max_iteration = 100;
	img->trgb = 0;
	img->xtemp = 0.0;
	while (x * x + y * y < 4 && img->iteration < img->max_iteration)
	{
		img->xtemp = x * x - y * y;
		y = 2 * x * y + img->jy;
		x = img->xtemp + img->jx;
		img->iteration = img->iteration + 1;
	}
}

void	init(t_data *img, double *k, int i, int j)
{
	img->temp1 = 0.0;
	img->temp2 = 0.0;
	if (img->jx != 0)
	{
		img->temp1 = 1.5 * (i - img->width / 2);
		img->temp2 = (0.5 * img->view * img->width);
		k[0] = img->temp1 / img->temp2;
	}
	if (img->jy != 0)
	{
		img->temp1 = (j - img->height / 2);
		img->temp2 = (0.5 * img->view * img->height);
		k[1] = img->temp1 / img->temp2;
	}
}

void	plot_julia(t_data *img)
{
	int		i[2];
	double	k[2];
	double	pts[2];

	i[0] = 0;
	pts[0] = 0.0;
	pts[1] = 0.0;
	k[0] = 0.0;
	k[1] = 0.0;
	while (i[0] < img->width)
	{
		i[1] = 0;
		while (i[1] < img->height)
		{
			init(img, k, i[0], i[1]);
			pts[0] = k[0] + img->trans_x;
			pts[1] = k[1] + img->trans_y;
			init_j(img, pts[0], pts[1]);
			img->trgb = img->base_color * (img->iteration
					/ (float)(img->max_iteration));
			my_mlx_pixel_put(img, i[0], i[1], img->trgb);
			i[1]++;
		}
		i[0]++;
	}			
}
