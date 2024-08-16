/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouyahy <mbouyahy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 18:30:10 by mbouyahy          #+#    #+#             */
/*   Updated: 2023/04/09 23:12:40 by mbouyahy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	print_message(t_philosopher *philo, char *msg)
{
	pthread_mutex_lock(philo->protect_print);
	pthread_mutex_lock(philo->ended_mutex);
	if (philo->number_eat >= philo->number_of_times_each_philosopher_must_eat \
					&& philo->number_of_times_each_philosopher_must_eat != -1)
		philo->eat_ended = TRUE;
	pthread_mutex_unlock(philo->ended_mutex);
	pthread_mutex_lock(philo->handle_race);
	if (philo->died == FALSE)
		printf("%ld %d %s\n", givemetime() - philo->time, philo->philo_id, msg);
	pthread_mutex_unlock(philo->handle_race);
	pthread_mutex_unlock(philo->protect_print);
	return (TRUE);
}

int	obtain_forks(t_philosopher *philo)
{
	print_message(philo, THINK);
	pthread_mutex_lock(philo->left_fork);
	print_message(philo, TAKEFORK);
	if (philo->number_of_philosopher == 1)
		return (FALSE);
	pthread_mutex_lock(philo->right_fork);
	print_message(philo, TAKEFORK);
	return (TRUE);
}

int	reliase_forks(t_philosopher *philo)
{
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	return (TRUE);
}

void	*do_that(void *ph)
{
	t_philosopher	*philo;
	int				died;

	philo = (t_philosopher *)ph;
	died = philo->died;
	while (died != 1)
	{
		if (obtain_forks(philo) == FALSE)
			return (NULL);
		pthread_mutex_lock(philo->died_mutex);
		philo->tm_before = givemetime();
		print_message(philo, EAT);
		pthread_mutex_unlock(philo->died_mutex);
		ft_sleep(philo, philo->time_to_eat);
		reliase_forks(philo);
		pthread_mutex_lock(philo->died_mutex);
		philo->number_eat++;
		pthread_mutex_unlock(philo->died_mutex);
		print_message(philo, SLEEP);
		ft_sleep(philo, philo->time_to_sleep);
		pthread_mutex_lock(philo->handle_race);
		died = philo->died;
		pthread_mutex_unlock(philo->handle_race);
	}
	return (NULL);
}

int	main(int ac, char **av)
{
	pthread_mutex_t		*forks;
	pthread_t			*thread;
	t_philosopher		*philo;
	int					nbr_p;

	if (ac >= 5 && ac <= 6)
	{
		nbr_p = ft_atoi(av[1]);
		if (check_argv(av) == 1 || nbr_p == 0 || (av[5] && ft_atoi(av[5]) == 0))
			return (1);
		thread = (pthread_t *)malloc(sizeof(pthread_t) * nbr_p);
		philo = NULL;
		forks = create_forks(nbr_p);
		if (forks && thread)
		{
			philo = create_philosophers(av, nbr_p, forks, thread);
			if (philo)
			{
				check_died_eat(philo, nbr_p);
				ft_pthread_join(thread, nbr_p);
			}
		}
		clainning(philo, forks, thread, nbr_p);
	}
	return (0);
}
