/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gafreita <gafreita@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 19:16:40 by gafreita          #+#    #+#             */
/*   Updated: 2022/09/27 17:50:11 by gafreita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_eat(t_philo *philo)
{
	int	right_fork;

	if (philo->id == 1)
		right_fork = data()->n_philos - 1;
	else
		right_fork = philo->id - 2;
	pthread_mutex_lock(&data()->mutex.forks[right_fork]); //check if right fork is avaible
	print_message(philo->id, "has taken a fork", GREY);
	pthread_mutex_lock(&data()->mutex.forks[philo->id - 1]); //check if left fork is avaible
	print_message(philo->id, "is eating", GREEN);
	philo->eat_time = my_sleep(data()->time_to[eat]);
	pthread_mutex_unlock(&data()->mutex.forks[philo->id - 1]);
	pthread_mutex_unlock(&data()->mutex.forks[right_fork]);
}

//what if he dies during sleep? I need to be checking all the time if he died?
void	philo_sleep_think(t_philo *philo)
{
	print_message(philo->id, "is sleeping", BLUE);
	my_sleep(data()->time_to[p_sleep]);
	print_message(philo->id, "is thinking", PURPLE);
}
