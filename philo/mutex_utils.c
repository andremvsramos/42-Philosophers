/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 15:10:05 by andvieir          #+#    #+#             */
/*   Updated: 2023/08/20 14:53:32 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "phi.h"

/**
 * @brief Acquires two forks for a philosopher to use.
 *
 * This function locks the two mutexes representing the forks `f1` and `f2` for the
 * philosopher `philo`. It also displays messages indicating that the philosopher
 * has taken each fork. If either mutex locking operation fails, an error message is
 * displayed. The function ensures proper synchronization when a philosopher acquires
 * the forks for eating.
 *
 * @param philo Pointer to the philosopher's data structure.
 * @param f1 Pointer to the mutex representing the first fork.
 * @param f2 Pointer to the mutex representing the second fork.
 */
void	choose_fork(t_phi *philo, pthread_mutex_t *f1, pthread_mutex_t *f2)
{
	if (pthread_mutex_lock(f1))
		error("Failed locking f1\n");
	p_msg("has taken a fork\n", philo);
	if (pthread_mutex_lock(f2))
		error("Failed locking f2\n");
	p_msg("has taken a fork\n", philo);
}

/**
 * @brief Initializes a mutex for synchronization.
 *
 * This function initializes the mutex pointed to by `mutex` using the default
 * attributes. If the initialization fails, an error message is displayed. The
 * function helps prepare mutexes for synchronization and resource protection.
 *
 * @param mutex Pointer to the mutex to be initialized.
 */
void	mutex_init(pthread_mutex_t *mutex)
{
	if (pthread_mutex_init(mutex, NULL))
		error("Failed initializing mutex\n.");
}

/**
 * @brief Locks a mutex for synchronization.
 *
 * This function locks the mutex pointed to by `mutex`. If the locking operation
 * fails, an error message is displayed. It ensures proper synchronization and
 * mutual exclusion among threads accessing shared resources.
 *
 * @param mutex Pointer to the mutex to be locked.
 */
void	mutex_lock(pthread_mutex_t *mutex)
{
	if (pthread_mutex_lock(mutex))
		error("Failed unlocking mutex\n.");
}

/**
 * @brief Unlocks a mutex after synchronization.
 *
 * This function unlocks the mutex pointed to by `mutex`. If the unlocking operation
 * fails, an error message is displayed. It releases the mutex after a critical
 * section has been completed, allowing other threads to access shared resources.
 *
 * @param mutex Pointer to the mutex to be unlocked.
 */
void	mutex_unlock(pthread_mutex_t *mutex)
{
	if (pthread_mutex_unlock(mutex))
		error("Failed unlocking mutex\n.");
}

/**
 * @brief Destroys a mutex after synchronization.
 *
 * This function destroys the mutex pointed to by `mutex`. If the destruction
 * operation fails, an error message is displayed. It releases the resources
 * allocated for the mutex, ensuring proper cleanup after its use.
 *
 * @param mutex Pointer to the mutex to be destroyed.
 */
void	mutex_destroy(pthread_mutex_t *mutex)
{
	if (pthread_mutex_destroy(mutex))
		error("Failed destroying mutex\n.");
}
