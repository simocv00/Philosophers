/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melayyad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 18:47:34 by melayyad          #+#    #+#             */
/*   Updated: 2025/08/26 18:47:41 by melayyad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_forks(pthread_mutex_t *forks, long n, int *flag)
{
	long	i;

	i = 0;
	while (i < n)
	{
		if (pthread_mutex_init(&forks[i], NULL))
		{
			if (i < 0)
			{
				while (i > 0)
				{
					pthread_mutex_destroy(&forks[i]);
					i--;
				}
				return ((*flag) = 1, printf("Erorr\n"), (void)0);
			}
		}
		i++;
	}
}

static t_table	*alloc_and_fill(char **av)
{
	t_table	*tab;

	tab = malloc(sizeof(t_table));
	if (!tab)
		return (print_error("Malloc failed\n"), NULL);
	tab->n_philos = ft_atol(av[1]);
	tab->time_to_die = ft_atol(av[2]);
	tab->time_to_eat = ft_atol(av[3]);
	tab->time_to_sleep = ft_atol(av[4]);
	tab->time_to_think = 0;
	if (tab->n_philos % 2 && tab->time_to_eat >= tab->time_to_sleep)
		tab->time_to_think = tab->time_to_eat - tab->time_to_sleep + 10;
	tab->must_eat_count = ft_atol(av[5]);
	tab->stop = 0;
	tab->start_time = -1;
	return (tab);
}

static int	check_and_alloc_forks(t_table *tab)
{
	if (tab->n_philos <= 0 || tab->time_to_die <= 0 || tab->time_to_eat <= 0
		|| tab->time_to_sleep <= 0 || tab->must_eat_count == -2)
		return (free(tab), print_input_rules());
	tab->forks = malloc(sizeof(pthread_mutex_t) * tab->n_philos);
	if (!tab->forks)
		return (print_error("Malloc failed\n"), free(tab), 1);
	return (0);
}

t_table	*init_table(char **av)
{
	t_table	*tab;
	int		error;

	tab = alloc_and_fill(av);
	if (!tab)
		return (NULL);
	if (check_and_alloc_forks(tab))
		return (NULL);
	error = 0;
	if (pthread_mutex_init(&tab->print_mutex, NULL)
		|| pthread_mutex_init(&tab->death, NULL))
		return (free(tab), print_error("pthread_mutex_init failed\n"), NULL);
	set_forks(tab->forks, tab->n_philos, &error);
	if (error)
		return (free(tab), NULL);
	return (tab);
}

//-----------------------philo----------------

void	create_philos(t_table *data, t_philo *tflsyf)
{
	int	i;

	i = 0;
	while (i < data->n_philos)
	{
		tflsyf[i].id = i + 1;
		tflsyf[i].left_fork = i;
		tflsyf[i].right_fork = (i + 1) % data->n_philos;
		tflsyf[i].last_meal = 0;
		tflsyf[i].meals_eaten = 0;
		tflsyf[i].table = data;
		tflsyf[i].is_full = 0;
		i++;
	}
}
