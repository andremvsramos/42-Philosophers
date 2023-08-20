/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   god.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 09:20:42 by andvieir          #+#    #+#             */
/*   Updated: 2023/08/20 14:52:06 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "phi.h"

/**
 * @brief Creates and monitors the vital signs of the philosophers.
 *
 * This function creates a monitoring thread, `vitals`, using a separate thread.
 * The `vitals` thread monitors the vital signs of philosophers' activities and
 * their time of death. It does so by analyzing the time elapsed since their last
 * meal. The function waits for the `vitals` thread to complete using `pthread_join`
 * and returns 1 on success or 0 if an error occurs during thread creation.
 *
 * @param data Pointer to the shared data structure.
 * @return 1 on success, 0 on thread creation failure.
 */
int	create_god(t_data *data)
{
	if (pthread_create(&data->god, NULL, &vitals, data) != 0)
		return (error("Failed creating vitals monitor.\n"));
	if (pthread_join(data->god, NULL) != 0)
		return (error("Failed closing vitals.\n"));
	return (1);
}

/**
 * @brief Checks if all philosophers have eaten the required number of times.
 *
 * This function checks if all philosophers have successfully consumed the
 * required number of meals. If the specified number of times to eat (`n_tte`)
 * is not set, the function returns 0. Otherwise, it iterates through the
 * philosophers' data and updates their `full` status and the count of fully-fed
 * philosophers. It returns 1 if all philosophers have eaten the required number
 * of meals, and 0 otherwise.
 *
 * @param data Pointer to the shared data structure.
 * @return 1 if all philosophers have eaten the required times, 0 otherwise.
 */
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

/**
 * @brief Checks if any philosopher has exceeded their time to die.
 *
 * This function iterates through the philosophers' data, analyzing their last meal
 * times compared to the specified time to die (`ttd`). If any philosopher's time
 * since their last meal exceeds `ttd`, the function prints a death message and
 * updates the `one_died` status in the shared data. The function returns 1 if a
 * philosopher has died, and 0 otherwise.
 *
 * @param data Pointer to the shared data structure.
 * @return 1 if a philosopher has died, 0 otherwise.
 */
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
