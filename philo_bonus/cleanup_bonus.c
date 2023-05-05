/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andvieir <andvieir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 16:31:26 by andvieir          #+#    #+#             */
/*   Updated: 2023/05/04 14:50:11 by andvieir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "phi_bonus.h"

void	free_semp(t_data *data)
{
	sem_close(data->finish);
	sem_close(data->meals);
	sem_close(data->one_died);
	sem_close(data->print);
	sem_close(data->fork);
	sem_unlink("finish");
	sem_unlink("meals");
	sem_unlink("one_died");
	sem_unlink("print");
	sem_unlink("fork");
}

int	clear_data(t_data *data)
{
	int		i;
	char	*philosopher;

	i = 0;
	free_semp(data);
	while (i < data->num_phi)
	{
		philosopher = ft_itoa(data->philo[i].index);
		sem_close(data->philo[i++].reaper);
		sem_unlink(philosopher);
		free(philosopher);
	}
	free(data->philo);
	free(data->pid);
	free(data);
	return (0);
}
