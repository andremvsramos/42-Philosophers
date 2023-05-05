/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andvieir <andvieir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 09:27:36 by andvieir          #+#    #+#             */
/*   Updated: 2023/04/28 09:28:14 by andvieir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "phi.h"

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
