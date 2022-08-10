/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhan <mkhan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 12:27:38 by mkhan             #+#    #+#             */
/*   Updated: 2022/08/10 15:24:06 by mkhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

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
	int		iteration;
	int		max_iteration;
	double	view;
	double	trans_x;
	double	trans_y;
	double	jx;
	double	jy;
	int		flag;
	double	zoom;
	double	m;
	double	m1;
	double	xtemp;
	double	temp1;
	double	temp2;

}				t_data;

void	plot_julia(t_data *img);
void	plot_mandel(t_data *img);
int		move(int keycode, t_data *img);
void	color_shift(t_data *img, int color);
int		mouse(int mouse_code, int x, int y, t_data *img);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
double	ft_atof(char *str, t_data *img);

#endif
