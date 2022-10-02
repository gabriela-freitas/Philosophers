/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gafreita <gafreita@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 20:10:33 by gafreita          #+#    #+#             */
/*   Updated: 2022/10/02 15:56:42 by gafreita         ###   ########.fr       */
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
	data()->n_philos = ft_atol(av[1]);
	data()->time_to[die] = ft_atol(av[2]);
	data()->time_to[eat] = ft_atol(av[3]);
	data()->time_to[p_sleep] = ft_atol(av[4]);
	if (ac == 6)
		data()->must_eat = ft_atol(av[5]);
	else
		data()->must_eat = 0;
	if (data()->n_philos <= 0 || data()->time_to[die] <= 0
		|| data()->time_to[eat] <= 0 || data()->time_to[p_sleep] <= 0)
	{
		printf("%sInvalid entry (must be only positive numbers)%s\n", RED, COLOUR_END);
		return (0);
	}
	return (1);
}

/*
check_times_eat will be incremented each time
a philosophers eats must_eat times (if this arg was given)
*/
void	init_var(t_philo **philos, pthread_t **tid)
{
	int	i;

	*philos = malloc(sizeof(t_philo) * data()->n_philos);
	*tid = malloc(sizeof(pthread_t) * data()->n_philos);
	i = -1;
	while (++i < data()->n_philos)
		(*philos)[i].meals = 0;
	(data()->eat_time) = malloc(sizeof(struct timeval) * data()->n_philos);
	i = -1;
	while (++i < data()->n_philos)
		data()->eat_time[i] = 0;
	data()->all_alive = TRUE;
	data()->check_times_eat = 0;
	init_mutexes();
}
