/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muzz <muzz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 15:07:26 by muzz              #+#    #+#             */
/*   Updated: 2025/05/19 15:15:47 by muzz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_table(t_table *table, int argc)
{
	table->num_philo = 0;
	table->time_to_die = 0;
	table->time_eat = 0;
	table->time_sleep = 0;
	if (argc == 6)
		table->num_need_eat = 0;
	else
		table->num_need_eat = -1;
}

void	init_philo(t_table *table)
{
	int	i;

	table->dead = 0;
	table->philo = malloc(sizeof(t_philo) * table->num_philo);
	if (!table->philo)
		return ;
	i = -1;
	while (++i < table->num_philo)
	{
		table->philo[i].id = i + 1;
		table->philo[i].l_fork = &table->forks[i];
		table->philo[i].r_fork = &table->forks[(i + 1) % table->num_philo];
		table->philo[i].mutex_write = &table->mutex_write;
		table->philo[i].mutex_meal = &table->mutex_meal;
		table->philo[i].dead = &table->dead;
		table->philo[i].mutex_dead = &table->mutex_dead;
		table->philo[i].table = table;
		table->philo[i].meals_eaten = 0;
	}
}

int	init_mutex(t_table *table)
{
	int	i;

	table->forks = malloc(sizeof(pthread_mutex_t) * table->num_philo);
	if (!table->forks)
		return (-1);
	i = -1;
	while (++i < table->num_philo)
	{
		if (pthread_mutex_init(&table->forks[i], NULL) != 0)
		{
			printf("Error: failed init fork %d\n", i);
			return (-1);
		}
	}
	if (pthread_mutex_init(&table->mutex_write, NULL) != 0)
		return (ret_error(-1, "Error: failed mutex write\n"));
	if (pthread_mutex_init(&table->mutex_meal, NULL) != 0)
		return (ret_error(-1, "Error: failed mutex meal\n"));
	if (pthread_mutex_init(&table->mutex_dead, NULL) != 0)
		return (ret_error(-1, "Error: failed mutex dead\n"));
	return (0);
}

void	init_thread(t_philo *philo)
{
	int	i;

	philo->table->time_start = get_time_in_ms();
	i = -1;
	while (++i < philo->table->num_philo)
	{
		philo[i].last_meal_time = get_time_in_ms();
		if (pthread_create(&philo[i].thread, NULL, routine, &philo[i]) != 0)
			return ;
	}
}

void	init_monitor_thread(t_table *table)
{
	pthread_t	monitor;

	if (pthread_create(&monitor, NULL, monitor_routine, table) != 0)
	{
		printf("Error: Failed to create thread\n");
		return ;
	}
	pthread_join(monitor, NULL);
}
