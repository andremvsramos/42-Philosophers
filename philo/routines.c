/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 09:27:36 by andvieir          #+#    #+#             */
/*   Updated: 2023/08/20 14:54:18 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "phi.h"

/**
 * @brief Simulates the actions of a philosopher.
 *
 * This function represents the simulation of a philosopher's behavior. It is executed
 * as a separate thread for each philosopher. The philosopher goes through the actions
 * of taking forks, eating, sleeping, and thinking, using the provided synchronization
 * mechanisms. The function also ensures that the simulation continues until one of the
 * conditions for ending is met (such as a philosopher having finished their meals).
 *
 * @param arg Pointer to the philosopher's data structure.
 * @return Always returns NULL, indicating the end of the simulation thread.
 */
void	*simulation(void *arg)
{
	t_phi	*philo;

	philo = (t_phi *)arg;
	if (philo->data->num_phi == 1)
	{
		mutex_lock(&philo->l_fork->lock);
		p_msg("has taken a fork\n", philo);
		mutex_unlock(&philo->l_fork->lock);
		return (NULL);
	}
	if (philo->index % 2)
		usleep(2000);
	while (1)
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

/**
 * @brief Monitors the vital conditions of philosophers and the simulation.
 *
 * This function represents a thread responsible for monitoring the vital conditions of
 * the philosophers and the simulation as a whole. It continuously checks for conditions
 * such as a philosopher's death or the completion of all meals. If any of these
 * conditions are met, the function terminates, signaling the end of the monitoring
 * thread.
 *
 * @param arg Pointer to the data structure containing simulation information.
 * @return Always returns NULL, indicating the end of the monitoring thread.
 */
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
