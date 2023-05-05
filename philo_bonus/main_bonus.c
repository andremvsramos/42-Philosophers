/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andvieir <andvieir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 12:16:29 by andvieir          #+#    #+#             */
/*   Updated: 2023/05/04 14:39:01 by andvieir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "phi_bonus.h"

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
