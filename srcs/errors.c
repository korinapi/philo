/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpuiu <cpuiu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 12:35:49 by cpuiu             #+#    #+#             */
/*   Updated: 2024/02/20 10:27:25 by cpuiu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philos.h"

static int	check_args(int argc)
{
	if (argc != 5 && argc != 6)
	{
		printf("Number of arguments invalid. Please provide 4 or 5 arguments");
		return (1);
	}
	return (0);
}

static int	check_arg_content(int argc, char **argv)
{
	int	index;
	int	i;

	index = 1;
	while (index < argc)
	{
		i = 0;
		while (argv[index][i] == '+' && argv[index][i])
			i++;
		while (argv[index][i])
		{
			if (!(ft_isdigit(argv[index][i])))
			{
				printf("The arguments has to contain only positive numbers\n");
				return (1);
			}
			i++;
		}
		index++;
	}
	return (0);
}

int	errors(int argc, char **argv)
{
	int	err;

	err = 0;
	err = check_args(argc);
	if (err != 0)
		return (1);
	if (argc == 5 || argc == 6)
		err = check_arg_content(argc, argv);
	if (err != 0)
		return (1);
	return (0);
}
