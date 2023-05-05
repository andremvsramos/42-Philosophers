/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andvieir <andvieir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 16:40:01 by andvieir          #+#    #+#             */
/*   Updated: 2023/04/28 09:21:37 by andvieir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "phi.h"

int	thread_init(t_data *data)
{
	int	i;

	i = 0;
	if (data->num_phi == 1)
		pthread_create(&data->philo[0].phi, NULL, &simulation, &data->philo[0]);
	else
	{
		while (i < data->num_phi)
		{
			if (pthread_create(&data->philo[i].phi,
					NULL, &simulation, &data->philo[i]))
				return (error("Failed creating thread &data->philo[i].phi.\n"));
			usleep(1000);
			i++;
		}
	}
	return (1);
}

int	thread_join(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_phi)
	{
		if (pthread_join(data->philo[i].phi, NULL) != 0)
			return (error("Failed joining data->philo[i].phi\n"));
		i++;
	}
	return (1);
}
