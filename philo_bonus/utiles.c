/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utiles.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouyahy <mbouyahy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 18:54:18 by mbouyahy          #+#    #+#             */
/*   Updated: 2023/04/09 23:08:07 by mbouyahy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	afficher_error(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		write(2, &str[i], 1);
		i++;
	}
}

void	ft_waitpid(t_philosopher *philo, int number_of_philosopher)
{
	int	value;

	waitpid(-1, &value, 0);
	sem_close(philo->died_sem);
	sem_close(philo->forks);
	sem_close(philo->protect_print);
	sem_close(philo->handle_race);
	sem_unlink("/died_sem");
	sem_unlink("/protect_sem");
	sem_unlink("/handle_race");
	sem_unlink("/forks");
	ft_kill(philo, number_of_philosopher);
	if (philo)
		free(philo);
	if (value != 0)
	{
		afficher_error("ERROR\n");
		exit(1);
	}
}

int	died_check(t_philosopher *philo)
{
	long	died_time;

	if (givemetime() - philo->tm_before >= \
					philo->time_to_die)
	{
		died_time = givemetime() - philo->time;
		sem_post(philo->died_sem);
		sem_wait(philo->protect_print);
		printf("%ld %d died\n", died_time, philo->philo_id);
		return (TRUE);
	}
	return (FALSE);
}

void	*check_died_eat(void *ph)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)ph;
	while (1)
	{
		sem_wait(philo->died_sem);
		if (died_check(philo) == 1)
			exit(0);
		sem_post(philo->died_sem);
		sem_wait(philo->handle_race);
		if (philo->number_eat > \
				philo->number_of_times_each_philosopher_must_eat + 2 \
				&& philo->number_of_times_each_philosopher_must_eat != -1)
		{
			sem_wait(philo->protect_print);
			sem_post(philo->handle_race);
			exit(0);
		}
		sem_post(philo->handle_race);
	}
	exit(0);
}
