/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpuiu <cpuiu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 11:54:21 by cpuiu             #+#    #+#             */
/*   Updated: 2024/05/02 21:44:05 by cpuiu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philos.h"

void	ft_eat(t_philosopher *philos)
{
	pthread_mutex_lock(philos->left_fork);
	print_action("has taken a fork", philos, philos->id);
	if (philos->nb_of_philo == 1)
	{
		ft_usleep(philos->time_to_die);
		return ;
	}
	pthread_mutex_lock(philos->right_fork);
	print_action("has taken a fork", philos, philos->id);
	print_action("is eating", philos, philos->id);
	philos->eating_flag = 1;
	pthread_mutex_lock(philos->meal_lock);
	philos->last_meal_time = get_current_time();
	philos->meals_eaten++;
	pthread_mutex_unlock(philos->meal_lock);
	ft_usleep(philos->time_to_eat);
	philos->eating_flag = 0;
	pthread_mutex_unlock(philos->right_fork);
	pthread_mutex_unlock(philos->left_fork);
}

int	ft_usleep(int time)
{
	long int	start;

	start = get_current_time();
	while (get_current_time() - start < time)
		usleep(50);
	return (0);
}

int	get_current_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}
