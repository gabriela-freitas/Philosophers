/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gafreita <gafreita@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 18:32:02 by gafreita          #+#    #+#             */
/*   Updated: 2022/09/16 19:23:21 by gafreita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	if (ac == 5 || ac == 6)
	{
		data()->philos = ft_atol(av[1]);
		data()->time_to_die = ft_atol(av[2]);
		data()->time_to_eat = ft_atol(av[3]);
		data()->time_to_sleep = ft_atol(av[4]);
		if (ac == 6)
			data()->must_eat = ft_atol(av[5]);
		else
			data()->must_eat = -1;
	}
	else
	{
		printf("Usage ./philosophers number_of_philosophers time_to_die time_to_eat ");
		printf("time_to_sleep [number_of_times_each_philosopher_must_eat]\n");
	}
}
