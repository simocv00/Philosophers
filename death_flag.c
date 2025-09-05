/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death_flag.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melayyad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 14:31:38 by melayyad          #+#    #+#             */
/*   Updated: 2025/09/01 14:32:16 by melayyad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	death_flag(t_table *tab, int flag)
{
	int	value;

	if (!tab)
		return (1);
	pthread_mutex_lock(&tab->death);
	if (flag)
		tab->stop = 1;
	value = tab->stop;
	pthread_mutex_unlock(&tab->death);
	return (value);
}
