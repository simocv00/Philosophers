/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melayyad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 12:41:02 by melayyad          #+#    #+#             */
/*   Updated: 2025/08/29 12:41:03 by melayyad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philo	t_philo;

typedef struct s_table
{
	long				n_philos;
	long				time_to_die;
	long				time_to_eat;
	long				time_to_sleep;
	long				time_to_think;
	int					must_eat_count;
	int					stop;
	_Atomic long		start_time;

	pthread_mutex_t		*forks;
	pthread_mutex_t		death;
	pthread_mutex_t		print_mutex;
	t_philo				*philos;
}						t_table;

typedef struct s_philo
{
	int						id;
	int						left_fork;
	int						right_fork;
	_Atomic unsigned long	last_meal;
	_Atomic int				meals_eaten;
	_Atomic int				is_full;
	pthread_t				thread_id;
	t_table					*table;
}						t_philo;

int						death_flag(t_table *tab, int flag);
long					ft_atol(char *str);
int						print_error(char *str);
void					clean_step(t_philo *philo, t_table *table);
void					create_philos(t_table *data, t_philo *tflsyf);
t_table					*init_table(char **av);
void					print_status(t_philo *philo, char *status);
long					get_time_ms(void);
void					ft_usleep(long ms, t_table *data);
void					*routine(void *arg);
void					take_forks(t_philo *p);
void					eat(t_philo *p);
void					put_forks(t_philo *p);
void					sleep_and_think(t_philo *p);
void					monitor(t_philo *ph, t_table *data);
long					get_timestamp(long start_time);
int						print_input_rules(void);

#endif
