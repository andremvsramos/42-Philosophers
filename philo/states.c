/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   states.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andvieir <andvieir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 10:59:56 by andvieir          #+#    #+#             */
/*   Updated: 2023/05/03 12:24:21 by andvieir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "phi.h"

int	take_fork(t_phi *philo)
{
	mutex_lock(&philo->data->god_shield);
	if (philo->data->one_died || philo->data->all_eaten == philo->data->num_phi)
	{
		mutex_unlock(&philo->data->god_shield);
		return (1);
	}
	mutex_unlock(&philo->data->god_shield);
	if (philo->index % 2)
		choose_fork(philo, &philo->l_fork->lock, &philo->r_fork->lock);
	else
		choose_fork(philo, &philo->r_fork->lock, &philo->l_fork->lock);
	return (0);
}

int	eating(t_phi *philo)
{
	mutex_lock(&philo->data->god_shield);
	if (philo->data->one_died || philo->data->all_eaten == philo->data->num_phi)
	{
		mutex_unlock(&philo->l_fork->lock);
		mutex_unlock(&philo->r_fork->lock);
		mutex_unlock(&philo->data->god_shield);
		return (1);
	}
	mutex_unlock(&philo->data->god_shield);
	mutex_lock(&philo->reaper);
	p_msg("is eating\n", philo);
	philo->since_lm = get_time();
	mutex_lock(&philo->data->god_shield);
	if (philo->data->n_tte != -1
		&& philo->n_eats <= philo->data->n_tte)
		philo->n_eats++;
	mutex_unlock(&philo->data->god_shield);
	mutex_unlock(&philo->reaper);
	usleep(philo->data->tte * 1000);
	mutex_unlock(&philo->r_fork->lock);
	mutex_unlock(&philo->l_fork->lock);
	return (0);
}

int	thinking(t_phi *philo)
{
	mutex_lock(&philo->data->god_shield);
	if (philo->data->one_died || philo->data->all_eaten == philo->data->num_phi)
	{
		mutex_unlock(&philo->data->god_shield);
		return (1);
	}
	mutex_unlock(&philo->data->god_shield);
	p_msg("is thinking\n", philo);
	return (0);
}

int	sleeping(t_phi *philo)
{
	mutex_lock(&philo->data->god_shield);
	if (philo->data->one_died || philo->data->all_eaten == philo->data->num_phi)
	{
		mutex_unlock(&philo->data->god_shield);
		return (1);
	}
	mutex_unlock(&philo->data->god_shield);
	p_msg("is sleeping\n", philo);
	usleep(philo->data->tts * 1000);
	return (0);
}
