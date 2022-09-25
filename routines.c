/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gafreita <gafreita@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 19:16:40 by gafreita          #+#    #+#             */
/*   Updated: 2022/09/25 19:32:39 by gafreita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_eat(int philo_id)
{
	(void) philo_id;
	//check if right fork is avaible
	//check if left fork is avaible
	//if it is
		// print_message(philo_id, "is eating", GREEN);
		//usleep(data()->time_to[eat]);
		//philo_sleep()
	// else
		// return ;
}

//what if he dies during sleep? I need to be checking all the time if he died?
void	philo_sleep_think(int philo_id)
{
	(void) philo_id;
	// print_message(philo_id, "is sleeping", BLUE);
	// usleep(data()->time_to[p_sleep]);
	//starts thinking
	//return
}
