/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 15:15:48 by andvieir          #+#    #+#             */
/*   Updated: 2023/08/20 15:06:39 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "phi_bonus.h"

/**
 * @brief Calculates the length of an integer's string representation.
 *
 * This function calculates the length of an integer's string representation,
 * considering both positive and negative integers.
 *
 * @param n The integer for which the length of the string representation is to be calculated.
 * @return The length of the string representation of the integer.
 */
static int	ft_length(int n)
{
	int	length;

	length = 0;
	if (n <= 0)
		length++;
	while (n != 0)
	{
		length++;
		n = n / 10;
	}
	return (length);
}

/**
 * @brief Calculates the absolute value of an integer.
 *
 * This function returns the absolute value of an integer, preserving the sign of positive integers.
 *
 * @param n The integer for which the absolute value is to be calculated.
 * @return The absolute value of the integer.
 */
static int	ft_abs(int n)
{
	if (n < 0)
		return (-n);
	return (n);
}

/**
 * @brief Converts an integer to its string representation.
 *
 * This function converts an integer to its string representation and returns a dynamically
 * allocated string containing the result. It considers both positive and negative integers.
 *
 * @param n The integer to be converted to a string.
 * @return A dynamically allocated string containing the string representation of the integer.
 *         The caller is responsible for freeing the memory allocated for this string.
 */
char	*ft_itoa(int n)
{
	char	*result;
	int		length;

	length = ft_length(n);
	result = malloc(sizeof(char) * (length + 1));
	if (!result)
		return (0);
	result[length] = '\0';
	if (n < 0)
		result[0] = '-';
	else if (n == 0)
		result[0] = '0';
	while (n != 0)
	{
		length--;
		result[length] = ft_abs(n % 10) + '0';
		n = n / 10;
	}
	return (result);
}
