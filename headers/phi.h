/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phi.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andvieir <andvieir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 16:23:13 by andvieir          #+#    #+#             */
/*   Updated: 2023/04/14 10:14:08 by andvieir         ###   ########.fr       */
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
	int			id;
	pthread_mutex_t	lock;
}				t_fork;

typedef struct s_phi
{
	int				index;
	long long		since_lm;
	int				n_eats;
	pthread_t		phi;
	t_fork			*l_fork;
	t_fork			*r_fork;
	struct s_data	*data;
}				t_phi;

typedef struct s_data
{
	unsigned int	start;
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
	t_phi			*philo;
	t_fork			*fork;
}				t_data;

int				ft_atoi(const char *str);
int				ft_isdigit(int c);
int				ft_isspace(int c);

void			*simulation(void *arg);
void			*vitals(void *arg);

long long		get_time(void);
int				data_init(t_data *data, int ac, char **av);
void			fork_init(t_data *data);
void			philo_init(t_data *data);
int				valid_args(char **av);



int				thread_init(t_data *data);
int				thread_join(t_data *data);

void			take_fork(t_phi *philo);
void			eating(t_phi *philo);
void			sleeping(t_phi *philo);
void			thinking(t_phi *philo);
int				deceased(t_data *data);
int				alleaten(t_data *data);

void			ft_putstr_fd(char *str, int fd);
void			ft_putchar_fd(char c, int fd);

void			p_msg(char *str, t_phi *philo);
int				error(char	*str);

#endif
