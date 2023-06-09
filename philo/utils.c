/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_libft.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andvieir <andvieir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 15:28:40 by andvieir          #+#    #+#             */
/*   Updated: 2023/04/28 09:30:52 by andvieir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "phi.h"

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

	mutex_lock(&philo->data->print);
	mutex_lock(&philo->data->god_shield);
	if (philo->data->one_died || philo->data->all_eaten == philo->data->num_phi)
	{
		mutex_unlock(&philo->data->god_shield);
		mutex_unlock(&philo->data->print);
		return ;
	}
	mutex_unlock(&philo->data->god_shield);
	time = get_time() - philo->data->time_init;
	printf("%lld %d %s", time, philo->index, str);
	mutex_unlock(&philo->data->print);
}

int	valid_args(char **av)
{
	int	i;
	int	j;

	i = 1;
	while (av[i])
	{
		j = 0;
		while (av[i][j])
		{
			if (!ft_isdigit(av[i][j]))
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}
