/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atof.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhan <mkhan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 17:26:01 by mkhan             #+#    #+#             */
/*   Updated: 2022/08/09 20:00:34 by mkhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.c"

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
		ft_error(img);
	return (sign * (i + j));
}