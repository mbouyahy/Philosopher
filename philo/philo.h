/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouyahy <mbouyahy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 18:29:43 by mbouyahy          #+#    #+#             */
/*   Updated: 2023/04/09 22:39:54 by mbouyahy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>
# include <stdio.h>

# define EAT "is eating"
# define THINK "is thinking"
# define SLEEP "is sleeping"
# define TAKEFORK "has taken a fork"
# define TRUE 1
# define FALSE 0
# define FAILURE NULL

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
	pthread_mutex_t	*protect_print;
	pthread_mutex_t	*died_mutex;
	pthread_mutex_t	*handle_race;
	pthread_mutex_t	*ended_mutex;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*left_fork;
}	t_philosopher;

//CKECK ARGUMENTS FUNCTIONS

int				check_argv(char	**str);
int				ft_atoi(char *str);

//TIME FUNCTIONS

void			ft_sleep(t_philosopher *philo, unsigned int philo_time);
long			givemetime(void);

//CREATE PHILOSOPHERS

t_philosopher	*create_philosophers(char **av, int number_of_philosopher, \
							pthread_mutex_t *forks, pthread_t *thread);
void			init(t_philosopher *philo, char **av, int i);
void			*do_that(void *ph);

//MUTEXES FUNCTIONS :

void			clainning(t_philosopher *philo, pthread_mutex_t *forks, \
							pthread_t *thread, int number_of_philosopher);
void			create_mutexes(pthread_mutex_t *forks, \
							int number_of_philosopher);
pthread_mutex_t	*create_forks(int number_of_philosopher);

//UTILES :

int				ft_pthread_join(pthread_t *thread, int number_of_philosopher);
int				each_philosopher_ate(t_philosopher *philo, \
							int number_of_philosopher);
int				check_died_eat(t_philosopher *philo, int number_of_philosopher);

#endif