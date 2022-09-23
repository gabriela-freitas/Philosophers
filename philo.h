/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gafreita <gafreita@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 18:32:53 by gafreita          #+#    #+#             */
/*   Updated: 2022/09/23 21:33:52 by gafreita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdlib.h>
# include <unistd.h>
# define GREEN "\033[0;32m"
# define RED "\033[1;31m"
# define PURPLE "\033[1;35m"
# define BLUE "\033[1;37m"
# define YELLOW "\033[0;33m"
# define GREY "\033[0;40m"
# define COLOUR_END "\033[0m"

enum e_actions{
	die,
	eat,
	p_sleep
};

enum e_forks
{
	not_avaible,
	avaible
};

typedef struct s_philo
{
	int	id;
	int	meals;
}	t_philo;

typedef struct s_data
{
	int				n_philos;
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

//utils.c
void	print_message(int id, char *message, char *colour);
#endif
