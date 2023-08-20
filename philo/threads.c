/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 16:40:01 by andvieir          #+#    #+#             */
/*   Updated: 2023/08/20 14:51:09 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "phi.h"

/**
 * @brief Initializes and starts philosopher threads for the dining philosophers simulation.
 *
 * This function initializes and launches threads for the philosophers based on the
 * specified number of philosophers in the shared data structure `data`. If there's only
 * one philosopher, a single thread is created for simulation. Otherwise, threads are
 * created for each philosopher and associated with the `simulation` function.
 *
 * @param data Pointer to the shared data structure.
 * @return 1 if thread initialization is successful, 0 if an error occurs.
 */
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

/**
 * @brief Waits for philosopher threads to complete their execution.
 *
 * This function waits for all philosopher threads to finish their execution by
 * joining each thread using the shared data structure `data`. It iterates through
 * the philosophers and waits for each thread to finish using the `pthread_join`
 * function. Returns 1 if thread joining is successful, 0 if an error occurs.
 *
 * @param data Pointer to the shared data structure.
 * @return 1 if thread joining is successful, 0 if an error occurs.
 */
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
