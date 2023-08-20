/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 15:41:37 by andvieir          #+#    #+#             */
/*   Updated: 2023/08/20 14:51:04 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "phi.h"

/**
 * @brief Initializes the shared data structure with input arguments.
 *
 * This function initializes the shared `t_data` structure by setting various
 * fields using the input arguments from the command line. It also initializes
 * mutexes used for printing and protection against concurrent operations.
 * Returns 1 if data initialization is successful, 0 if an error occurs.
 *
 * @param data Pointer to the shared data structure.
 * @param ac Number of command-line arguments.
 * @param av Array of command-line argument strings.
 * @return 1 if data initialization is successful, 0 if an error occurs.
 */
int	data_init(t_data *data, int ac, char **av)
{
	data->time_init = get_time();
	data->num_phi = ft_atoi(av[1]);
	data->ttd = ft_atoi(av[2]);
	data->tte = ft_atoi(av[3]);
	data->tts = ft_atoi(av[4]);
	data->one_died = 0;
	data->all_eaten = 0;
	data->n_tte = -1;
	mutex_init(&data->print);
	mutex_init(&data->god_shield);
	if (ac == 6)
		data->n_tte = ft_atoi(av[5]);
	if (!data->num_phi || !data->n_tte)
		return (error("Number of philosophers must be > 0\n"));
	return (1);
}

/**
 * @brief Initializes the forks for the dining philosophers simulation.
 *
 * This function initializes an array of `t_fork` structures representing
 * the forks used by philosophers. It assigns each fork an ID and initializes
 * a mutex lock associated with it. The total number of forks is determined
 * by the number of philosophers specified in the shared data structure `data`.
 *
 * @param data Pointer to the shared data structure.
 */
void	fork_init(t_data *data)
{
	int	i;

	i = 0;
	data->fork = (t_fork *)malloc(sizeof(t_fork) * data->num_phi);
	while (i < data->num_phi)
	{
		data->fork[i].id = i + 1;
		mutex_init(&data->fork[i].lock);
		i++;
	}
}

/**
 * @brief Initializes the philosophers for the dining philosophers simulation.
 *
 * This function initializes an array of `t_phi` structures representing the
 * philosophers participating in the simulation. It assigns each philosopher
 * an index, initializes mutex locks, and sets initial values for various fields.
 * The left and right forks for each philosopher are assigned based on the
 * total number of philosophers in the shared data structure `data`.
 *
 * @param data Pointer to the shared data structure.
 */
void	philo_init(t_data *data)
{
	int	i;

	i = 0;
	data->philo = (t_phi *)malloc(sizeof(t_phi) * data->num_phi);
	while (i < data->num_phi)
	{
		data->philo[i].index = i + 1;
		data->philo[i].since_lm = get_time();
		data->philo[i].l_fork = &data->fork[i];
		if (data->num_phi != 1)
			data->philo[i].r_fork = &data->fork[(i + 1) % data->num_phi];
		data->philo[i].data = data;
		data->philo[i].n_eats = 0;
		data->philo[i].full = 0;
		mutex_init(&data->philo[i].reaper);
		i++;
	}
}
