/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   states.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andvieir <andvieir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 10:59:56 by andvieir          #+#    #+#             */
/*   Updated: 2023/04/14 11:48:22 by andvieir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/phi.h"

void	take_fork(t_phi *philo)
{
	//if (philo->data->all_eaten)
	if (pthread_mutex_lock(&philo->l_fork->lock) != 0)
		error("Failed locking left fork mutex\n");
	p_msg("has taken a fork\n", philo);
	if (pthread_mutex_lock(&philo->r_fork->lock) != 0)
		error("Failed locking right fork mutex\n");
	p_msg("has taken a fork\n", philo);
}

void	eating(t_phi *philo)
{
	philo->since_lm = get_time();
	p_msg("is eating\n", philo);
	if (philo->data->n_tte != -1)
	{
		philo->n_eats++;
		if (philo->n_eats == philo->data->n_tte)
			philo->data->all_eaten++;
	}
	usleep(philo->data->tte * 1000);
	if (pthread_mutex_unlock(&philo->l_fork->lock) != 0)
		error("Failed unlocking left fork mutex\n");
	if (pthread_mutex_unlock(&philo->r_fork->lock) != 0)
		error("Failed unlocking right fork mutex\n");
}

void	thinking(t_phi *philo)
{
	p_msg("is thinking\n", philo);
}

void	sleeping(t_phi *philo)
{
	p_msg("is sleeping\n", philo);
	usleep(philo->data->tts * 1000);
}

int	deceased(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_phi)
	{
		if ((get_time() - data->philo[i].since_lm) > data->ttd)
		{
			p_msg("died.\n", &data->philo[i]);
			data->one_died = 1;
			return (1);
		}
		i++;
	}
	return (0);
}
