/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   activities.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abin-moh <abin-moh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 15:25:35 by abin-moh          #+#    #+#             */
/*   Updated: 2025/05/28 11:12:06 by abin-moh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->mutex_meal);
	philo->last_meal_time = get_time_in_ms();
	pthread_mutex_unlock(&philo->mutex_meal);
	print_status(philo, "is eating", 0);
	// print_status(philo, "is eating", philo->last_meal_time - philo->table->time_start);
	ft_usleep(philo->table->time_eat, philo);
	pthread_mutex_lock(&philo->mutex_meal);
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->mutex_meal);
}

void	sleeping(t_philo *philo)
{
	print_status(philo, "is sleeping", 0);
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

void	thinking(t_philo *philo)
{
    long time_since_last_meal;
    long time_to_think;
    
    pthread_mutex_lock(&philo->mutex_meal);
    time_since_last_meal = get_time_in_ms() - philo->last_meal_time;
    pthread_mutex_unlock(&philo->mutex_meal);
    time_to_think = (philo->table->time_to_die - time_since_last_meal - philo->table->time_eat) / 2;
    if (time_to_think < 0)
        time_to_think = 0;
    else if (time_to_think > 200)
        time_to_think = 200;
    print_status(philo, "is thinking", 0);
    if (time_to_think > 0)
        ft_usleep(time_to_think, philo);
}
