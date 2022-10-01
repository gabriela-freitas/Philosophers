/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gafreita <gafreita@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 20:36:36 by gafreita          #+#    #+#             */
/*   Updated: 2022/10/01 21:16:58 by gafreita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//FIXME: Am I dealing right with the time stamps? Can it be more exact?
/*messages:
◦ timestamp_in_ms X has taken a fork
◦ timestamp_in_ms X is eating
◦ timestamp_in_ms X is sleeping
◦ timestamp_in_ms X is thinking
◦ timestamp_in_ms X died*/

//will eating, sleeping, thinking be consecutive? I think so

void	print_message(int id, char *message, char *colour)
{
	suseconds_t	time;

	time = get_program_time(data()->start_time);
	pthread_mutex_lock(&data()->mutex.print);
	printf("%s", colour);
	printf("[%ld ms] %d %s", time, id, message);
	printf("%s\n", COLOUR_END);
	pthread_mutex_unlock(&data()->mutex.print);
}

/*initializes mutexes*/
void	init_mutexes(void)
{
	int	i;

	pthread_mutex_init(&data()->mutex.print, NULL);
	pthread_mutex_init(&data()->mutex.is_alive, NULL);
	pthread_mutex_init(&data()->mutex.check_times_eat, NULL);
	// pthread_mutex_init(&data()->mutex.init, NULL);
	data()->mutex.forks = malloc(sizeof(pthread_mutex_t) * data()->n_philos);
	i = -1;
	while (++i < data()->n_philos)
		pthread_mutex_init(&data()->mutex.forks[i], NULL);
}

/*destroy mutexes*/
void	clean_program(void)
{
	int	i;

	pthread_mutex_destroy(&data()->mutex.print);
	i = -1;
	while (++i < data()->n_philos)
		pthread_mutex_destroy(&data()->mutex.forks[i]);
}

/*returns program_time as current time - start_time given as arg
in miliseconds*/
long long	get_program_time(long long start_time)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000 + time.tv_usec / 1000) - start_time);
}

/*My version of usleep, returns the start time + time asleep*/
long long	my_sleep(long long time_to)
{
	struct timeval	time;
	long long		start;

	gettimeofday(&time, NULL);
	start = time.tv_sec * 1000 + time.tv_usec / 1000;
	while (get_program_time(start) <= time_to)
	{
		if (!check_if_alive())
			return (0);
	}
	return (start + time_to);
}
