/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abin-moh <abin-moh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 15:18:45 by muzz              #+#    #+#             */
/*   Updated: 2025/05/25 15:29:24 by abin-moh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(&philo->go);
	if (philo->table->num_philo == 1)
		return (special_case(philo));
	while (!is_dead(philo))
	{
		if (philo->id % 2 == 0)
    		usleep(1000);
		print_status(philo, "is thinking");
		if (is_dead(philo))
			break ;
		if (philo->l_fork < philo->r_fork)
		{
			pthread_mutex_lock(philo->l_fork);
			print_status(philo, "has taken a fork");
			pthread_mutex_lock(philo->r_fork);
			print_status(philo, "has taken a fork");
		}
		else
		{
			pthread_mutex_lock(philo->r_fork);
			print_status(philo, "has taken a fork");
			pthread_mutex_lock(philo->l_fork);
			print_status(philo, "has taken a fork");
		}
		eating(philo);
		unlock_both_forks(philo);
		sleeping(philo);
	}
	pthread_mutex_unlock(&philo->go);
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
		usleep(1000);
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
