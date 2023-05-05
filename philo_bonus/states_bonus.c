/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   states_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andvieir <andvieir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 10:59:56 by andvieir          #+#    #+#             */
/*   Updated: 2023/05/04 15:02:03 by andvieir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "phi_bonus.h"

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

int	thinking(t_phi *philo)
{
	p_msg("is thinking\n", philo);
	return (0);
}

int	sleeping(t_phi *philo)
{
	p_msg("is sleeping\n", philo);
	usleep(philo->data->tts * 1000);
	return (0);
}
