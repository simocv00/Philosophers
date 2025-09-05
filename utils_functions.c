/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melayyad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 18:43:12 by melayyad          #+#    #+#             */
/*   Updated: 2025/08/26 18:46:32 by melayyad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	clean_step(t_philo *philo, t_table *table)
{
	int	i;

	i = 0;
	if (table)
	{
		if (table->forks)
		{
			while (i < table->n_philos)
			{
				pthread_mutex_destroy(&table->forks[i]);
				i++;
			}
			pthread_mutex_destroy(&table->print_mutex);
			pthread_mutex_destroy(&table->death);
			free(table->forks);
			free(table);
		}
	}
	if (philo)
		free(philo);
}

long	get_timestamp(long start_time)
{
	struct timeval	tv;
	long			current_time;

	gettimeofday(&tv, NULL);
	current_time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (current_time - start_time);
}

void	print_status(t_philo *p, char *status)
{
	static int	flg = 1;

	pthread_mutex_lock(&p->table->print_mutex);
	if (flg)
		printf("%ld %d %s\n", get_timestamp(p->table->start_time), p->id,
			status);
	if (status[0] == 'd')
		flg = 0;
	pthread_mutex_unlock(&p->table->print_mutex);
}

void	ft_usleep(long ms, t_table *data)
{
	long	start;

	start = get_time_ms();
	while (!death_flag(data, 0) && (get_time_ms() - start) < ms)
		usleep(100);
}

long	get_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}
