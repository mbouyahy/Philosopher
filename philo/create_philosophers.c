/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_philosophers.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouyahy <mbouyahy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 14:49:34 by mbouyahy          #+#    #+#             */
/*   Updated: 2023/04/09 23:34:53 by mbouyahy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init(t_philosopher *philo, char **av, int i)
{
	if (!av || !*av)
		return ;
	philo->philo_id = i + 1;
	philo->died = FALSE;
	philo->time_to_die = ft_atoi(av[2]);
	philo->time_to_eat = ft_atoi(av[3]);
	philo->time_to_sleep = ft_atoi(av[4]);
	philo->number_of_philosopher = ft_atoi(av[1]);
	philo->number_eat = 0;
	philo->ended = FALSE;
	philo->eat_ended = FALSE;
	philo->eating = FALSE;
	if (av[5])
		philo->number_of_times_each_philosopher_must_eat = ft_atoi(av[5]);
	else
		philo->number_of_times_each_philosopher_must_eat = -1;
}

int	init_mutexes(t_philosopher *philo, int number_of_philosopher)
{
	static pthread_mutex_t	protect_print;
	static pthread_mutex_t	died_mutex;
	static pthread_mutex_t	handle_race;
	static pthread_mutex_t	ended_mutex;
	int						i;

	if (pthread_mutex_init(&died_mutex, NULL) != 0 || \
					pthread_mutex_init(&protect_print, NULL) != 0 || \
					pthread_mutex_init(&handle_race, NULL) != 0 || \
					pthread_mutex_init(&ended_mutex, NULL) != 0)
	{
		free(philo);
		return (1);
	}
	i = 0;
	while (i < number_of_philosopher)
	{
		philo[i].died_mutex = &died_mutex;
		philo[i].handle_race = &handle_race;
		philo[i].ended_mutex = &ended_mutex;
		philo[i].protect_print = &protect_print;
		i++;
	}
	return (0);
}

int	create_threads(t_philosopher *philo, \
				pthread_t *thread, int number_of_philosopher)
{
	int	i;

	i = 0;
	while (i < number_of_philosopher)
	{
		if (pthread_create(&thread[i], NULL, &do_that, &philo[i]) != FALSE)
		{
			free(philo);
			return (1);
		}
		usleep(100);
		i++;
	}
	return (0);
}

t_philosopher	*create_philosophers(char **av, int number_of_philosopher, \
					pthread_mutex_t *forks, pthread_t *thread)
{
	t_philosopher			*philo;
	long					time_start;
	int						i;

	philo = (t_philosopher *)malloc(sizeof(t_philosopher) * \
				number_of_philosopher);
	if (!philo)
		return (NULL);
	if (init_mutexes(philo, number_of_philosopher) != 0)
		return (NULL);
	i = 0;
	time_start = givemetime();
	while (i < number_of_philosopher)
	{
		init((philo + i), av, i);
		philo[i].time = time_start;
		philo[i].tm_before = time_start;
		philo[i].left_fork = &forks[i];
		philo[i].right_fork = &forks[(i + 1) % number_of_philosopher];
		i++;
	}
	if (create_threads(philo, thread, number_of_philosopher) != 0)
		return (NULL);
	return (philo);
}
