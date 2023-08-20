/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   god_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 11:56:15 by andvieir          #+#    #+#             */
/*   Updated: 2023/08/20 15:07:59 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "phi_bonus.h"

/**
 * @brief Monitors the vital signs of a philosopher.
 *
 * This function continually monitors the vital signs of a philosopher. If the philosopher's
 * time since the last meal exceeds the time-to-die (ttd), the philosopher is considered
 * deceased. It uses the reaper semaphore to ensure exclusive access to the philosopher's
 * status and timing information.
 *
 * @param arg A pointer to the philosopher's data structure.
 * @return Always returns NULL.
 */
void	*vitals(void *arg)
{
	t_phi	*philo;

	philo = (t_phi *)arg;
	while (1)
		if (deceased(philo))
			break ;
	return (NULL);
}

/**
 * @brief Checks if a philosopher has exceeded their time-to-die.
 *
 * This function checks if a philosopher has exceeded their time-to-die (ttd). If the time
 * since the last meal is greater than ttd, the philosopher is considered deceased. It uses
 * the reaper semaphore to ensure exclusive access to the philosopher's status and timing
 * information.
 *
 * @param philo A pointer to the philosopher's data structure.
 * @return 1 if the philosopher is deceased, 0 otherwise.
 */
int	deceased(t_phi *philo)
{
	sem_wait(philo->reaper);
	if ((get_time() - philo->since_lm) > philo->data->ttd)
	{
		sem_wait(philo->data->one_died);
		p_msg("died\n", philo);
		sem_post(philo->data->finish);
		sem_post(philo->reaper);
		return (1);
	}
	sem_post(philo->reaper);
	return (0);
}

/**
 * @brief Initiates monitoring of the philosophers' meal completion.
 *
 * This function creates two monitoring threads: one for checking if all philosophers have
 * completed their meals, and another for ending the simulation and terminating the
 * philosopher processes. It uses the meals and finish semaphores to control the synchronization
 * between the monitoring threads and the philosopher processes.
 *
 * @param data A pointer to the main data structure.
 */
void	check_meals(t_data *data)
{
	pthread_t	monitor;
	pthread_t	meals;

	pthread_create(&monitor, NULL, monitoring, data);
	pthread_create(&meals, NULL, meals_done, data);
	pthread_join(monitor, NULL);
	pthread_join(meals, NULL);
}

/**
 * @brief Monitors if all philosophers have completed their meals.
 *
 * This function is executed as a thread and monitors if all philosophers have completed
 * their meals. Once all philosophers have completed eating, it signals the finish semaphore
 * to terminate the philosopher processes.
 *
 * @param arg A pointer to the main data structure.
 * @return Always returns NULL.
 */
void	*monitoring(void *arg)
{
	t_data	*data;
	int		i;

	i = 0;
	data = (t_data *)arg;
	sem_wait(data->finish);
	while (i++ < data->num_phi)
		sem_post(data->meals);
	return (NULL);
}

/**
 * @brief Monitors if all philosophers have completed their meals to terminate the simulation.
 *
 * This function is executed as a thread and monitors if all philosophers have completed
 * their meals. Once all philosophers have completed eating, it signals the finish semaphore
 * to terminate the philosopher processes and sends a SIGKILL signal to each philosopher
 * process using their respective PIDs.
 *
 * @param arg A pointer to the main data structure.
 * @return Always returns NULL.
 */
void	*meals_done(void *arg)
{
	t_data	*data;
	int		i;
	int		j;

	i = 0;
	j = 0;
	data = (t_data *)arg;
	while (1)
	{
		sem_wait(data->meals);
		i++;
		if (i == data->num_phi)
		{
			sem_post(data->finish);
			while (j < data->num_phi)
				kill(data->pid[j++], SIGKILL);
			return (0);
		}
	}
}
