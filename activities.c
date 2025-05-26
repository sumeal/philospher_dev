/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   activities.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abin-moh <abin-moh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 15:25:35 by abin-moh          #+#    #+#             */
/*   Updated: 2025/05/25 13:58:22 by abin-moh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_fork(t_philo *philo, char *s)
{
	if (ft_strcmp(s, "left") == 0)
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
	pthread_mutex_lock(&philo->mutex_meal);
	philo->meals_eaten++;
	philo->last_meal_time = get_time_in_ms();
	pthread_mutex_unlock(&philo->mutex_meal);
	print_status(philo, "is eating");
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
	int	i;

	if (table->philo)
	{
		i = -1;
		while (++i < table->num_philo)
			if (table->philo[i].mutex_meal_init)
				pthread_mutex_destroy(&table->philo[i].mutex_meal);
		free(table->philo);
	}
	if (table->forks)
	{
		i = -1;
		while (++i < table->num_philo)
			pthread_mutex_destroy(&table->forks[i]);
		free(table->forks);
	}
	if (table->mutex_write_init)
		pthread_mutex_destroy(&table->mutex_write);
	if (table->mutex_dead_init)
		pthread_mutex_destroy(&table->mutex_dead);
}
