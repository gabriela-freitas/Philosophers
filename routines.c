/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gafreita <gafreita@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 19:16:40 by gafreita          #+#    #+#             */
/*   Updated: 2022/10/03 18:44:04 by gafreita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_sleep_think(t_philo *philo)
{
	long long	time_left;

	if (!check_if_alive())
		return ;
	print_message(philo->id, "is sleeping", BLUE);
	my_sleep(data()->time_to[p_sleep]);
	if (!check_if_alive())
		return ;
	print_message(philo->id, "is thinking", PURPLE);
	time_left = get_program_time(data()->eat_time[philo->id - 1]);
	if (data()->time_to[die] - time_left >= 10)
		my_sleep(1);
}

void	philo_die(int philo_id)
{
	print_message(philo_id, "is dead", RED);
	data()->all_alive = FALSE;
	pthread_mutex_unlock(&data()->mutex.is_alive);
}

/*	check whether all philosophers are alive and
	if the current is alive too
	i.e haven't passed enough time_to_die since last meal*/
int	check_if_alive(void)
{
	long long		eat_time;
	int				i;

	pthread_mutex_lock(&data()->mutex.is_alive);
	if (!data()->all_alive
		|| (data()->must_eat && data()->check_times_eat == data()->n_philos))
	{
		pthread_mutex_unlock(&data()->mutex.is_alive);
		return (FALSE);
	}
	i = -1;
	while (++i < data()->n_philos)
	{
		eat_time = data()->eat_time[i];
		if (eat_time && get_program_time(eat_time) > data()->time_to[die])
		{
			philo_die(i + 1);
			return (FALSE);
		}
	}
	pthread_mutex_unlock(&data()->mutex.is_alive);
	return (TRUE);
}
