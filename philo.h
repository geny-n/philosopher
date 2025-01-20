/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngeny <ngeny@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 18:36:26 by ngeny             #+#    #+#             */
/*   Updated: 2025/01/17 13:27:20 by ngeny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "stdlib.h"
# include "unistd.h"
# include "stdio.h"
# include "pthread.h"
# include "limits.h"
# include "sys/time.h"

# define PHILO_MAX 200

typedef struct s_philo
{
	int				id;
	int				nbr_philo;
	int				*flag_die;
	int				flag_eating;
	int				cnt_meal;
	long long		start_time;
	long long		start_eat;
	long long		tm_die;
	long long		tm_eat;
	long long		tm_sleep;
	long long		tm_think;
	int				nb_to_eat;
	pthread_t		thread;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*check_dead;
	pthread_mutex_t	*is_eating;
	pthread_mutex_t	*mtx_print;
}	t_philo;

typedef struct s_data
{
	int				nbr_philo;
	int				is_dead;
	long long		tm_die;
	long long		tm_eat;
	long long		tm_sleep;
	int				nb_to_eat;
	pthread_mutex_t	check_dead;
	pthread_mutex_t	is_eating;
	pthread_mutex_t	mtx_print;
	pthread_mutex_t	mtx_forks[PHILO_MAX];
	t_philo			philo[PHILO_MAX];
}	t_data;

/********INIT********/
int			init_all(t_data *data, char **av);
int			init_data(t_data *data, char **av);
void		init_philo_bis(int i, t_data *data);
int			init_philo(t_data *data);

/*******PHILO LIFE***/
void		sleeping_time(t_philo *philo);
void		itadakimasu(t_philo *philo);
void		*philo_routine(void *data_th);
int			manage_philo(t_data *data);

/*****DEAD OR ALIVE*****/
int			philosopher_dead(t_philo *philo, int tm_die);
int			check_dead(t_philo *philo);
int			check_full(t_philo *philo);
void		*check_status(void *status_th);
int			dead_or_full(t_philo *philo);

/*******LIBFT*******/
int			ft_atoi(const char *nptr);
int			check_number(int argc, char **argv);

/*******FREE*******/
void		destroy_all(t_data *data, char *msg);
int			error(char *msg, int val);

/*******UTILS*******/
int			arg_is_num(char **av);
long long	get_time(void);
void		mail_print(t_philo *philo, char *msg);
void		to_wait(long long wait_tm, t_philo *philo);

#endif