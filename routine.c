/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abin-moh <abin-moh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 15:18:45 by muzz              #+#    #+#             */
/*   Updated: 2025/05/20 12:28:13 by abin-moh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	take_fork_right_first(t_philo *philo)
{
	take_fork(philo, "right");
	if (is_dead(philo))
	{
		pthread_mutex_unlock(philo->l_fork);
		return (-1);
	}
	take_fork(philo, "left");
	return (0);
}

int	take_fork_left_first(t_philo *philo)
{
	take_fork(philo, "left");
	if (is_dead(philo))
	{
		pthread_mutex_unlock(philo->l_fork);
		return (-1);
	}
	take_fork(philo, "right");
	return (0);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->table->num_philo == 1)
		return (special_case(philo));
	while (!is_dead(philo))
	{
		print_status(philo, "is thinking");
		if (is_dead(philo))
			break ;
		if (philo->id % 2 == 0)
		{
			if (take_fork_left_first(philo) < 0)
				break ;
		}
		else
		{
			if (take_fork_right_first(philo) < 0)
				break ;
		}
		eating(philo);
		unlock_both_forks(philo);
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
		usleep(100);
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
