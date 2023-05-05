/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   god_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andvieir <andvieir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 11:56:15 by andvieir          #+#    #+#             */
/*   Updated: 2023/05/04 15:22:37 by andvieir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "phi_bonus.h"

void	*vitals(void *arg)
{
	t_phi	*philo;

	philo = (t_phi *)arg;
	while (1)
		if (deceased(philo))
			break ;
	return (NULL);
}

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

void	check_meals(t_data *data)
{
	pthread_t	monitor;
	pthread_t	meals;

	pthread_create(&monitor, NULL, monitoring, data);
	pthread_create(&meals, NULL, meals_done, data);
	pthread_join(monitor, NULL);
	pthread_join(meals, NULL);
}

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
