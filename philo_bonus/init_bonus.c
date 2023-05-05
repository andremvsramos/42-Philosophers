/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andvieir <andvieir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 12:49:03 by andvieir          #+#    #+#             */
/*   Updated: 2023/05/04 15:24:46 by andvieir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "phi_bonus.h"

int	semp_init(t_data *data)
{
	sem_unlink("finish");
	sem_unlink("meals");
	sem_unlink("one_died");
	sem_unlink("print");
	sem_unlink("fork");
	data->fork = sem_open("fork", O_CREAT, 0644, data->num_phi);
	data->one_died = sem_open("one_died", O_CREAT, 0644, 1);
	data->print = sem_open("print", O_CREAT, 0644, 1);
	data->meals = sem_open("meals", O_CREAT, 0644, 0);
	data->finish = sem_open("finish", O_CREAT, 0644, 0);
	if (data->fork == SEM_FAILED || data->one_died == SEM_FAILED
		|| data->print == SEM_FAILED || data->meals == SEM_FAILED
		|| data->finish == SEM_FAILED)
		return (1);
	return (0);
}

int	philo_init(t_data *data)
{
	int		i;
	char	*philosopher;

	i = 0;
	data->philo = (t_phi *)malloc(sizeof(t_phi) * data->num_phi);
	if (!data->philo)
		return (1);
	while (i < data->num_phi)
	{
		data->philo[i].index = i + 1;
		data->philo[i].data = data;
		data->philo[i].n_eats = 0;
		philosopher = ft_itoa(data->philo[i].index);
		sem_unlink(philosopher);
		data->philo[i].reaper = sem_open(philosopher, O_CREAT, 0644, 1);
		free(philosopher);
		i++;
	}
	return (0);
}

int	data_init(t_data *data, int ac, char **av)
{
	data->time_init = get_time();
	data->num_phi = ft_atoi(av[1]);
	data->ttd = ft_atoi(av[2]);
	data->tte = ft_atoi(av[3]);
	data->tts = ft_atoi(av[4]);
	data->all_eaten = 0;
	data->pid = (int *)malloc(sizeof(int) * data->num_phi);
	data->n_tte = -1;
	if (ac == 6)
		data->n_tte = ft_atoi(av[5]);
	if (!data->num_phi || !data->pid || !data)
		return (error("Memory allocation failed.\n"));
	if (philo_init(data))
	{
		error("crash on philo init\n");
		free(data->philo);
		return (0);
	}
	if (semp_init(data))
	{
		error("crash on semaphore init\n");
		free_semp(data);
		return (0);
	}
	return (1);
}
