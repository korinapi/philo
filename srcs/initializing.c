/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpuiu <cpuiu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 13:17:08 by cpuiu             #+#    #+#             */
/*   Updated: 2024/02/20 11:48:00 by cpuiu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philos.h"

void	initialize_philosophers(t_philosopher *philos, t_dining_table *table,
		pthread_mutex_t *forks, char **argv)
{
	int	i;
	int	num_of_philosophers;

	i = 0;
	num_of_philosophers = philo_atoi(argv[ARG_NUM_PHILOSOPHERS]);
	while (i < num_of_philosophers)
	{
		philos[i].id = i + 1;
		philos[i].meals_eaten = 0;
		philos[i].eating_flag = 0;
		initialize_data(&philos[i], argv);
		philos[i].start_time = get_current_time();
		philos[i].last_meal_time = get_current_time();
		philos[i].write_lock = &table->write_lock;
		philos[i].dead_lock = &table->dead_lock;
		philos[i].meal_lock = &table->meal_lock;
		philos[i].done = &table->death_flag;
		philos[i].left_fork = &forks[i];
		philos[i].right_fork = &forks[(i + 1) % num_of_philosophers];
		i++;
	}
}

void	initialize_data(t_philosopher *philos, char **argv)
{
	philos->time_to_die = philo_atoi(argv[ARG_TIME_TO_DIE]);
	philos->time_to_eat = philo_atoi(argv[ARG_TIME_TO_EAT]);
	philos->time_to_sleep = philo_atoi(argv[ARG_TIME_TO_SLEEP]);
	philos->nb_of_philo = philo_atoi(argv[ARG_NUM_PHILOSOPHERS]);
	if (argv[5])
		philos->min_meals_to_eat = philo_atoi(argv[ARG_MIN_MEALS_TO_EAT]);
	else
		philos->min_meals_to_eat = -1;
}

void	initialize_forks(pthread_mutex_t *forks, int num_of_philos)
{
	int	i;

	i = 0;
	while (i < num_of_philos)
	{
		if (pthread_mutex_init(&forks[i], NULL) != 0)
			write(1, "Error initializing fork mutex\n", 30);
		i++;
	}
}

void	table_init(t_dining_table *table, t_philosopher *philos)
{
	table->death_flag = 0;
	table->philosophers = philos;
	if (pthread_mutex_init(&table->write_lock, NULL) != 0)
		write(1, "Error initializing write lock\n", 31);
	if (pthread_mutex_init(&table->dead_lock, NULL) != 0)
		write(1, "Error initializing death lock\n", 31);
	if (pthread_mutex_init(&table->meal_lock, NULL) != 0)
		write(1, "Error initializing meal lock\n", 30);
}
