/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   god.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andvieir <andvieir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 09:20:42 by andvieir          #+#    #+#             */
/*   Updated: 2023/05/03 12:26:52 by andvieir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "phi.h"

int	create_god(t_data *data)
{
	if (pthread_create(&data->god, NULL, &vitals, data) != 0)
		return (error("Failed creating vitals monitor.\n"));
	if (pthread_join(data->god, NULL) != 0)
		return (error("Failed closing vitals.\n"));
	return (1);
}

int	alleaten(t_data *data)
{
	int	i;

	i = 0;
	if (data->n_tte == -1)
		return (0);
	mutex_lock(&data->god_shield);
	while (i < data->num_phi)
	{
		if (data->philo[i].n_eats == data->n_tte && !data->philo[i].full)
		{
			data->philo[i].full = 1;
			data->all_eaten++;
		}
		i++;
	}
	if (data->all_eaten == data->num_phi)
	{
		mutex_unlock(&data->god_shield);
		return (1);
	}
	mutex_unlock(&data->god_shield);
	return (0);
}

int	deceased(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_phi)
	{
		mutex_lock(&data->philo[i].reaper);
		if ((get_time() - data->philo[i].since_lm) > data->ttd)
		{
			p_msg("died\n", &data->philo[i]);
			mutex_lock(&data->god_shield);
			data->one_died = 1;
			mutex_unlock(&data->god_shield);
			mutex_unlock(&data->philo[i].reaper);
			return (1);
		}
		mutex_unlock(&data->philo[i].reaper);
		i++;
	}
	return (0);
}
