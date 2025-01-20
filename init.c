/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngeny <ngeny@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 18:47:26 by ngeny             #+#    #+#             */
/*   Updated: 2025/01/17 13:48:02 by ngeny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_all(t_data *data, char **av)
{
	if (!init_data(data, av))
		return (0);
	if (!init_philo(data))
		return (0);
	return (1);
}

int	init_data(t_data *data, char **av)
{
	data->nbr_philo = ft_atoi(av[1]);
	data->tm_die = ft_atoi(av[2]);
	data->tm_eat = ft_atoi(av[3]);
	data->tm_sleep = ft_atoi(av[4]);
	data->is_dead = 0;
	if (av[5])
		data->nb_to_eat = ft_atoi(av[5]);
	else
		data->nb_to_eat = -1;
	pthread_mutex_init(&data->check_dead, NULL);
	pthread_mutex_init(&data->is_eating, NULL);
	pthread_mutex_init(&data->mtx_print, NULL);
	return (1);
}

void	init_philo_bis(int i, t_data *data)
{
	data->philo[i].id = i + 1;
	data->philo[i].nbr_philo = data->nbr_philo;
	data->philo[i].flag_die = &data->is_dead;
	data->philo[i].flag_eating = 0;
	data->philo[i].cnt_meal = 0;
	data->philo[i].start_time = get_time();
	data->philo[i].start_eat = get_time();
	data->philo[i].tm_die = data->tm_die;
	data->philo[i].tm_eat = data->tm_eat;
	data->philo[i].tm_sleep = data->tm_sleep;
	data->philo[i].nb_to_eat = data->nb_to_eat;
	data->philo[i].check_dead = &data->check_dead;
	data->philo[i].is_eating = &data->is_eating;
	data->philo[i].mtx_print = &data->mtx_print;
	data->philo[i].tm_think = -1;
	if (data->philo[i].tm_eat >= data->philo[i].tm_sleep)
		data->philo[i].tm_think = data->philo[i].tm_eat;
}

int	init_philo(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nbr_philo)
	{
		init_philo_bis(i, data);
		if (i < (i + data->nbr_philo - 1) % data->nbr_philo)
		{
			data->philo[i].r_fork = &data->mtx_forks[i];
			data->philo[i].l_fork
				= &data->mtx_forks[(i + data->nbr_philo - 1) % data->nbr_philo];
		}
		else
		{
			data->philo[i].l_fork = &data->mtx_forks[i];
			data->philo[i].r_fork
				= &data->mtx_forks[(i + data->nbr_philo - 1) % data->nbr_philo];
		}
		pthread_mutex_init(&data->mtx_forks[i], NULL);
		i++;
	}
	return (1);
}
