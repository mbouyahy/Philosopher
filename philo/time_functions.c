/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouyahy <mbouyahy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 14:45:50 by mbouyahy          #+#    #+#             */
/*   Updated: 2023/04/07 16:41:12 by mbouyahy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	int		died;

	objectif = givemetime() + (long)philo_time;
	died = 0;
	while (died != TRUE)
	{
		current = givemetime();
		if (current >= objectif)
			break ;
		usleep(80);
		pthread_mutex_lock(philo->handle_race);
		died = philo->died;
		pthread_mutex_unlock(philo->handle_race);
	}
}
