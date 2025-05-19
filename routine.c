/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muzz <muzz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 15:18:45 by muzz              #+#    #+#             */
/*   Updated: 2025/05/19 15:24:34 by muzz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->table->num_philo == 1)
		return (special_case(philo));
	if (philo->id % 2 == 0)
		usleep(1000);
	while (!is_dead(philo))
	{
		print_status(philo, "is thinking");
		if (is_dead(philo))
			break ;
		take_fork(philo, "left");
		if (is_dead(philo))
		{
			pthread_mutex_unlock(philo->l_fork);
			break ;
		}
		take_fork(philo, "right");
		eating(philo);
		pthread_mutex_unlock(philo->l_fork);
		pthread_mutex_unlock(philo->r_fork);
		sleeping(philo);
	}
	return (NULL);
}

void	*monitor_routine(void *arg)
{
	t_table	*table;
	int		i;

	table = (t_table *)arg;
	while (1)
	{
		i = -1;
		while (++i < table->num_philo)
			if (check_dead(table, i) < 0)
				return (NULL);
		if (table->num_need_eat > 0)
		{
			if (table->num_philo == check_all_finished(table))
			{
				all_philo_is_full(table);
				return (NULL);
			}
		}
		usleep(200);
	}
	return (NULL);
}

void	wait_thread(t_philo *philo)
{
	int	i;

	i = -1;
	while (++i < philo->table->num_philo)
	{
		pthread_join(philo[i].thread, NULL);
	}
}
