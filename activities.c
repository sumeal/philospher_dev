/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   activities.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abin-moh <abin-moh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 15:25:35 by abin-moh          #+#    #+#             */
/*   Updated: 2025/05/29 19:29:55 by abin-moh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eating(t_philo *philo)
{
	pthread_mutex_lock(philo->l_fork);
	print_status(philo, "has taken a fork", 0);
	if (is_dead(philo))
	{
		pthread_mutex_unlock(philo->l_fork);
		return ;
    }
	pthread_mutex_lock(philo->r_fork);
	print_status(philo, "has taken a fork", 0);
	pthread_mutex_lock(&philo->mutex_meal);
	philo->last_meal_time = get_time_in_ms();
	pthread_mutex_unlock(&philo->mutex_meal);
	print_status(philo, "is eating", 0);
	// print_status(philo, "is eating", philo->last_meal_time - philo->table->time_start);
	ft_usleep(philo->table->time_eat, philo);
	pthread_mutex_lock(&philo->mutex_meal);
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->mutex_meal);
	unlock_both_forks(philo);
}

void	sleeping(t_philo *philo)
{
	print_status(philo, "is sleeping", 0);
	ft_usleep(philo->table->time_sleep, philo);
}

void	unlock_both_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(philo->l_fork);

}

void	free_thread(t_table *table)
{
	int	i;

	if (table->philo)
	{
		i = -1;
		while (++i < table->num_philo)
		{
			if (table->philo[i].mutex_meal_init)
			{
				if (pthread_mutex_destroy(&table->philo[i].mutex_meal) != 0)
					fprintf(stderr, "Failed to destroy mutex_meal for philo %d\n", i);
			}
		}
		free(table->philo);
	}
	if (table->forks)
	{
		i = -1;
		while (++i < table->num_philo)
		{
			if (pthread_mutex_destroy(&table->forks[i]) != 0)
				fprintf(stderr, "Failed to destroy fork mutex %d\n", i);
		}
		free(table->forks);
	}
	if (table->mutex_write_init)
	{
		if (pthread_mutex_destroy(&table->mutex_write) != 0)
			fprintf(stderr, "Failed to destroy mutex_write\n");
	}
	if (table->mutex_dead_init)
	{
		if (pthread_mutex_destroy(&table->mutex_dead) != 0)
			fprintf(stderr, "Failed to destroy mutex_dead\n");
	}
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
