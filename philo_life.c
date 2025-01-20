/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngeny <ngeny@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 23:23:03 by ngeny             #+#    #+#             */
/*   Updated: 2025/01/17 13:32:44 by ngeny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	sleeping_time(t_philo *philo)
{
	mail_print(philo, "is sleeping");
	to_wait(philo->tm_sleep, philo);
}

void	thinking_time(t_philo *philo)
{
	mail_print(philo, "is thinking");
}

void	itadakimasu(t_philo *philo)
{
	if (dead_or_full(philo))
		return ;
	pthread_mutex_lock(philo->r_fork);
	mail_print(philo, "has taken a fork");
	if (philo->nbr_philo == 1)
	{
		to_wait(philo->tm_die, philo);
		pthread_mutex_unlock(philo->r_fork);
		return ;
	}
	pthread_mutex_lock(philo->l_fork);
	mail_print(philo, "has taken a fork");
	pthread_mutex_lock(philo->is_eating);
	philo->flag_eating = 1;
	philo->cnt_meal += 1;
	philo->start_eat = get_time();
	pthread_mutex_unlock(philo->is_eating);
	mail_print(philo, "is eating");
	to_wait(philo->tm_eat, philo);
	philo->flag_eating = 0;
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(philo->l_fork);
}

void	*philo_routine(void *data_th)
{
	t_philo	*philo;

	philo = (t_philo *)data_th;
	if (philo->id % 2 != 0)
		to_wait(philo->tm_eat / 2, philo);
	while (dead_or_full(philo) != 1)
	{
		itadakimasu(philo);
		if (dead_or_full(philo) == 1)
			break ;
		sleeping_time(philo);
		if (dead_or_full(philo) == 1)
			break ;
		thinking_time(philo);
		if (philo->nbr_philo % 2 == 1 && philo->tm_think != -1)
			usleep(1000 * philo->tm_eat);
	}
	return (NULL);
}

int	manage_philo(t_data *data)
{
	int			i;
	pthread_t	philo_status;

	i = 0;
	if (pthread_create(&philo_status, NULL, &check_status, data->philo) != 0)
		destroy_all(data, "error create thread");
	while (i < data->nbr_philo)
	{
		if (pthread_create(&data->philo[i].thread, NULL,
				&philo_routine, &data->philo[i]) != 0)
			destroy_all(data, "error create thread");
		i++;
	}
	if (pthread_join(philo_status, NULL) != 0)
		destroy_all(data, "error join");
	i = 0;
	while (i < data->nbr_philo)
	{
		if (pthread_join(data->philo[i].thread, NULL) != 0)
			destroy_all(data, "error join");
		i++;
	}
	return (0);
}
