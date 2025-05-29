/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abin-moh <abin-moh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 15:18:45 by muzz              #+#    #+#             */
/*   Updated: 2025/05/29 16:42:23 by abin-moh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	sim_start_delay(long start_time)
{
	while (get_time_in_ms() < start_time)
		usleep(50);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(&philo->mutex_meal);
	philo->last_meal_time = philo->table->time_start;
	pthread_mutex_unlock(&philo->mutex_meal);
	sim_start_delay(philo->table->time_start);
	if (philo->table->num_philo == 1)
		return (special_case(philo));
	if (philo->id % 2 == 0)
    	thinking(philo);
	while (!is_dead(philo))
	{
		if (is_dead(philo))
			break ;
		// if (philo->l_fork < philo->r_fork)
		// {
		// 	pthread_mutex_lock(philo->l_fork);
		// 	print_status(philo, "has taken a fork", 0);
		// 	if (is_dead(philo))
		// 	{
		// 		pthread_mutex_unlock(philo->l_fork);
		// 		break ;
        // 	}
		// 	pthread_mutex_lock(philo->r_fork);
		// 	print_status(philo, "has taken a fork", 0);
		// }
		// else
		// {
		// 	pthread_mutex_lock(philo->r_fork);
		// 	print_status(philo, "has taken a fork", 0);
		// 	if (is_dead(philo))
		// 	{
		// 		pthread_mutex_unlock(philo->r_fork);
		// 		break ;
        // 	}
		// 	pthread_mutex_lock(philo->l_fork);
		// 	print_status(philo, "has taken a fork", 0);
		// }
		eating(philo);
		sleeping(philo);
		thinking(philo);
	}
	return (NULL);
}

void	*monitor_routine(void *arg)
{
	t_table	*table;
	int		i;

	table = (t_table *)arg;
	sim_start_delay(table->time_start);
	while (1)
	{
		usleep(1000);
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
