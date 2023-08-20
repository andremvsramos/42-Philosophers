/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 14:35:28 by andvieir          #+#    #+#             */
/*   Updated: 2023/08/20 15:09:08 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "phi_bonus.h"

/**
 * @brief Simulates the actions of a philosopher in the dining philosophers problem.
 *
 * This function represents the simulation of a philosopher's actions. It introduces a delay for
 * philosophers with odd indices to prevent immediate synchronization. The function creates a vital
 * monitoring thread and enters an infinite loop where the philosopher attempts to perform actions,
 * such as taking forks, eating, sleeping, and thinking.
 *
 * @param philo A pointer to the philosopher's data structure.
 */
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

/**
 * @brief Initializes philosopher processes.
 *
 * This function initializes processes for each philosopher using the `fork` system call. It creates
 * a new process for each philosopher and enters the simulation loop within the child process. The
 * parent process continues iterating to create the remaining philosopher processes.
 *
 * @param data A pointer to the main data structure.
 * @return 1 if process initialization fails, 0 if successful.
 */
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
