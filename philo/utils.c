/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 15:28:40 by andvieir          #+#    #+#             */
/*   Updated: 2023/08/20 15:04:24 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "phi.h"

/**
 * @brief Displays an error message and returns an error code.
 *
 * This function displays an error message to the standard error stream (stderr),
 * followed by the provided string `str`. It is commonly used to handle errors
 * in the program's execution. The function returns 0 to indicate an error condition.
 *
 * @param str The error message to display.
 * @return Returns 0 to indicate an error.
 */
int	error(char	*str)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(str, 2);
	return (0);
}

/**
 * @brief Retrieves the current time in milliseconds.
 *
 * This function retrieves the current time in milliseconds since an arbitrary epoch
 * and returns it as a `long long` value. It uses the `gettimeofday` function to
 * achieve this precision.
 *
 * @return Returns the current time in milliseconds.
 */
long long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

/**
 * @brief Prints a message with a timestamp and philosopher index.
 *
 * This function prints a message with a timestamp, philosopher index, and a provided
 * message string. It first acquires the `print` mutex to ensure thread-safe printing,
 * then checks whether the specified philosopher has died or if all philosophers have
 * finished eating to avoid unnecessary printing. It then prints the message along with
 * a timestamp indicating the time since the program's start and the philosopher's index.
 * Finally, the function releases the `print` mutex.
 *
 * @param str The message string to print.
 * @param philo Pointer to the philosopher's data structure.
 */
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

/**
 * @brief Validates the command-line arguments as numeric values.
 *
 * This function checks whether all command-line arguments are valid numeric values.
 * It iterates through the provided array of strings `av`, verifying that each character
 * in the strings represents a digit. If all characters are digits in all arguments,
 * the function returns 1 to indicate valid arguments; otherwise, it returns 0.
 *
 * @param av Array of command-line argument strings.
 * @return Returns 1 if all arguments are valid numeric values, otherwise returns 0.
 */
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
