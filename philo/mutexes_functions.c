/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutexes_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouyahy <mbouyahy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 19:19:40 by mbouyahy          #+#    #+#             */
/*   Updated: 2023/04/08 18:06:10 by mbouyahy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	create_mutexes(pthread_mutex_t *forks, int number_of_philosopher)
{
	int	i;

	i = 0;
	while (i < number_of_philosopher)
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
}

pthread_mutex_t	*create_forks(int number_of_philosopher)
{
	pthread_mutex_t		*forks;
	int					i;

	forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * \
					number_of_philosopher);
	if (!forks)
		return (0);
	i = 0;
	while (i < number_of_philosopher)
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
	return (forks);
}

void	clainning(t_philosopher *philo, pthread_mutex_t *forks, \
					pthread_t *thread, int number_of_philosopher)
{
	int	i;

	if (forks)
	{
		i = 0;
		while (i < number_of_philosopher)
		{
			pthread_mutex_destroy(&forks[i]);
			i++;
		}
		free(forks);
	}
	pthread_mutex_destroy(philo[0].protect_print);
	pthread_mutex_destroy(philo[0].died_mutex);
	pthread_mutex_destroy(philo[0].handle_race);
	pthread_mutex_destroy(philo[0].ended_mutex);
	if (thread)
		free(thread);
	if (philo)
		free(philo);
}
