/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   activities.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abin-moh <abin-moh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 15:25:35 by muzz              #+#    #+#             */
/*   Updated: 2025/05/20 12:29:22 by abin-moh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_fork(t_philo *philo, char *s)
{
	if (ft_strcmp(s, "left"))
	{
		pthread_mutex_lock(philo->l_fork);
		print_status(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(philo->r_fork);
		print_status(philo, "has taken a fork");
	}
}

void	eating(t_philo *philo)
{
	pthread_mutex_lock(philo->mutex_meal);
	philo->meals_eaten++;
	philo->last_meal_time = get_time_in_ms();
	print_status(philo, "is eating");
	pthread_mutex_unlock(philo->mutex_meal);
	ft_usleep(philo->table->time_eat, philo);
}

void	sleeping(t_philo *philo)
{
	print_status(philo, "is sleeping");
	ft_usleep(philo->table->time_sleep, philo);
}

void	unlock_both_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}

void	free_thread(t_table *table)
{
	free(table->philo);
	free(table->forks);
}
