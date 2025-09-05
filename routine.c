/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melayyad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 10:54:35 by melayyad          #+#    #+#             */
/*   Updated: 2025/08/29 10:54:43 by melayyad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_forks(t_philo *p)
{
	if (death_flag(p->table, 0))
		return ;
	if (p->id % 2)
	{
		pthread_mutex_lock(&p->table->forks[p->left_fork]);
		print_status(p, "has taken a fork");
		pthread_mutex_lock(&p->table->forks[p->right_fork]);
		print_status(p, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(&p->table->forks[p->right_fork]);
		print_status(p, "has taken a fork");
		pthread_mutex_lock(&p->table->forks[p->left_fork]);
		print_status(p, "has taken a fork");
	}
}

void	eat(t_philo *p)
{
	if (death_flag(p->table, 0))
		return ;
	print_status(p, "is eating");
	p->last_meal = get_time_ms();
	p->meals_eaten++;
	if (p->table->must_eat_count != -1
		&& p->meals_eaten >= p->table->must_eat_count)
		p->is_full = 1;
	ft_usleep(p->table->time_to_eat, p->table);
}

void	put_forks(t_philo *p)
{
	pthread_mutex_unlock(&p->table->forks[p->left_fork]);
	pthread_mutex_unlock(&p->table->forks[p->right_fork]);
}

void	sleep_and_think(t_philo *p)
{
	if (death_flag(p->table, 0))
		return ;
	print_status(p, "is sleeping");
	ft_usleep(p->table->time_to_sleep, p->table);
	print_status(p, "is thinking");
	ft_usleep(p->table->time_to_think, p->table);
}

void	*routine(void *arg)
{
	t_philo	*p;

	p = (t_philo *)arg;
	p->last_meal = p->table->start_time;
	print_status(p, "is thinking");
	if (p->id % 2 == 0)
		usleep(1000);
	while (!death_flag(p->table, 0))
	{
		take_forks(p);
		eat(p);
		put_forks(p);
		sleep_and_think(p);
	}
	return (NULL);
}
