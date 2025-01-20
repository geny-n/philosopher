/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dead_or_alive.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngeny <ngeny@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 16:54:07 by ngeny             #+#    #+#             */
/*   Updated: 2025/01/16 20:32:22 by ngeny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philosopher_dead(t_philo *philo, int tm_die)
{
	pthread_mutex_lock(philo->is_eating);
	if ((philo->start_eat + tm_die) < get_time() && philo->flag_eating == 0)
	{
		pthread_mutex_unlock(philo->is_eating);
		return (1);
	}	
	pthread_mutex_unlock(philo->is_eating);
	return (0);
}

int	check_dead(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo[0].nbr_philo)
	{
		if (philosopher_dead(&philo[i], philo[i].tm_die))
		{
			mail_print (philo, "died");
			pthread_mutex_lock(philo[0].check_dead);
			*philo->flag_die = 1;
			pthread_mutex_unlock(philo[0].check_dead);
			return (1);
		}
		i++;
	}
	return (0);
}

int	check_full(t_philo *philo)
{
	int	i;
	int	philo_full;

	i = 0;
	philo_full = 0;
	if (philo[0].nb_to_eat == -1)
		return (0);
	while (i < philo[0].nbr_philo)
	{
		pthread_mutex_lock(philo[i].is_eating);
		if (philo[i].cnt_meal >= philo[0].nb_to_eat)
			philo_full++;
		pthread_mutex_unlock(philo[i].is_eating);
		i++;
	}
	if (philo_full == philo[0].nbr_philo)
	{
		pthread_mutex_lock(philo[0].check_dead);
		*philo->flag_die = 1;
		pthread_mutex_unlock(philo[0].check_dead);
		return (1);
	}
	return (0);
}

void	*check_status(void *status_th)
{
	t_philo	*philo;

	philo = (t_philo *)status_th;
	while (1)
	{
		usleep(50);
		if (check_dead(philo) == 1 || check_full(philo) == 1)
			break ;
	}
	return (status_th);
}

int	dead_or_full(t_philo *philo)
{
	pthread_mutex_lock(philo->check_dead);
	if (*philo->flag_die == 1)
	{
		pthread_mutex_unlock(philo->check_dead);
		return (1);
	}
	pthread_mutex_unlock(philo->check_dead);
	return (0);
}
