/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andvieir <andvieir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 15:10:05 by andvieir          #+#    #+#             */
/*   Updated: 2023/04/27 15:31:50 by andvieir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "phi.h"

void	choose_fork(t_phi *philo, pthread_mutex_t *f1, pthread_mutex_t *f2)
{
	if (pthread_mutex_lock(f1))
		error("Failed locking f1\n");
	p_msg("has taken a fork\n", philo);
	if (pthread_mutex_lock(f2))
		error("Failed locking f2\n");
	p_msg("has taken a fork\n", philo);
}

void	mutex_init(pthread_mutex_t *mutex)
{
	if (pthread_mutex_init(mutex, NULL))
		error("Failed initializing mutex\n.");
}

void	mutex_lock(pthread_mutex_t *mutex)
{
	if (pthread_mutex_lock(mutex))
		error("Failed unlocking mutex\n.");
}

void	mutex_unlock(pthread_mutex_t *mutex)
{
	if (pthread_mutex_unlock(mutex))
		error("Failed unlocking mutex\n.");
}

void	mutex_destroy(pthread_mutex_t *mutex)
{
	if (pthread_mutex_destroy(mutex))
		error("Failed destroying mutex\n.");
}
