/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utiles.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouyahy <mbouyahy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 18:54:18 by mbouyahy          #+#    #+#             */
/*   Updated: 2023/04/08 19:18:27 by mbouyahy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_pthread_join(pthread_t *thread, int number_of_philosopher)
{
	int	i;

	i = 0;
	while (i < number_of_philosopher)
	{
		if (pthread_join(thread[i], NULL) != 0)
			return (1);
		i++;
	}
	return (0);
}

int	each_philosopher_ate(t_philosopher *philo, int number_of_philosopher)
{
	t_var	var;
	int		j;

	var.i = -1;
	j = -1;
	var.counter = 0;
	while (var.i++ < number_of_philosopher)
	{
		pthread_mutex_lock(philo->ended_mutex);
		if (philo[var.i].eat_ended == TRUE)
			var.counter++;
		pthread_mutex_unlock(philo->ended_mutex);
		if (var.counter >= number_of_philosopher)
		{
			while (++j < number_of_philosopher)
			{
				pthread_mutex_lock(philo->handle_race);
				philo[j].died = TRUE;
				pthread_mutex_unlock(philo->handle_race);
			}
			pthread_mutex_unlock(philo->ended_mutex);
			return (1);
		}
	}
	return (0);
}

int	died_check(t_philosopher *philo, t_philosopher *philosophers, \
					int number_of_philosopher)
{
	long	died_time;
	int		x;

	x = -1;
	if (givemetime() - philo->tm_before >= \
					philo->time_to_die)
	{
		died_time = givemetime() - philo->time;
		pthread_mutex_unlock(philo->died_mutex);
		pthread_mutex_lock(philo->protect_print);
		while (++x < number_of_philosopher)
		{
			pthread_mutex_lock(philo->handle_race);
			philosophers[x].died = TRUE;
			pthread_mutex_unlock(philo->handle_race);
		}
		printf("%ld %d died\n", died_time, philo->philo_id);
		pthread_mutex_unlock(philo->protect_print);
		return (TRUE);
	}
	return (FALSE);
}

int	check_died_eat(t_philosopher *philo, int number_of_philosopher)
{
	int		i;

	i = 0;
	while (1)
	{
		pthread_mutex_lock(philo->died_mutex);
		if (died_check(&philo[i], philo, number_of_philosopher) == 1)
			return (TRUE);
		else if (each_philosopher_ate(philo, number_of_philosopher) == 1)
		{
			pthread_mutex_unlock(philo->died_mutex);
			return (TRUE);
		}
		i = (i + 1) % number_of_philosopher;
		pthread_mutex_unlock(philo->died_mutex);
	}
	return (TRUE);
}
