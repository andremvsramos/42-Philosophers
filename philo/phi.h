/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phi.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 16:23:13 by andvieir          #+#    #+#             */
/*   Updated: 2023/08/20 14:47:22 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHI_H
# define PHI_H

# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <limits.h>
# include <sys/time.h>

/**
 * Structure representing a fork.
 */
typedef struct s_fork
{
	int				id;                 // Identifier of the fork
	pthread_mutex_t	lock;               // Mutex lock for synchronization
}				t_fork;

/**
 * Structure representing a philosopher.
 */
typedef struct s_phi
{
	int				index;              // Index of the philosopher
	long long		since_lm;           // Time since the philosopher's last meal
	int				n_eats;             // Number of meals eaten by the philosopher
	int				full;               // Flag indicating if the philosopher is full
	pthread_t		phi;                // Philosopher's thread
	pthread_mutex_t	reaper;             // Mutex for controlling the reaper
	t_fork			*l_fork;            // Pointer to the left fork
	t_fork			*r_fork;            // Pointer to the right fork
	struct s_data	*data;              // Pointer to shared data
}				t_phi;

/**
 * Structure representing shared data for the dining philosophers problem.
 */
typedef struct s_data
{
	int				num_phi;            // Number of philosophers
	int				ttd;                // Time to die (in milliseconds)
	int				tte;                // Time to eat (in milliseconds)
	int				tts;                // Time to sleep (in milliseconds)
	int				n_tte;              // Number of times each philosopher must eat
	int				one_died;           // Flag indicating if a philosopher has died
	int				all_eaten;          // Flag indicating if all philosophers have eaten
	long long		time_init;          // Initial time
	pthread_t		god;                // "God" thread for monitoring philosophers
	pthread_mutex_t	print;              // Mutex for synchronizing printing
	pthread_mutex_t	god_shield;         // Mutex for protecting "God" thread
	t_phi			*philo;              // Array of philosopher structures
	t_fork			*fork;               // Array of fork structures
}				t_data;

//-------------ROUTINES----------------//
void			*simulation(void *arg);
void			*vitals(void *arg);

//---------------INIT------------------//
int				data_init(t_data *data, int ac, char **av);
void			fork_init(t_data *data);
void			philo_init(t_data *data);

//-----------PHILOSOPHERS--------------//
int				thread_init(t_data *data);
int				thread_join(t_data *data);
void			m_destroy(t_data *data);

//----------------GOD------------------//
int				create_god(t_data *data);
int				alleaten(t_data *data);

//--------------STATES-----------------//
int				take_fork(t_phi *philo);
int				eating(t_phi *philo);
int				sleeping(t_phi *philo);
int				thinking(t_phi *philo);
int				deceased(t_data *data);

//------------UTILS LIBFT-------------//
int				ft_atoi(const char *str);
int				ft_isdigit(int c);
int				ft_isspace(int c);
void			ft_putstr_fd(char *str, int fd);
void			ft_putchar_fd(char c, int fd);

//---------------UTILS----------------//
long long		get_time(void);
void			p_msg(char *str, t_phi *philo);
int				error(char	*str);
int				clear_data(t_data *data);
int				valid_args(char **av);

//------------MUTEX UTILS-------------//
void			mutex_init(pthread_mutex_t *mutex);
void			mutex_lock(pthread_mutex_t *mutex);
void			mutex_unlock(pthread_mutex_t *mutex);
void			mutex_destroy(pthread_mutex_t *mutex);
void			choose_fork(t_phi *philo, pthread_mutex_t *f1,
					pthread_mutex_t *f2);

#endif
