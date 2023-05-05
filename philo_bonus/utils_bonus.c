/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andvieir <andvieir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 12:52:26 by andvieir          #+#    #+#             */
/*   Updated: 2023/05/04 15:22:55 by andvieir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "phi_bonus.h"

long long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

int	error(char	*str)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(str, 2);
	return (0);
}

void	p_msg(char *str, t_phi *philo)
{
	long long	time;

	sem_wait(philo->data->print);
	time = get_time() - philo->data->time_init;
	printf("%lld %d %s", time, philo->index, str);
	sem_post(philo->data->print);
}
