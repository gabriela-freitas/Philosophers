/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gafreita <gafreita@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 18:32:53 by gafreita          #+#    #+#             */
/*   Updated: 2022/09/23 20:29:32 by gafreita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdlib.h>
# include <unistd.h>

enum e_actions{
	die,
	eat,
	p_sleep
};

typedef struct s_philo
{
	int	id;
	int	meals;
}	t_philo;

typedef struct s_data
{
	int				philos;
	int				*forks;
	suseconds_t		time_to[3];
	int				must_eat;
	struct timeval	start_time;
}	t_data;

//parse.c
int		parse_args(int ac, char **av);
void	init_var(t_philo **philos, pthread_t **tid);
t_data	*data(void);

//libft.c
long	ft_atol(const char *str);
void	*ft_calloc(size_t count, size_t size);

#endif
