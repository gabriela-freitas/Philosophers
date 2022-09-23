/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gafreita <gafreita@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 20:36:36 by gafreita          #+#    #+#             */
/*   Updated: 2022/09/23 21:22:01 by gafreita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_message(int id, char *message, char *colour)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	time.tv_usec -= data()->start_time.tv_usec;
	printf("%s", colour);
	printf("[%ld ms] %d %s", time.tv_usec, id, message);
	printf("%s\n", COLOUR_END);
}
