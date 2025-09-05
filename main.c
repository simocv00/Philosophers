/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melayyad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 11:50:32 by melayyad          #+#    #+#             */
/*   Updated: 2025/08/29 11:50:34 by melayyad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	print_error(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
		write(2, &str[i++], 1);
	return (1);
}

void	monitor(t_philo *ph, t_table *data)
{
	int (i), (count);
	unsigned long (currnt_time);
	i = 0;
	while (1)
	{
		i = 0;
		currnt_time = get_time_ms();
		count = 0;
		while (i < data->n_philos)
		{
			if (currnt_time >= ph[i].last_meal + data->time_to_die)
			{
				print_status((&ph[i]), "died");
				death_flag(data, 1);
				break ;
			}
			if (ph[i].is_full)
				count++;
			i++;
		}
		if (data->must_eat_count != -1 && count == data->n_philos)
			death_flag(data, 1);
		if (death_flag(data, 0))
			break ;
	}
}

void	philo_one(t_philo *ph, t_table *tab)
{
	pthread_mutex_lock(&tab->forks[ph->left_fork]);
	print_status(ph, "has taken a fork");
	ft_usleep(ph->table->time_to_die, ph->table);
	pthread_mutex_unlock(&tab->forks[ph->left_fork]);
	print_status(ph, "died");
}

int	starting_program(t_philo *ph, t_table *data)
{
	int	i;

	i = 0;
	while (i < data->n_philos)
	{
		if (pthread_create(&ph[i].thread_id, NULL, routine, &ph[i]))
		{
			if (i > 0)
			{
				while (i > 0)
					pthread_join(ph[i--].thread_id, NULL);
				clean_step(ph, data);
				return (print_error("Pthread Create failed !\n"));
			}
		}
		i++;
	}
	usleep(1000);
	monitor(ph, data);
	i = 0;
	while (i < data->n_philos)
		pthread_join(ph[i++].thread_id, NULL);
	return (0);
}

int	main(int ac, char **av)
{
	t_table	*data;
	t_philo	*ph;

	if (ac != 5 && ac != 6)
		return (print_input_rules());
	data = init_table(av);
	if (!data)
		return (1);
	ph = malloc(sizeof(t_philo) * data->n_philos);
	if (!ph)
		return (clean_step(NULL, data), print_error("Malloc failed !\n"));
	create_philos(data, ph);
	data->start_time = get_time_ms();
	if (data->n_philos == 1)
		philo_one(ph, data);
	else
	{
		if (data->must_eat_count != 0)
			if (starting_program(ph, data))
				return (1);
	}
	return (clean_step(ph, data), 0);
}
