/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andvieir <andvieir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 14:35:28 by andvieir          #+#    #+#             */
/*   Updated: 2023/05/04 15:23:57 by andvieir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "phi_bonus.h"

void	simulation(t_phi *philo)
{
	if (philo->index % 2)
		usleep(2000);
	if (pthread_create(&philo->data->god, NULL, &vitals, philo))
		error("Failed creating god thread.\n");
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
}

int	proc_init(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_phi)
	{
		data->pid[i] = fork();
		if (data->pid[i] == -1)
			return (1);
		if (!data->pid[i])
		{
			data->philo[i].since_lm = get_time();
			simulation(&data->philo[i]);
			break ;
		}
		i++;
	}
	return (0);
}
