/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouyahy <mbouyahy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 18:30:10 by mbouyahy          #+#    #+#             */
/*   Updated: 2023/04/09 23:11:42 by mbouyahy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	print_message(t_philosopher *philo, char *msg)
{
	sem_wait(philo->protect_print);
	printf("%ld %d %s\n", givemetime() - philo->time, philo->philo_id, msg);
	sem_post(philo->protect_print);
	return (TRUE);
}

int	obtain_forks(t_philosopher *philo)
{
	sem_wait(philo->forks);
	print_message(philo, TAKEFORK);
	sem_wait(philo->forks);
	print_message(philo, TAKEFORK);
	return (TRUE);
}

int	reliase_forks(t_philosopher *philo)
{
	sem_post(philo->forks);
	sem_post(philo->forks);
	return (TRUE);
}

void	*do_that(void *ph)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)ph;
	while (1)
	{
		print_message(philo, THINK);
		obtain_forks(philo);
		sem_wait(philo->died_sem);
		philo->tm_before = givemetime();
		print_message(philo, EAT);
		sem_post(philo->died_sem);
		ft_sleep(philo, philo->time_to_eat);
		reliase_forks(philo);
		sem_wait(philo->handle_race);
		philo->number_eat++;
		sem_post(philo->handle_race);
		print_message(philo, SLEEP);
		ft_sleep(philo, philo->time_to_sleep);
	}
	return (NULL);
}

int	main(int ac, char **av)
{
	sem_t				*forks;
	t_philosopher		*philo;
	int					number_of_philosopher;

	if (ac >= 5 && ac <= 6)
	{
		forks = NULL;
		number_of_philosopher = ft_atoi(av[1]);
		if (check_argv(av) == TRUE || number_of_philosopher == 0 || \
					(av[5] && ft_atoi(av[5]) == 0))
		{
			afficher_error("Incorrect args!\n");
			return (1);
		}
		philo = NULL;
		philo = create_philosophers(av, number_of_philosopher, forks);
		if (!philo)
		{
			afficher_error("Failed To Create Philosopher\n");
			return (1);
		}
		ft_waitpid(philo, number_of_philosopher);
	}
	return (0);
}
