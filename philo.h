/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gafreita <gafreita@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 18:32:53 by gafreita          #+#    #+#             */
/*   Updated: 2022/10/02 13:12:33 by gafreita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdlib.h>
# include <unistd.h>
# define TRUE 1
# define FALSE 0
# define GREEN "\033[0;32m"
# define RED "\033[1;31m"
# define PURPLE "\033[1;35m"
# define BLUE "\033[1;36m"
# define YELLOW "\033[0;33m"
# define GREY "\033[0;40m"
# define COLOUR_END "\033[0m"

enum e_actions{
	die,
	eat,
	p_sleep
};

typedef struct s_philo
{
	int				id;
	int				meals;
}	t_philo;

typedef struct s_mutex
{
	pthread_mutex_t	*forks;
	pthread_mutex_t	print;
	pthread_mutex_t	check_times_eat;
	pthread_mutex_t	is_alive;
}	t_mutex;

typedef struct s_data
{
	int				n_philos;
	suseconds_t		time_to[3];
	int				must_eat;
	int				check_times_eat;
	long long		start_time;
	t_mutex			mutex;
	long long		*eat_time;
	int				all_alive;
}	t_data;

//parse.c
int				parse_args(int ac, char **av);
void			init_var(t_philo **philos, pthread_t **tid);
t_data			*data(void);

//libft.c
long			ft_atol(const char *str);
void			*ft_calloc(size_t count, size_t size);

//eat_routine.c
int				philo_eat(t_philo *philo);

//routines.c
void			philo_sleep_think(t_philo *philo);
void			philo_die(int philo_id);
int				check_if_alive(void);

//utils.c
void			print_message(int id, char *message, char *colour);
void			init_mutexes(void);
void			clean_program(void);
long long		get_program_time(long long start_time);
long long		my_sleep(long long time_to);

#endif
