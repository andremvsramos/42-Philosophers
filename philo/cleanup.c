/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 09:29:17 by andvieir          #+#    #+#             */
/*   Updated: 2023/08/20 14:52:43 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "phi.h"

/**
 * @brief Frees memory and resources allocated for the simulation.
 *
 * This function releases the memory and resources allocated during the execution
 * of the dining philosophers simulation. It destroys mutexes associated with
 * philosophers' reapers and fork locks. The memory allocated for the `data`,
 * `fork`, and `philo` structures is also freed. The function returns 0.
 *
 * @param data Pointer to the shared data structure.
 * @return Always returns 0.
 */
int	clear_data(t_data *data)
{
	m_destroy(data);
	free(data->fork);
	free(data->philo);
	free(data);
	return (0);
}

/**
 * @brief Destroys mutexes used for synchronization and resource protection.
 *
 * This function iterates through the philosophers' data and destroys the mutexes
 * associated with their reapers and fork locks. It also destroys the mutex used
 * for synchronized printing. The function helps release the resources allocated
 * for synchronization and ensures proper cleanup after the simulation finishes.
 *
 * @param data Pointer to the shared data structure.
 */
void	m_destroy(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_phi)
	{
		mutex_destroy(&data->philo[i].reaper);
		mutex_destroy(&data->fork[i].lock);
		i++;
	}
	mutex_destroy(&data->print);
}
