/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_argv.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouyahy <mbouyahy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 18:51:06 by mbouyahy          #+#    #+#             */
/*   Updated: 2023/04/09 23:19:06 by mbouyahy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	ft_atoi(char *str)
{
	int	i;
	int	sign;
	int	res;

	res = 0;
	sign = 1;
	i = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
		{
			sign *= -1;
		}
		i++;
	}
	if (!(str[i] >= '0' && str[i] <= '9'))
		return (res);
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + str[i] - '0';
		i++;
	}
	return (sign * res);
}

int	plus_minus(char c, int *i)
{
	if (c == '+' || c == '-')
	{
		if (c == '-')
			return (1);
		(*i)++;
	}
	return (0);
}

void	mini_atoi(char *str, int *i, long long int *nbr)
{
	while (str[*i] >= '0' && str[*i] <= '9')
	{
		*nbr = *nbr * 10 + str[*i] - '0';
		(*i)++;
	}
}

int	short_code(char *str)
{
	t_var	var;

	var.i = 0;
	while (str[var.i])
	{
		var.nbr = 0;
		if (plus_minus(str[var.i], &var.i) == 1)
			return (1);
		if (!str[var.i] || !(str[var.i] >= '0' && str[var.i] <= '9'))
			return (1);
		else if (str[var.i])
		{
			mini_atoi(str, &var.i, &var.nbr);
			if (var.nbr > 2147483647 || var.nbr < -2147483648)
				return (1);
		}
	}
	return (0);
}

int	check_argv(char	**str)
{
	int				i;

	i = 1;
	while (str[i])
	{
		if (str[i][0] == '\0')
			return (1);
		if (short_code(str[i]) == 1)
			return (1);
		i++;
	}
	return (0);
}
