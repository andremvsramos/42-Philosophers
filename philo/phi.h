/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phi.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andvieir <andvieir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 16:23:13 by andvieir          #+#    #+#             */
/*   Updated: 2023/04/28 12:33:10 by andvieir         ###   ########.fr       */
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

typedef struct s_fork
{
	int				id;
	pthread_mutex_t	lock;
}				t_fork;

typedef struct s_phi
{
	int				index;
	long long		since_lm;
	int				n_eats;
	int				full;
	pthread_t		phi;
	pthread_mutex_t	reaper;
	t_fork			*l_fork;
	t_fork			*r_fork;
	struct s_data	*data;
}				t_phi;

typedef struct s_data
{
	int				num_phi;
	int				ttd;
	int				tte;
	int				tts;
	int				n_tte;
	int				one_died;
	int				all_eaten;
	long long		time_init;
	pthread_t		god;
	pthread_mutex_t	print;
	pthread_mutex_t	god_shield;
	t_phi			*philo;
	t_fork			*fork;
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
