/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gafreita <gafreita@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 18:32:02 by gafreita          #+#    #+#             */
/*   Updated: 2022/10/02 15:55:24 by gafreita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


/*evaluation tests

# Do not test with more than 200 philosophers
# Do not test with time_to_die or time_to_eat or time_to_sleep under 60 ms
# ./philo 1 800 200 200, the philosopher should not eat and should die!
# ./philo 5 800 200 200, no one should die!
# ./philo 5 800 200 200 7
	 no one should die and the simulation should stop when all
	 the philosopher has eaten at least 7 times each.
# ./philo 4 410 200 200, no one should die!
# ./philo 4 310 200 100, a philosopher should die!
# Test with 2 philosophers and check the different times
	(a death delayed by more than 10 ms is unacceptable).
# Test with your values to check all the rules. Check if a philosopher
	dies at the right time if they don't steal forks, etc.
*/

void	*routine(void *arg)
{
	t_philo			*philo;

	philo = (t_philo *)arg;
	if (data()->n_philos == 1)
	{
		print_message(philo->id, "has taken first fork", GREY);
		my_sleep(data()->time_to[die]);
		philo_die(philo->id);
		return (FALSE);
	}
	pthread_mutex_lock(&data()->mutex.is_alive);
	data()->eat_time[philo->id - 1] = get_program_time(0);
	pthread_mutex_unlock(&data()->mutex.is_alive);
	while (TRUE)
	{
		if (!check_if_alive())
			break ;
		if (philo_eat(philo))
			philo_sleep_think(philo);
	}
	return (NULL);
}

void	create_threads(void)
{
	int				i;
	pthread_t		*tid;
	t_philo			*philos;

	init_var(&philos, &tid);
	i = -1;
	data()->start_time = get_program_time(0);
	while (++i < data()->n_philos)
	{
		philos[i].id = i + 1;
		pthread_create(&tid[i], NULL, routine, (void *)&philos[i]);
	}
	i = -1;
	while (++i < data()->n_philos)
		pthread_join(tid[i], NULL);
	clean_program();
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
		printf("  The program must take these args:\n");
		printf("\t%sn_of_philo%s\n", GREY, COLOUR_END);
		printf("\t%stime_to_die%s\n", RED, COLOUR_END);
		printf("\t%stime_to_eat%s\n", GREEN, COLOUR_END);
		printf("\t%stime_to_sleep%s\n\tOptional: %s", BLUE, COLOUR_END, YELLOW);
		printf("number_of_times_each_philosopher_must_eat\n%s", COLOUR_END);
	}
}
