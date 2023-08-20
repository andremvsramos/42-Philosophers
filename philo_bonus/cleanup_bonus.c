/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 16:31:26 by andvieir          #+#    #+#             */
/*   Updated: 2023/08/20 15:06:03 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "phi_bonus.h"

/**
 * @brief Closes and unlinks the synchronization semaphores used in the dining philosophers problem.
 *
 * This function closes and unlinks the semaphores used for synchronization in the
 * dining philosophers problem. It is responsible for releasing the resources allocated
 * for the semaphores.
 *
 * @param data A pointer to the shared data structure containing the semaphores.
 */
void	free_semp(t_data *data)
{
	sem_close(data->finish);
	sem_close(data->meals);
	sem_close(data->one_died);
	sem_close(data->print);
	sem_close(data->fork);
	sem_unlink("finish");
	sem_unlink("meals");
	sem_unlink("one_died");
	sem_unlink("print");
	sem_unlink("fork");
}

/**
 * @brief Clears the allocated memory and resources used by the shared data structure.
 *
 * This function deallocates memory and resources used by the shared data structure and
 * the associated synchronization semaphores. It closes the philosopher-specific reaper
 * semaphores and unlinks them, along with the semaphores for various purposes.
 *
 * @param data A pointer to the shared data structure to be cleared.
 * @return 0 upon successful clearing of data.
 */
int	clear_data(t_data *data)
{
	int		i;
	char	*philosopher;

	i = 0;
	free_semp(data);
	while (i < data->num_phi)
	{
		philosopher = ft_itoa(data->philo[i].index);
		sem_close(data->philo[i++].reaper);
		sem_unlink(philosopher);
		free(philosopher);
	}
	free(data->philo);
	free(data->pid);
	free(data);
	return (0);
}
