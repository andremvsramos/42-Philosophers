/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 12:52:26 by andvieir          #+#    #+#             */
/*   Updated: 2023/08/20 15:10:19 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "phi_bonus.h"

/**
 * @brief Retrieves the current time in milliseconds.
 *
 * This function gets the current time using the system's gettimeofday function and returns it in
 * milliseconds since the epoch. It provides a precise timestamp for various time calculations.
 *
 * @return The current time in milliseconds.
 */
long long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

/**
 * @brief Prints an error message to the standard error stream.
 *
 * This function displays an error message to the standard error stream (stderr). It prefixes the message
 * with "Error\n" and then prints the provided string argument.
 *
 * @param str The error message to be printed.
 * @return Always returns 0.
 */
int	error(char	*str)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(str, 2);
	return (0);
}

/**
 * @brief Prints a formatted message with timestamp and philosopher index.
 *
 * This function prints a formatted message that includes the current timestamp, philosopher index, and
 * a custom message string. It uses semaphores to ensure thread-safe printing and to prevent concurrent
 * access to shared output resources.
 *
 * @param str The message string to be printed.
 * @param philo A pointer to the philosopher's data structure.
 */
void	p_msg(char *str, t_phi *philo)
{
	long long	time;

	sem_wait(philo->data->print);
	time = get_time() - philo->data->time_init;
	printf("%lld %d %s", time, philo->index, str);
	sem_post(philo->data->print);
}
