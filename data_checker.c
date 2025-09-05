/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_checker.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melayyad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 11:25:32 by melayyad          #+#    #+#             */
/*   Updated: 2025/08/29 11:25:36 by melayyad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	print_input_rules(void)
{
	printf("\033[31m⚠️  Invalid input!\033[0m\n\n");
	printf("\033[32mCorrect usage:\033[0m\n");
	printf("./philo number_of_philos time_to_die time_to_eat "
		"time_to_sleep [number_of_times_each_philo_must_eat]\n\n");
	printf("\033[33mRules:\033[0m\n");
	printf(" - \033[32mnumber_of_philos\033[0m: integer > 0\n");
	printf(" - \033[32mtime_to_die\033[0m: time in ms (> 0)\n");
	printf(" - \033[32mtime_to_eat\033[0m: time in ms (> 0)\n");
	printf(" - \033[32mtime_to_sleep\033[0m: time in ms (> 0)\n");
	printf(" - \033[32mnumber_of_times_each_philo_must_eat\033[0m: optional,"
		"integer > 0\n");
	return (1);
}

int	ft_isspace(int c)
{
	c = (unsigned char)c;
	if (c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r'
		|| c == ' ')
		return (1);
	return (0);
}

int	valid_input(char **str)
{
	while ((**str == '\t' || **str == '\n' || **str == '\v' || **str == '\f'
			|| **str == '\r' || **str == ' '))
		(*str)++;
	if (**str == '-')
		return (1);
	return (0);
}

long	ft_atol(char *str)
{
	int				i;
	unsigned long	n;

	i = 0;
	n = 0;
	if (!str || !str[i])
		return (-1);
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
		return (-2);
	while (str[i] >= '0' && str[i] <= '9')
	{
		n = n * 10 + (str[i] - '0');
		if ((n > LONG_MAX))
			return (-2);
		i++;
	}
	if ((str[i]) && (!ft_isspace(str[i])))
	{
		return (-2);
	}
	return (n);
}
