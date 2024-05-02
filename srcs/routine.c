/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpuiu <cpuiu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 11:54:21 by cpuiu             #+#    #+#             */
/*   Updated: 2024/05/02 11:24:13 by cpuiu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philos.h"

void	ft_eat(t_philosopher *philos)
{
	pthread_mutex_lock(philos->right_fork);
	print_action("has taken a fork", philos, philos->id);
	pthread_mutex_lock(philos->left_fork);
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

int	ft_usleep(size_t ms)
{
	struct timespec	req;
	struct timespec	rem;

	req.tv_sec = ms / 1000;
	req.tv_nsec = (ms % 1000) * 1000000L;
	while (nanosleep(&req, &rem) && errno == EINTR)
		req = rem;
	return (0);
}

size_t	get_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
	{
		ft_putendl_fd("ERROR getting the time", 2);
		exit(EXIT_FAILURE);
	}
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}
