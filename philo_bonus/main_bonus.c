/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 12:16:29 by andvieir          #+#    #+#             */
/*   Updated: 2023/08/20 15:07:04 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "phi_bonus.h"

/**
 * @brief Validates command-line arguments for being numeric strings.
 *
 * This function checks the validity of command-line arguments by ensuring that each argument
 * is a valid numeric string. If an argument is found to be non-numeric, it prints an error
 * message indicating the index of the invalid argument and returns 0.
 *
 * @param av An array of command-line argument strings.
 * @return 1 if all arguments are valid numeric strings, 0 otherwise.
 */
int	valid_args(char **av)
{
	int	i;
	int	j;

	i = 1;
	while (av[i])
	{
		j = 0;
		while (av[i][j])
		{
			if (!ft_isdigit(av[i][j]))
			{
				printf("av[%d] ", i);
				error("NaN\n");
				return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}

int	main(int ac, char **av)
{
	t_data	*data;
	int		i;

	i = 0;
	if (ac == 5 || ac == 6)
	{
		data = (t_data *)malloc(sizeof(t_data));
		if (!data)
			return (0);
		if (!valid_args(av) || !data_init(data, ac, av))
		{
			printf("Invalid arguments.\n");
			return (clear_data(data));
		}
		if (proc_init(data))
			return ((clear_data(data)));
		check_meals(data);
		waitpid(-1, 0, WNOHANG);
		clear_data(data);
	}
	return (0);
}
