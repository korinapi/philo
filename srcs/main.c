/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpuiu <cpuiu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 12:34:43 by cpuiu             #+#    #+#             */
/*   Updated: 2024/02/19 17:26:50 by cpuiu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philos.h"

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
		create_philosopher_threads(&table, forks);
		delete_all(NULL, &table, forks);
	}
	return (0);
}
