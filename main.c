/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngeny <ngeny@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 18:36:52 by ngeny             #+#    #+#             */
/*   Updated: 2025/01/17 13:48:48 by ngeny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_data			data;

	if ((ac != 5 && ac != 6) || check_number(ac, av))
		return (error("ERROR arg", 1));
	if (!init_all(&data, av))
		return (0);
	manage_philo(&data);
	destroy_all(&data, NULL);
	return (0);
}
