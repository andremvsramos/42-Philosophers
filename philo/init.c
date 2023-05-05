/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andvieir <andvieir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 15:41:37 by andvieir          #+#    #+#             */
/*   Updated: 2023/04/28 09:25:18 by andvieir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "phi.h"

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
