/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gafreita <gafreita@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 18:32:53 by gafreita          #+#    #+#             */
/*   Updated: 2022/09/16 19:25:04 by gafreita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct	s_data
{
	int			philos;
	suseconds_t	time_to[3];
	suseconds_t	time_to_eat;
	suseconds_t	time_to_sleep;
	int			must_eat;
	suseconds_t	start_time;
}	t_data;

long	ft_atol(const char *str);
t_data	*data(void);

#endif
