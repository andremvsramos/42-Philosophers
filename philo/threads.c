/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andvieir <andvieir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 16:40:01 by andvieir          #+#    #+#             */
/*   Updated: 2023/04/27 10:48:01 by andvieir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "phi.h"

int	alleaten(t_data *data)
{
	int	i;

	i = 0;
	if (data->n_tte == -1)
		return (0);
	while (i < data->num_phi)
	{
		if (data->philo[i].n_eats == data->n_tte && !data->philo[i].full)
		{
			data->philo[i].full = 1;
			data->all_eaten++;
		}
		i++;
	}
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
			break ;
		if (alleaten(data))
			break ;
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
		usleep(1000);
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
	//pthread_mutex_unlock(&data->print);
	/* while (i < data->num_phi)
	{
		pthread_mutex_unlock(&data->fork[i].lock);
		i++;
	}  ??????????????? */
	i = 0;
	while (i < data->num_phi)
	{
		if (pthread_join(data->philo[i].phi, NULL) != 0)
			return (error("Failed joining data->philo[i].phi\n"));
		i++;
	}
	return (1);
}
