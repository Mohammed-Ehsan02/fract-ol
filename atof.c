/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atof.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhan <mkhan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 17:26:01 by mkhan             #+#    #+#             */
/*   Updated: 2022/08/11 10:09:48 by mkhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	return (0);
}

size_t	ft_strlen(const char *s)
{
	size_t	count;

	count = 0;
	while (*s++)
		count++;
	s = s - count;
	return (count);
}

int	ft_atoi(const char *str)
{
	int				count;
	unsigned long	sum;

	count = 1;
	sum = 0;
	sum = 0;
	while (*str == ' ' || *str == '\n' || *str == '\t' || *str == '\f'
		|| *str == '\r' || *str == '\v')
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			count = -count;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		sum = sum * 10 + (*str - '0');
		str++;
		if (sum > 2147483648 && count == -1)
			return (-1);
		else if (sum > 2147483647 && count == 1)
			return (-1);
	}
	return (sum * count);
}

int	atof_split(char c)
{
	char	*s;
	int		i;

	s = malloc (sizeof(char) * 2);
	s[0] = c;
	s[1] = '\0';
	i = ft_atoi(s);
	free(s);
	if (i < 0)
		exit (1);
	return (i);
}

double	ft_atof(char *str, t_data *img)
{
	double	i;
	int		sign;
	double	j;
	int		k;

	(void)img;
	i = 0;
	j = 0;
	k = 1;
	sign = 1;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str != '.' && ft_isdigit(*str))
		i = i * 10.0 + atof_split(*str++);
	if (*str == '.')
		str++;
	while (*str != '\0' && ft_isdigit(*str))
		j = j + atof_split(*str++) / pow(10.0, k++);
	if (*str != '\0' && !ft_isdigit(*str))
		ft_error();
	return (sign * (i + j));
}
