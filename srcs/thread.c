/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpuiu <cpuiu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 11:38:34 by cpuiu             #+#    #+#             */
/*   Updated: 2024/02/19 17:46:04 by cpuiu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philos.h"

int	create_observer_thread(t_dining_table *table, pthread_mutex_t *forks)
{
	pthread_t	observer;

	if (pthread_create(&observer, NULL, monitor, table->philosophers) != 0)
		return (delete_all("ERROR Creating the Observer Thread", table, forks),
			-1);
	if (create_philosopher_threads(table, forks) != 0)
		return (pthread_cancel(observer), -1);
	if (pthread_join(observer, NULL) != 0)
		return (delete_all("ERROR Joining the Observer Thread", table, forks),
			-1);
	return (0);
}

int	create_philosopher_threads(t_dining_table *table, pthread_mutex_t *forks)
{
	int	i;

	i = 0;
	while (i < table->philosophers[0].nb_of_philo)
	{
		if (pthread_create(&table->philosophers[i].thread, NULL, routine,
				&table->philosophers[i]) != 0)
			return (delete_all("ERROR Creating Philosopher Threads", table,
					forks), -1);
		i++;
	}
	while (i < table->philosophers[0].nb_of_philo)
	{
		if (pthread_join(table->philosophers[i].thread, NULL) != 0)
			return (delete_all("ERROR Joining Philosopher Threads", table,
					forks), -1);
		i++;
	}
	return (0);
}

void	*routine(void *ptr)
{
	t_philosopher	*philos;

	philos = (t_philosopher *)ptr;
	if (philos->id % 2 == 0)
		ft_usleep(1);
	while (!dead_loop(philos))
	{
		ft_eat(philos);
		ft_sleep(philos);
		ft_think(philos);
	}
	return (NULL);
}

int	dead_loop(t_philosopher *philos)
{
	int	is_dead;

	pthread_mutex_lock(philos->death_lock);
	is_dead = *philos->done;
	pthread_mutex_unlock(philos->death_lock);
	return (is_dead);
}

void	delete_all(char *str, t_dining_table *table, pthread_mutex_t *forks)
{
	int	i;

	i = 0;
	if (str)
		ft_putendl_fd(str, 1);
	pthread_mutex_destroy(&table->write_lock);
	pthread_mutex_destroy(&table->meal_lock);
	pthread_mutex_destroy(&table->death_lock);
	while (i < table->philosophers[0].nb_of_philo)
	{
		pthread_mutex_destroy(&forks[i]);
		i++;
	}
}
