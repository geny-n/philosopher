/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngeny <ngeny@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 17:27:53 by ngeny             #+#    #+#             */
/*   Updated: 2025/01/17 13:47:44 by ngeny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy_all(t_data *data, char *msg)
{
	int	i;

	i = 0;
	if (!data)
		return ;
	if (msg)
		printf ("%s\n", msg);
	pthread_mutex_destroy(&data->mtx_print);
	pthread_mutex_destroy(&data->check_dead);
	pthread_mutex_destroy(&data->is_eating);
	while (i < data->philo[0].nbr_philo)
	{
		pthread_mutex_destroy(&data->mtx_forks[i]);
		i++;
	}
}

int	error(char *msg, int val)
{
	printf("%s\n", msg);
	return (val);
}
