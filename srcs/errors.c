/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpuiu <cpuiu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 12:35:49 by cpuiu             #+#    #+#             */
/*   Updated: 2024/05/02 10:27:33 by cpuiu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philos.h"

static int	check_args(int argc)
{
	if (argc == 5 || argc == 6)
		return (0);
	else
		write(2,
			"Number of arguments invalid. Please provide 4 or 5 arguments\n",
			60);
	return (1);
}

static int	check_arg_content(int argc, char **argv)
{
	int		index;
	char	*arg;

	index = 1;
	while (index < argc)
	{
		arg = argv[index];
		while (*arg == '+' && *arg)
			arg++;
		while (*arg)
		{
			if (!ft_isdigit(*arg))
			{
				write(2, "The arguments has to contain only positive numbers\n",
					52);
				return (1);
			}
			arg++;
		}
		index++;
	}
	return (0);
}

int	errors(int argc, char **argv)
{
	int	time_to_die;
	int	time_to_eat;

	time_to_die = philo_atoi(argv[ARG_TIME_TO_DIE]);
	time_to_eat = philo_atoi(argv[ARG_TIME_TO_EAT]);
	if (time_to_die < time_to_eat)
	{
		write (2, "not enough time to die\n", 24);
		return (1);
	}
	if (check_args(argc))
		return (1);
	if (check_arg_content(argc, argv))
		return (1);
	return (0);
}
