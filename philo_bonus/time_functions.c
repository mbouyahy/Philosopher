/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouyahy <mbouyahy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 14:45:50 by mbouyahy          #+#    #+#             */
/*   Updated: 2023/04/08 15:45:58 by mbouyahy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

long	givemetime(void)
{
	long			res;
	struct timeval	time_v;

	gettimeofday(&time_v, NULL);
	res = (time_v.tv_sec * 1000) + (time_v.tv_usec / 1000);
	return (res);
}

void	ft_sleep(t_philosopher *philo, unsigned int philo_time)
{
	long	current;
	long	objectif;

	objectif = givemetime() + (long)philo_time;
	while (philo->died != TRUE)
	{
		current = givemetime();
		if (current >= objectif)
			break ;
		usleep(80);
	}
}
