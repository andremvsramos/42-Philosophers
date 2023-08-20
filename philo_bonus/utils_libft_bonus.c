/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_libft_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 16:56:56 by andvieir          #+#    #+#             */
/*   Updated: 2023/08/20 15:10:35 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* *******************************************************
 * Description:
 *
 * This code file contains essential utility functions used
 * for character checks, writing characters and strings to
 * file descriptors, and converting strings to integers.
 *
 * Functions:
 * - int ft_isdigit(int c)
 *   Checks if a character is a digit (0-9).
 *
 * - int ft_isspace(int c)
 *   Checks if a character is a whitespace character (space, tab, newline, etc.).
 *
 * - void ft_putchar_fd(char c, int fd)
 *   Writes a character to the specified file descriptor.
 *
 * - void ft_putstr_fd(char *str, int fd)
 *   Writes a string to the specified file descriptor.
 *
 * - int ft_atoi(const char *str)
 *   Converts a string to an integer, handling whitespace and sign symbols.
 *
 * Refer to the corresponding library (libft.h).
 * *******************************************************/

#include "phi_bonus.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}

int	ft_isspace(int c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (1);
	else
		return (0);
}

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void	ft_putstr_fd(char *str, int fd)
{
	while (*str)
	{
		ft_putchar_fd(*str, fd);
		str++;
	}
}

int	ft_atoi(const char *str)
{
	int	result;
	int	sign;

	result = 0;
	sign = 1;
	while (ft_isspace(*str))
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign *= -1;
		str++;
	}
	while (ft_isdigit(((int)*str)))
	{
		result = result * 10 + (*str - '0');
		str++;
	}
	return (result * sign);
}
