/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngeny <ngeny@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 17:36:36 by ngeny             #+#    #+#             */
/*   Updated: 2025/01/17 13:48:24 by ngeny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *nptr)
{
	int	i;
	int	sign;
	int	nb;

	i = 0;
	sign = 1;
	nb = 0;
	while (nptr[i] == 32 || (nptr[i] >= 9 && nptr[i] <= 13))
	{
		i++;
	}
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			sign = -sign;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		nb = nb * 10 + (nptr[i] - '0');
		i++;
	}
	return (nb * sign);
}

int	check_number(int argc, char **argv)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (ft_atoi(argv[i]) > 2147483647 || ft_atoi(argv[i]) < 1)
			return (1);
		i++;
	}
	if (ft_atoi(argv[1]) > 0)
		return (0);
	return (0);
}

long long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	to_wait(long long wait_tm, t_philo *philo)
{
	long long	start;

	start = get_time();
	while ((get_time() - start) < wait_tm)
	{
		if (dead_or_full(philo) == 1)
			return ;
		usleep(1000);
	}
}

void	mail_print(t_philo *philo, char *msg)
{
	long long	time;

	time = get_time() - philo->start_time;
	pthread_mutex_lock(philo->mtx_print);
	pthread_mutex_lock(philo->check_dead);
	if (*philo->flag_die == 0)
		printf("%lld %d %s\n", time, philo->id, msg);
	pthread_mutex_unlock(philo->check_dead);
	pthread_mutex_unlock(philo->mtx_print);
}
