/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 16:25:31 by andvieir          #+#    #+#             */
/*   Updated: 2023/08/20 14:53:42 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "phi.h"

int	main(int ac, char **av)
{
	t_data	*data;

	if (ac == 5 || ac == 6)
	{
		data = (t_data *)malloc(sizeof(t_data));
		data_init(data, ac, av);
		if ((!valid_args(av)) || !data_init(data, ac, av))
			return (0);
		fork_init(data);
		philo_init(data);
		if (!thread_init(data))
			return (clear_data(data));
		if (!create_god(data))
			return (clear_data(data));
		thread_join(data);
		clear_data(data);
		return (1);
	}
	else
		printf("Invalid number of arguments");
	return (0);
}
