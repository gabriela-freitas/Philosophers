/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gafreita <gafreita@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 20:10:33 by gafreita          #+#    #+#             */
/*   Updated: 2022/09/23 21:04:56 by gafreita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_data	*data(void)
{
	static t_data	data;

	return (&data);
}

int	parse_args(int ac, char **av)
{
	data()->philos = ft_atol(av[1]);
	data()->time_to[die] = ft_atol(av[2]);
	data()->time_to[eat] = ft_atol(av[3]);
	data()->time_to[p_sleep] = ft_atol(av[4]);
	if (ac == 6)
		data()->must_eat = ft_atol(av[5]);
	else
		data()->must_eat = -1;
	if (data()->philos <= 0 || data()->time_to[die] <= 0
		|| data()->time_to[eat] <= 0 || data()->time_to[p_sleep] <= 0)
	{
		printf("invalid entry (must be numbers > 0)\n");
		return (0);
	}
	return (1);
}

void	init_var(t_philo **philos, pthread_t **tid)
{
	int	i;

	(data()->forks) = ft_calloc(sizeof(int), data()->philos);
	*philos = malloc(sizeof(t_philo) * data()->philos);
	*tid = malloc(sizeof(pthread_t) * data()->philos);
	i = -1;
	while (++i < data()->philos)
		(*philos)[i].meals = 0;
}
