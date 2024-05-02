/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpuiu <cpuiu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 11:05:40 by cpuiu             #+#    #+#             */
/*   Updated: 2024/05/02 21:37:12 by cpuiu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOS_H
# define PHILOS_H

# include "Libft/libft.h"
# include <errno.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>
# define NC "\e[0m"
# define BLACK "\e[0;30m"
# define RED "\e[0;31m"
# define GREEN "\e[0;32m"
# define YELLOW "\e[0;33m"
# define BLUE "\e[0;34m"
# define PURPLE "\e[0;35m"
# define CYAN "\e[0;36m"
# define WHITE "\e[0;37m"

# define ARG_NUM_PHILOSOPHERS 1
# define ARG_TIME_TO_DIE 2
# define ARG_TIME_TO_EAT 3
# define ARG_TIME_TO_SLEEP 4
# define ARG_MIN_MEALS_TO_EAT 5

# define MAX_NBR_OF_PHILOS 400

typedef struct s_philosopher
{
	pthread_t		thread;
	int				id;
	int				meals_eaten;
	size_t			last_meal_time;
	size_t			time_to_sleep;
	size_t			time_to_eat;
	size_t			time_to_die;
	size_t			start_time;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*write_lock;
	pthread_mutex_t	*dead_lock;
	pthread_mutex_t	*meal_lock;
	int				min_meals_to_eat;
	int				*done;
	int				eating_flag;
	int				nb_of_philo;
}					t_philosopher;

typedef struct s_dining_table
{
	t_philosopher	*philosophers;
	int				death_flag;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	write_lock;
	pthread_mutex_t	meal_lock;
}					t_dining_table;

int					errors(int argc, char **argv);
// init
void				initialize_philosophers(t_philosopher *philos,
						t_dining_table *table, pthread_mutex_t *forks,
						char **argv);
void				initialize_data(t_philosopher *philos, char **argv);
void				initialize_forks(pthread_mutex_t *forks, int num_of_philos);
void				table_init(t_dining_table *table, t_philosopher *philos);

// threads
int					create_observer_thread(t_dining_table *table,
						pthread_mutex_t *forks);
void				*routine(void *ptr);
int					dead_loop(t_philosopher *philos);

// eat think sleep

void				ft_eat(t_philosopher *philos);
void				ft_sleep(t_philosopher *philos);
void				ft_think(t_philosopher *philos);

// monitoring

void				*monitor(void *ptr);
bool				check_if_all_ate(t_philosopher *philos);
bool				check_if_dead(t_philosopher *philos);
bool				philo_is_dead(t_philosopher *philos, size_t time_to_die);

// utils

int					ft_usleep(int time);
int					get_current_time(void);
void				delete_all(char *str, t_dining_table *table,
						pthread_mutex_t *forks);

int					philo_atoi(char *str);
void				print_action(char *str, t_philosopher *philo, int id);

#endif