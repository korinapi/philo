/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpuiu <cpuiu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 11:54:21 by cpuiu             #+#    #+#             */
/*   Updated: 2024/02/20 11:30:17 by cpuiu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philos.h"

void	ft_think(t_philosopher *philos)
{
	if (*philos->done == 0)
		print_action("is thinking", philos, philos->id);
}

void	ft_sleep(t_philosopher *philos)
{
	if (*philos->done == 0)
		print_action("is sleeping", philos, philos->id);
	ft_usleep(philos->time_to_sleep);
}

void	ft_eat(t_philosopher *philos)
{
	pthread_mutex_lock(philos->right_fork);
	if (philos->nb_of_philo > 1)
		pthread_mutex_lock(philos->left_fork);
	else
	{
		ft_usleep(philos->time_to_die);
		pthread_mutex_unlock(philos->right_fork);
		return ;
	}
	if (*philos->done == 0)
		print_action("is eating", philos, philos->id);
	pthread_mutex_lock(philos->meal_lock);
	philos->last_meal_time = get_current_time();
	philos->meals_eaten++;
	pthread_mutex_unlock(philos->meal_lock);
	ft_usleep(philos->time_to_eat);
	philos->eating_flag = 0;
	pthread_mutex_unlock(philos->left_fork);
	pthread_mutex_unlock(philos->right_fork);
}

int	ft_usleep(size_t ms)
{
	size_t	start_time;

	start_time = get_current_time();
	while ((get_current_time() - start_time) < ms)
		usleep(500);
	return (0);
}

size_t	get_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
	{
		ft_putendl_fd("ERROR getting the time", 1);
		exit(EXIT_FAILURE);
	}
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}
