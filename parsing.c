/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muzz <muzz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 15:22:11 by muzz              #+#    #+#             */
/*   Updated: 2025/05/19 15:23:28 by muzz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	parsing_input(int argc, char **argv, t_table *table)
{
	int		i;
	long	num[5];

	i = 0;
	while (++i < argc)
	{
		if (ft_is_numeric(argv[i]) < 0)
			return (ret_error(-1, "Error: need numeric input"));
		num[i - 1] = ft_atol(argv[i]);
	}
	if (put_value_to_table(table, num) < 0)
		return (-1);
	return (0);
}

int	put_value_to_table(t_table *table, long *num)
{
	table->num_philo = num[0];
	table->time_to_die = num[1];
	table->time_eat = num[2];
	table->time_sleep = num[3];
	if (table->num_need_eat >= 0)
		table->num_need_eat = num[4];
	if (table->num_philo > 200)
		return (ret_error(-1, "Error: exceed maximum 200 philos"));
	table->dead = 0;
	return (0);
}
