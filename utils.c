/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gafreita <gafreita@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 20:36:36 by gafreita          #+#    #+#             */
/*   Updated: 2022/09/28 20:49:25 by gafreita         ###   ########.fr       */
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

/*returns program_time as current time - start_time given as arg*/
suseconds_t	get_program_time(struct timeval start_time)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	time.tv_usec -= start_time.tv_usec;
	return (time.tv_usec);
}

/*My version of usleep, returns the start time + time asleep*/
suseconds_t	my_sleep(suseconds_t time_to)
{
	struct timeval	start;

	gettimeofday(&start, NULL);
	while (get_program_time(start) < time_to)
		;
	return (start.tv_sec + time_to);
}
