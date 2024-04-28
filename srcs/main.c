/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpuiu <cpuiu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 12:34:43 by cpuiu             #+#    #+#             */
/*   Updated: 2024/02/21 20:57:21 by cpuiu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philos.h"

void	print_action(char *str, t_philosopher *philo, int id)
{
	time_t time;
	pthread_mutex_lock (philo->write_lock);
	time = get_current_time() - philo->start_time;
	if (!dead_loop(philo) && ft_strcmp(str, "is thinking") == 0)
		printf(BLUE"%zu %d %s\n", time, id, str);
	if (!dead_loop(philo) && ft_strcmp(str, "is sleeping") == 0)
		printf(GREEN"%zu %d %s\n", time, id, str);
	if (!dead_loop(philo) && ft_strcmp(str, "is eating") == 0)
		printf(YELLOW"%zu %d %s\n", time, id, str);
	if (!dead_loop(philo) && ft_strcmp(str, "has taken a fork") == 0)
		printf(WHITE"%zu %d %s\n", time, id, str);
	if (ft_strcmp(str, "died") == 0)
		printf(RED"%zu %d %s\n", time, id, str);
	pthread_mutex_unlock(philo->write_lock);
}

int	main(int argc, char **argv)
{
	t_dining_table	table;
	t_philosopher	philos[MAX_NBR_OF_PHILOS];
	pthread_mutex_t	forks[MAX_NBR_OF_PHILOS];
	int				err;

	err = errors(argc, argv);
	if (err == 1)
		return (0);
	else
	{
		table_init(&table, philos);
		initialize_forks(forks, philo_atoi(argv[1]));
		initialize_philosophers(philos, &table, forks, argv);
		create_observer_thread(&table, forks);
		delete_all(NULL, &table, forks);
	}
	return (0);
}
