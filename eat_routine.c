/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat_routine.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gafreita <gafreita@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 13:10:36 by gafreita          #+#    #+#             */
/*   Updated: 2022/10/02 15:44:32 by gafreita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	decide_fork(t_philo *philo, int *first, int *second);
static void	eat_routine(t_philo *philo);

//alternar se for par ou impar (comecar pela direita ou esquerda)
int	philo_eat(t_philo *philo)
{
	int	forks[2];

	decide_fork(philo, &forks[0], &forks[1]);
	pthread_mutex_lock(&data()->mutex.forks[forks[0]]);
	if (!check_if_alive())
	{
		pthread_mutex_unlock(&data()->mutex.forks[forks[0]]);
		return (FALSE);
	}
	print_message(philo->id, "has taken first fork", GREY);
	pthread_mutex_lock(&data()->mutex.forks[forks[1]]);
	if (!check_if_alive())
	{
		pthread_mutex_unlock(&data()->mutex.forks[forks[1]]);
		pthread_mutex_unlock(&data()->mutex.forks[forks[0]]);
		return (FALSE);
	}
	print_message(philo->id, "has taken second fork", GREY);
	eat_routine(philo);
	pthread_mutex_unlock(&data()->mutex.forks[forks[1]]);
	pthread_mutex_unlock(&data()->mutex.forks[forks[0]]);
	return (TRUE);
}

static void	eat_routine(t_philo *philo)
{
	pthread_mutex_lock(&data()->mutex.is_alive);
	data()->eat_time[philo->id - 1] = get_program_time(0);
	pthread_mutex_unlock(&data()->mutex.is_alive);
	print_message(philo->id, "is eating", GREEN);
	my_sleep(data()->time_to[eat]);
	if (++philo->meals == data()->must_eat)
	{
		pthread_mutex_lock(&data()->mutex.is_alive);
		data()->check_times_eat++;
		pthread_mutex_unlock(&data()->mutex.is_alive);
	}
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
