/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpuiu <cpuiu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 12:03:49 by cpuiu             #+#    #+#             */
/*   Updated: 2024/02/21 20:57:34 by cpuiu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philos.h"

void	*monitor(void *ptr)
{
	t_philosopher	*philos;

	philos = (t_philosopher *)ptr;
	while (true)
	{
		if (check_if_dead(philos) || check_if_all_ate(philos))
			break ;
	}
	return (ptr);
}

bool	check_if_all_ate(t_philosopher *philos)
{
	int	i;
	int	finished_eating;

	i = 0;
	finished_eating = 0;
	if (philos[0].min_meals_to_eat == -1)
		return (false);
	while (i < philos[0].nb_of_philo)
	{
		pthread_mutex_lock(philos[i].meal_lock);
		if (philos[i].meals_eaten >= philos[i].min_meals_to_eat)
			finished_eating++;
		pthread_mutex_unlock(philos[i].meal_lock);
		i++;
	}
	if (finished_eating == philos[0].nb_of_philo)
	{
		pthread_mutex_lock(philos[0].dead_lock);
		*philos->done = 1;
		pthread_mutex_unlock(philos[0].dead_lock);
		return (true);
	}
	return (false);
}

bool	check_if_dead(t_philosopher *philos)
{
	int	i;

	i = 0;
	while (i < philos->nb_of_philo)
	{
		if (philo_is_dead(&philos[i], philos[i].time_to_die))
		{
			pthread_mutex_lock(philos->dead_lock);
			*philos->done = 1;
			pthread_mutex_unlock(philos->dead_lock);
			print_action("died", philos, philos->id);
			return (true);
		}
		i++;
	}
	return (false);
}

bool	philo_is_dead(t_philosopher *philos, size_t time_to_die)
{
	pthread_mutex_lock(philos->meal_lock);
	if (get_current_time() - philos->last_meal_time >= time_to_die && philos->eating_flag == 0)
	{
		pthread_mutex_unlock(philos->meal_lock);
		return (true);
	}
	pthread_mutex_unlock(philos->meal_lock);
	return (false);
}
