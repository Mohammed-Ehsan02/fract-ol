/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhan <mkhan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 15:56:54 by mkhan             #+#    #+#             */
/*   Updated: 2022/08/31 16:01:02 by mkhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

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
