/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   states.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 10:59:56 by andvieir          #+#    #+#             */
/*   Updated: 2023/08/20 14:57:24 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "phi.h"

/**
 * @brief Attempts to pick up the forks required for eating.
 *
 * This function simulates a philosopher's attempt to pick up the forks required for eating.
 * The philosopher first checks whether any termination conditions have been met, such as
 * the death of a philosopher or the completion of all meals. If so, the function returns
 * immediately. Otherwise, the philosopher attempts to pick up the appropriate forks based
 * on their index, using synchronization mechanisms to avoid deadlocks. To prevent
 * reverse-lock-inversion, the philosopher with an odd index first tries to lock the left
 * fork and then the right fork, while the philosopher with an even index does the opposite.
 *
 * @param philo Pointer to the philosopher's data structure.
 * @return Returns 1 if termination conditions are met, otherwise returns 0.
 */
int	take_fork(t_phi *philo)
{
	mutex_lock(&philo->data->god_shield);
	if (philo->data->one_died || philo->data->all_eaten == philo->data->num_phi)
	{
		mutex_unlock(&philo->data->god_shield);
		return (1);
	}
	mutex_unlock(&philo->data->god_shield);
	if (philo->index % 2)
		choose_fork(philo, &philo->l_fork->lock, &philo->r_fork->lock);
	else
		choose_fork(philo, &philo->r_fork->lock, &philo->l_fork->lock);
	return (0);
}

/**
 * @brief Represents the eating action of a philosopher.
 *
 * This function simulates the eating action of a philosopher after successfully picking
 * up the required forks. It also updates the philosopher's state, records the time of
 * their last meal, and increments the count of their eaten meals. After a specified
 * duration of eating, the function releases the forks and returns. To prevent data races,
 * the philosopher locks appropriate mutexes during critical sections, such as updating
 * the philosopher's state and releasing the forks.
 *
 * @param philo Pointer to the philosopher's data structure.
 * @return Returns 1 if termination conditions are met, otherwise returns 0.
 */
int	eating(t_phi *philo)
{
	mutex_lock(&philo->data->god_shield);
	if (philo->data->one_died || philo->data->all_eaten == philo->data->num_phi)
	{
		mutex_unlock(&philo->l_fork->lock);
		mutex_unlock(&philo->r_fork->lock);
		mutex_unlock(&philo->data->god_shield);
		return (1);
	}
	mutex_unlock(&philo->data->god_shield);
	mutex_lock(&philo->reaper);
	p_msg("is eating\n", philo);
	philo->since_lm = get_time();
	mutex_lock(&philo->data->god_shield);
	if (philo->data->n_tte != -1
		&& philo->n_eats <= philo->data->n_tte)
		philo->n_eats++;
	mutex_unlock(&philo->data->god_shield);
	mutex_unlock(&philo->reaper);
	usleep(philo->data->tte * 1000);
	mutex_unlock(&philo->r_fork->lock);
	mutex_unlock(&philo->l_fork->lock);
	return (0);
}

/**
 * @brief Represents the thinking action of a philosopher.
 *
 * This function simulates the thinking action of a philosopher during which they are not
 * holding any forks. It checks whether termination conditions are met before allowing
 * the philosopher to think, and returns 1 if they are. Otherwise, it prints a message
 * indicating that the philosopher is thinking. To prevent data races, the philosopher
 * locks appropriate mutexes when checking for termination conditions and printing messages.
 *
 * @param philo Pointer to the philosopher's data structure.
 * @return Returns 1 if termination conditions are met, otherwise returns 0.
 */
int	thinking(t_phi *philo)
{
	mutex_lock(&philo->data->god_shield);
	if (philo->data->one_died || philo->data->all_eaten == philo->data->num_phi)
	{
		mutex_unlock(&philo->data->god_shield);
		return (1);
	}
	mutex_unlock(&philo->data->god_shield);
	p_msg("is thinking\n", philo);
	return (0);
}

/**
 * @brief Represents the sleeping action of a philosopher.
 *
 * This function simulates the sleeping action of a philosopher during which they do not
 * hold any forks. Similar to other actions, it checks whether termination conditions are
 * met before allowing the philosopher to sleep, and returns 1 if they are. Otherwise,
 * it prints a message indicating that the philosopher is sleeping for a specified duration.
 * To prevent data races, the philosopher locks appropriate mutexes when checking for
 * termination conditions and printing messages.
 *
 * @param philo Pointer to the philosopher's data structure.
 * @return Returns 1 if termination conditions are met, otherwise returns 0.
 */
int	sleeping(t_phi *philo)
{
	mutex_lock(&philo->data->god_shield);
	if (philo->data->one_died || philo->data->all_eaten == philo->data->num_phi)
	{
		mutex_unlock(&philo->data->god_shield);
		return (1);
	}
	mutex_unlock(&philo->data->god_shield);
	p_msg("is sleeping\n", philo);
	usleep(philo->data->tts * 1000);
	return (0);
}
