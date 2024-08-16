/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_philosophers.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouyahy <mbouyahy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 14:49:34 by mbouyahy          #+#    #+#             */
/*   Updated: 2023/04/09 23:08:14 by mbouyahy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ft_kill(t_philosopher *philo, int counter)
{
	int	i;

	i = 0;
	while (i < counter)
	{
		kill(philo[i].pid, SIGKILL);
		i++;
	}
}

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
	if (av[5])
		philo->number_of_times_each_philosopher_must_eat = ft_atoi(av[5]);
	else
		philo->number_of_times_each_philosopher_must_eat = -1;
}

int	init_sem(t_philosopher *philo, sem_t *forks, int number_of_philosopher)
{
	int						i;
	static sem_t			*protect_print;
	static sem_t			*died_sem;
	static sem_t			*handle_race;

	i = 0;
	sem_unlink("/died_sem");
	died_sem = sem_open("/died_sem", O_CREAT | O_EXCL, 0644, 1);
	sem_unlink("/protect_sem");
	protect_print = sem_open("/protect_sem", O_CREAT | O_EXCL, 0644, 1);
	sem_unlink("/forks");
	forks = sem_open("/forks", O_CREAT | O_EXCL, 0644, number_of_philosopher);
	sem_unlink("/handle_race");
	handle_race = sem_open("/handle_race", O_CREAT | O_EXCL, 0644, 1);
	if (handle_race < 0 || forks < 0 || died_sem < 0 || protect_print < 0)
		return (1);
	while (i < number_of_philosopher)
	{
		philo[i].died_sem = died_sem;
		philo[i].protect_print = protect_print;
		philo[i].handle_race = handle_race;
		philo[i].forks = forks;
		i++;
	}
	return (0);
}

int	create_processes(t_philosopher *philo, int number_of_philosopher)
{
	int	i;
	int	pid;

	i = 0;
	while (i < number_of_philosopher)
	{
		pid = fork();
		if (pid > 0)
			philo[i].pid = pid;
		else if (pid < 0)
		{
			ft_kill(philo, i);
			exit (1);
		}
		else if (pid == 0)
		{
			if (pthread_create(&(philo[i].thread), NULL, \
						&check_died_eat, &philo[i]) != FALSE)
				exit (1);
			do_that(&philo[i]);
		}
		usleep(100);
		i++;
	}
	return (0);
}

t_philosopher	*create_philosophers(char **av, int number_of_philosopher, \
					sem_t *forks)
{
	t_philosopher			*philo;
	long					time_start;
	int						i;

	philo = (t_philosopher *)malloc(sizeof(t_philosopher) * \
				number_of_philosopher);
	if (!philo)
		return (NULL);
	if (init_sem(philo, forks, number_of_philosopher) != 0)
	{
		free(philo);
		return (NULL);
	}
	i = 0;
	time_start = givemetime();
	while (i < number_of_philosopher)
	{
		init((philo + i), av, i);
		philo[i].time = time_start;
		philo[i].tm_before = time_start;
		i++;
	}
	create_processes(philo, number_of_philosopher);
	return (philo);
}
