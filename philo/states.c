/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   states.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andvieir <andvieir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 10:59:56 by andvieir          #+#    #+#             */
/*   Updated: 2023/04/27 10:41:40 by andvieir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "phi.h"

int	take_fork(t_phi *philo)
{
	if (philo->data->one_died || philo->data->all_eaten == philo->data->num_phi)
		return (1);
	if (pthread_mutex_lock(&philo->l_fork->lock) != 0)
		error("Failed locking left fork mutex\n");
	p_msg("has taken a fork\n", philo);
	if (pthread_mutex_lock(&philo->r_fork->lock) != 0)
		error("Failed locking right fork mutex\n");
	p_msg("has taken a fork\n", philo);
	return (0);
}

int	eating(t_phi *philo)
{
	if (philo->data->one_died || philo->data->all_eaten == philo->data->num_phi)
		return (1);
	if (pthread_mutex_lock(&philo->reaper))
		error("Failed locking reaper\n");
	p_msg("is eating\n", philo);
	philo->since_lm = get_time();
	if (philo->data->n_tte != -1
		&& philo->n_eats <= philo->data->n_tte)
		philo->n_eats++;
	usleep(philo->data->tte * 1000);
	if (pthread_mutex_unlock(&philo->l_fork->lock) != 0)
		error("Failed unlocking left fork mutex\n");
	if (pthread_mutex_unlock(&philo->r_fork->lock) != 0)
		error("Failed unlocking right fork mutex\n");
	if (pthread_mutex_unlock(&philo->reaper))
		error("Failed unlocking reaper\n");
	return (0);
}

int	thinking(t_phi *philo)
{
	if (philo->data->one_died || philo->data->all_eaten == philo->data->num_phi)
		return (1);
	p_msg("is thinking\n", philo);
	return (0);
}

int	sleeping(t_phi *philo)
{
	if (philo->data->one_died || philo->data->all_eaten == philo->data->num_phi)
		return (1);
	p_msg("is sleeping\n", philo);
	usleep(philo->data->tts * 1000);
	return (0);
}

int	deceased(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_phi)
	{
		if ((get_time() - data->philo[i].since_lm) > data->ttd)
		{
			if (pthread_mutex_lock(&data->philo[i].reaper))
				error("Failed locking reaper\n");
			p_msg("died.\n", &data->philo[i]);
			data->one_died = 1;
			if (pthread_mutex_unlock(&data->philo[i].reaper))
				error("Failed unlocking reaper\n");
			return (1);
		}
		i++;
	}
	return (0);
}
