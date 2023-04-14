/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andvieir <andvieir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 16:40:01 by andvieir          #+#    #+#             */
/*   Updated: 2023/04/14 11:43:04 by andvieir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/phi.h"

int	alleaten(t_data *data)
{
	int	i;

	i = 0;
	if (data->n_tte == -1)
		return (0);
	if (data->all_eaten == data->num_phi)
		return (1);
	return (0);
}

void	*vitals(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	while (1)
	{
		if (deceased(data))
			return (0);
		if (alleaten(data))
			return (0);
	}
	return (NULL);
}

int	thread_init(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_phi)
	{
		if (pthread_create(&data->philo[i].phi, NULL, &simulation, &data->philo[i]) != 0)
			return (error("Failed creating thread &data->philo[i].phi.\n"));
		i++;
	}
	if (pthread_create(&data->god, NULL, &vitals, data) != 0)
		return (error("Failed creating vitals monitor.\n"));
	return (1);
}

int	thread_join(t_data *data)
{
	int	i;

	i = 0;
	if (pthread_join(data->god, NULL) != 0)
		return (error("Failed closing vitals.\n"));
	while (i < data->num_phi)
	{
		if (pthread_join(data->philo[i].phi, NULL) != 0)
			return (error("Failed joining data->philo[i].phi\n"));
		i++;
	}
	i = 0;
	while (i < data->num_phi)
		pthread_mutex_destroy(&data->fork[i++].lock);
	pthread_mutex_destroy(&data->print);
	return (1);
}
