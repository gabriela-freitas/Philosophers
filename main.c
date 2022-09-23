/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gafreita <gafreita@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 18:32:02 by gafreita          #+#    #+#             */
/*   Updated: 2022/09/23 21:24:00 by gafreita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *arg)
{
	t_philo			*philo;

	philo = (t_philo *)arg;
	print_message(philo->id, "hello from here", PURPLE);
	return (NULL);
}

void	create_threads(void)
{
	int			i;
	pthread_t	*tid;
	t_philo		*philos;

	init_var(&philos, &tid);
	i = -1;
	gettimeofday(&(data()->start_time), NULL);
	while (++i < data()->philos)
	{
		philos[i].id = i + 1;
		pthread_create(&tid[i], NULL, routine, (void *)&philos[i]);
	}
	i = -1;
	while (++i < data()->philos)
		pthread_join(tid[i], NULL);
	free(data()->forks);
	free(philos);
	free(tid);
}

int	main(int ac, char **av)
{
	if (ac == 5 || ac == 6)
	{
		if (!parse_args(ac, av))
			return (0);
		create_threads();
	}
	else
	{
		printf("Usage:\n ./philosophers n_of_philo time_to_die time_to_eat ");
		printf("time_to_sleep [number_of_times_each_philosopher_must_eat]\n");
	}
}
