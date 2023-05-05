/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andvieir <andvieir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 09:29:17 by andvieir          #+#    #+#             */
/*   Updated: 2023/04/28 09:30:05 by andvieir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "phi.h"

int	clear_data(t_data *data)
{
	m_destroy(data);
	free(data->fork);
	free(data->philo);
	free(data);
	return (0);
}

void	m_destroy(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_phi)
	{
		mutex_destroy(&data->philo[i].reaper);
		mutex_destroy(&data->fork[i].lock);
		i++;
	}
	mutex_destroy(&data->print);
}
