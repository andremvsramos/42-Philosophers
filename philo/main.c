/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andvieir <andvieir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 16:25:31 by andvieir          #+#    #+#             */
/*   Updated: 2023/04/27 10:42:55 by andvieir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "phi.h"

void	*simulation(void *arg)
{
	t_phi	*philo;
	int		i;

	i = 0;
	philo = (t_phi *)arg;
	if (philo->index % 2)
			usleep(2000);
	while(1)
	{
		if (take_fork(philo))
			break ;
		if (eating(philo))
			break ;
		if (sleeping(philo))
			break ;
		if (thinking(philo))
			break ;
	}
	return (NULL);
}

void	m_destroy(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_phi)
	{
		pthread_mutex_destroy(&data->philo[i].reaper);
		pthread_mutex_destroy(&data->fork[i].lock);
		i++;
	}
	pthread_mutex_destroy(&data->print);
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
		m_destroy(data);
		free(data->fork);
		free(data->philo);
		free(data);
	}
	return (0);
}
