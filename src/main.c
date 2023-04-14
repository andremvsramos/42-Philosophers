/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andvieir <andvieir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 16:25:31 by andvieir          #+#    #+#             */
/*   Updated: 2023/04/14 11:42:29 by andvieir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/phi.h"

void	*simulation(void *arg)
{
	t_phi	*philo;

	philo = (t_phi *)arg;
	if (philo->index % 2)
			usleep(2000);
	while(1)
	{
		if (philo->data->one_died || philo->data->all_eaten == philo->data->num_phi)
			return (NULL);
		take_fork(philo);
		if (philo->data->one_died || philo->data->all_eaten == philo->data->num_phi)
			return (NULL);
		eating(philo);
		if (philo->data->one_died || philo->data->all_eaten == philo->data->num_phi)
			return (NULL);
		sleeping(philo);
		if (philo->data->one_died || philo->data->all_eaten == philo->data->num_phi)
			return (NULL);
		thinking(philo);
	}
	return (NULL);
}

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
			return (0);
		if (!thread_join(data))
			return (0);
		free(data->fork);
		free(data->philo);
		free(data);
	}
	return (0);
}
