/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   states_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 10:59:56 by andvieir          #+#    #+#             */
/*   Updated: 2023/08/20 15:09:50 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "phi_bonus.h"

/**
 * @brief Attempts to take two forks for the philosopher to start eating.
 *
 * This function represents the action of a philosopher attempting to pick up two forks, one at a time,
 * in order to start eating. It uses semaphores to ensure that forks are acquired safely and prints a
 * message to indicate that the philosopher has taken the forks.
 *
 * @param philo A pointer to the philosopher's data structure.
 * @return Always returns 0.
 */
int	take_fork(t_phi *philo)
{
	usleep(100);
	sem_wait(philo->data->fork);
	p_msg("has taken a fork\n", philo);
	usleep(100);
	sem_wait(philo->data->fork);
	p_msg("has taken a fork\n", philo);
	return (0);
}

/**
 * @brief Simulates the eating action of a philosopher.
 *
 * This function represents the eating action of a philosopher. It updates the philosopher's last meal
 * timestamp, prints an eating message, and increases the number of times the philosopher has eaten. If
 * the desired number of meals is reached, the function signals that all meals are done using a semaphore.
 *
 * @param philo A pointer to the philosopher's data structure.
 * @return Always returns 0.
 */
int	eating(t_phi *philo)
{
	sem_wait(philo->reaper);
	philo->since_lm = get_time();
	p_msg("is eating\n", philo);
	if (philo->data->n_tte != -1)
	{
		philo->n_eats++;
		if (philo->n_eats == philo->data->n_tte)
			sem_post(philo->data->meals);
	}
	sem_post(philo->reaper);
	usleep(philo->data->tte * 1000);
	sem_post(philo->data->fork);
	sem_post(philo->data->fork);
	return (0);
}

/**
 * @brief Simulates the thinking action of a philosopher.
 *
 * This function represents the thinking action of a philosopher. It prints a thinking message to indicate
 * that the philosopher is currently thinking.
 *
 * @param philo A pointer to the philosopher's data structure.
 * @return Always returns 0.
 */
int	thinking(t_phi *philo)
{
	p_msg("is thinking\n", philo);
	return (0);
}

/**
 * @brief Simulates the sleeping action of a philosopher.
 *
 * This function represents the sleeping action of a philosopher. It prints a sleeping message to indicate
 * that the philosopher is currently sleeping and introduces a delay before the philosopher wakes up.
 *
 * @param philo A pointer to the philosopher's data structure.
 * @return Always returns 0.
 */
int	sleeping(t_phi *philo)
{
	p_msg("is sleeping\n", philo);
	usleep(philo->data->tts * 1000);
	return (0);
}
