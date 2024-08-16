/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouyahy <mbouyahy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 18:29:43 by mbouyahy          #+#    #+#             */
/*   Updated: 2023/04/08 23:04:00 by mbouyahy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <unistd.h>
# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>
# include  <sys/wait.h>
# include <semaphore.h>
# include <signal.h>
# include <stdio.h>
# include <fcntl.h>

# define EAT "is eating"
# define THINK "is thinking"
# define SLEEP "is sleeping"
# define TAKEFORK "has taken a fork"
# define TRUE 1
# define FALSE 0

typedef struct s_var
{
	int				sign;
	long long int	nbr;
	int				i;
	int				j;
	int				counter;
}	t_var;

typedef struct s_philosopher
{
	int				number_of_times_each_philosopher_must_eat;
	int				number_of_philosopher;
	int				time_to_sleep;
	int				time_to_eat;
	int				time_to_die;
	int				number_eat;
	int				eat_ended;
	long			tm_before;
	int				philo_id;
	int				eating;
	int				ended;
	int				died;
	long			time;
	int				pid;
	sem_t			*protect_print;
	sem_t			*died_sem;
	sem_t			*handle_race;
	sem_t			*ended_sem;
	sem_t			*forks;
	pthread_t		thread;
}	t_philosopher;

//CKECK ARGUMENTS FUNCTIONS

int				check_argv(char	**str);
int				ft_atoi(char *str);

//TIME FUNCTIONS

void			ft_sleep(t_philosopher *philo, unsigned int philo_time);
long			givemetime(void);

//CREATE PHILOSOPHERS

t_philosopher	*create_philosophers(char **av, int number_of_philosopher, \
					sem_t *forks);
void			init(t_philosopher *philo, char **av, int i);
void			*do_that(void *ph);
void			ft_kill(t_philosopher *philo, int counter);

//UTILES :

void			*check_died_eat(void *ph);
void			afficher_error(char *str);
void			ft_waitpid(t_philosopher *philo, int number_of_philosopher);

#endif