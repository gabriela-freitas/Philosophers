/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gafreita <gafreita@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 19:16:40 by gafreita          #+#    #+#             */
/*   Updated: 2022/09/29 17:19:29 by gafreita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	decide_fork(t_philo *philo, int *first, int *second);

//alternar se for par ou impar (comecar pela direita ou esquerda)
int	philo_eat(t_philo *philo)
{
	int	first;
	int	second;

	decide_fork(philo, &first, &second);
	pthread_mutex_lock(&data()->mutex.forks[first]);
	print_message(philo->id, "has taken a fork", GREY);
	pthread_mutex_lock(&data()->mutex.forks[second]);
	print_message(philo->id, "is eating", GREEN);
	my_sleep(data()->time_to[eat]);
	gettimeofday(&data()->eat_time[philo->id - 1], NULL);
	pthread_mutex_unlock(&data()->mutex.forks[second]);
	pthread_mutex_unlock(&data()->mutex.forks[first]);
	return (TRUE);
}

void	philo_sleep_think(t_philo *philo)
{
	struct timeval	start;

	gettimeofday(&start, NULL);
	if (!check_if_alive(philo))
		return ;
	print_message(philo->id, "is sleeping", BLUE);
	while (get_program_time(start) < data()->time_to[p_sleep])
	{
		if (get_program_time(start) > data()->time_to[die])
		{
			philo_die(philo);
			return ;
		}
	}
	if (!check_if_alive(philo))
		return ;
	print_message(philo->id, "is thinking", PURPLE);
}

void	philo_die(t_philo *philo)
{
	print_message(philo->id, "is dead", RED);
	pthread_mutex_lock(&data()->mutex.is_alive);
	data()->all_alive = FALSE;
	pthread_mutex_unlock(&data()->mutex.is_alive);
}

/*	check whether all philosophers are alive and
	if the current is alive too
	i.e haven't passed enough time_to_die since last meal*/
int	check_if_alive(t_philo *philo)
{
	struct timeval	eat_time;

	eat_time = data()->eat_time[philo->id - 1];
	pthread_mutex_lock(&data()->mutex.is_alive);
	if (!data()->all_alive)
	{
		pthread_mutex_unlock(&data()->mutex.is_alive);
		return (FALSE);
	}
	pthread_mutex_unlock(&data()->mutex.is_alive);
	if (get_program_time(eat_time) > data()->time_to[die])
	{
		print_message(philo->id, "is dead", RED);
		return (FALSE);
	}
	return (TRUE);
}

static void	decide_fork(t_philo *philo, int *first, int *second)
{
	int	right_fork;

	if (philo->id == 1)
	right_fork = data()->n_philos - 1;
	else
		right_fork = philo->id - 2;
	if (philo->id % 2 == 0)
	{
		*first = right_fork;
		*second = philo->id - 1;
	}
	else
	{
		*first = philo->id - 1;
		*second = right_fork;
	}
}
