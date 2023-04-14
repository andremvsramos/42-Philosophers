/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andvieir <andvieir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 15:28:40 by andvieir          #+#    #+#             */
/*   Updated: 2023/04/14 11:48:44 by andvieir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/phi.h"

int	error(char	*str)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(str, 2);
	return (0);
}

long long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	p_msg(char *str, t_phi *philo)
{
	long long	time;

	if (philo->data->one_died || philo->data->all_eaten == philo->data->num_phi)
		return ;
	time = get_time() - philo->data->time_init;
	if (pthread_mutex_lock(&philo->data->print) != 0)
		error("Failed locking print.\n");
	printf("%lld %d %s", time, philo->index, str);
	if (pthread_mutex_unlock(&philo->data->print) != 0)
		error("Failed unlocking print.\n");
}
