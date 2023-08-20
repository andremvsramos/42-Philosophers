/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phi_bonus.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 12:17:02 by andvieir          #+#    #+#             */
/*   Updated: 2023/08/20 15:05:41 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHI_BONUS_H
# define PHI_BONUS_H

# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <limits.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <semaphore.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <signal.h>

/**
 * @brief Structure representing a philosopher in the dining philosophers problem.
 *
 * This structure holds information about an individual philosopher including their
 * index, time since their last meal, number of eaten meals, and synchronization
 * semaphore for reaping. It also stores a reference to the shared data structure.
 */
typedef struct s_phi
{
	int				index;
	long long		since_lm;
	int				n_eats;
	sem_t			*reaper;
	struct s_data	*data;
}				t_phi;

/**
 * @brief Structure representing shared data for the dining philosophers problem.
 *
 * This structure holds the shared information required for the bonus part of the dining
 * philosophers problem. It includes the number of philosophers, time to die, time to eat,
 * time to sleep, maximum number of times a philosopher must eat, and other synchronization
 * semaphores and flags.
 */
typedef struct s_data
{
	int				num_phi;
	int				ttd;
	int				tte;
	int				tts;
	int				n_tte;
	int				all_eaten;
	long long		time_init;
	int				*pid;
	t_phi			*philo;
	pthread_t		god;
	sem_t			*one_died;
	sem_t			*print;
	sem_t			*fork;
	sem_t			*finish;
	sem_t			*meals;
}				t_data;

//INIT
int				data_init(t_data *data, int ac, char **av);
void			fork_init(t_data *data);
int				philo_init(t_data *data);
int				proc_init(t_data *data);
int				valid_args(char **av);

//CLEANUP
int				clear_data(t_data *data);
void			free_semp(t_data *data);

//ROUTINES
void			simulation(t_phi *philo);
void			*vitals(void *arg);

//STATES
int				take_fork(t_phi *philo);
int				eating(t_phi *philo);
int				sleeping(t_phi *philo);
int				thinking(t_phi *philo);

//GOD & MONITORING
int				deceased(t_phi *philo);
void			check_meals(t_data *data);
void			*monitoring(void *arg);
void			*meals_done(void *arg);

//UTILS
long long		get_time(void);
void			p_msg(char *str, t_phi *philo);
int				error(char	*str);

//UTILS LIBFT
int				ft_atoi(const char *str);
int				ft_isdigit(int c);
int				ft_isspace(int c);
void			ft_putstr_fd(char *str, int fd);
void			ft_putchar_fd(char c, int fd);
char			*ft_itoa(int n);

#endif
