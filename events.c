/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhan <mkhan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 13:15:13 by mkhan             #+#    #+#             */
/*   Updated: 2022/08/28 14:49:57 by mkhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./mlx/mlx.h"
#include "fractol.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *) dst = color;
}

int	mouse(int mouse_code, int x, int y, t_data *img)
{
	(void)x;
	(void)y;
	mlx_clear_window(img->mlx, img->mlx_win);
	img->trans_x = 0;
	img->trans_y = 0;
	if (mouse_code == 5)
		img->view *= 1.1;
	else if (mouse_code == 4)
		img->view /= 1.1;
	if (img->flag == 0)
		plot_julia(img);
	else if (img->flag == 1)
		plot_mandel(img);
	else if (img->flag == 2)
		plot_bship(img);
	mlx_put_image_to_window(img->mlx, img->mlx_win, img->img, 0, 0);
	return (0);
}

void	color_shift(t_data *img, int color)
{
	img->base_color = color;
}

void	translate_frac(t_data *img, int keycode)
{
	if (keycode == 2 || keycode == 124)
		img->trans_x += 0.1;
	if (keycode == 0 || keycode == 123)
		img->trans_x += -0.1;
	if (keycode == 13 || keycode == 126)
		img->trans_y += -0.1;
	if (keycode == 1 || keycode == 125)
		img->trans_y += 0.1;
}

int	move(int keycode, t_data *img)
{
	mlx_clear_window(img->mlx, img->mlx_win);
	if (keycode == 53)
	{
		mlx_destroy_window(img->mlx, img->mlx_win);
		exit(0);
	}
	else if (keycode == 18)
		color_shift(img, 0x3456789a);
	else if (keycode == 19)
		color_shift(img, 0x12563478);
	translate_frac(img, keycode);
	if (img->flag == 0)
		plot_julia(img);
	else if (img->flag == 1)
		plot_mandel(img);
	else if (img->flag == 2)
		plot_bship(img);
	mlx_put_image_to_window(img->mlx, img->mlx_win, img->img, 0, 0);
	return (0);
}
