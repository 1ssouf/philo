/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialousse <ialousse@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 17:00:33 by ialousse          #+#    #+#             */
/*   Updated: 2023/08/28 23:21:23 by ialousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <sys/time.h>
# include <limits.h>

typedef struct l_philo
{
	int				n;
	int				m_count;
	bool			is_eating;
	pthread_t		thread;
	long int		last_eat;
	struct l_info	*info;
	pthread_mutex_t	*fork_right;
	pthread_mutex_t	fork_left;
}		t_philo;

typedef struct l_info
{
	int				philo_eat;
	int				nbr_philo;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				nbr_eat;
	int				stop;
	long int		time_start;
	t_philo			*philo;
	pthread_mutex_t	print;
	pthread_mutex_t	m_stop;
	pthread_mutex_t	m_eat;
	pthread_mutex_t	dead;
}	t_info;

/*init.c*/
int			var_init(t_info *data, char **av);
int			philo_init(t_info *data);

/*libft.c*/
int			ft_atoi(const char *str);
int			ft_isdigit(int character);
int			ft_check_nbr(char **str);

/*main.c*/
void		freeall(t_info *data);

/*philo.c*/
void		*check_death(void *phi);
void		*philo_life(void *phi);
void		philo_eat(t_philo *philo);
void		take_fork(t_philo *philo);

/*utils.c*/
void		ft_usleep(int s);
int			is_dead(t_philo *philo, int nb);
long long	timestamp(void);
void		print(t_philo *philo, char *str);

#endif