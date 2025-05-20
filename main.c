/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abin-moh <abin-moh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 16:06:46 by abin-moh          #+#    #+#             */
/*   Updated: 2025/05/20 12:29:13 by abin-moh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time_in_ms(void)
{
	struct timeval	time_value;

	gettimeofday(&time_value, NULL);
	return ((time_value.tv_sec * 1000) + (time_value.tv_usec / 1000));
}

void	ft_usleep(long time_sleep, t_philo *philo)
{
	long	start;

	start = get_time_in_ms();
	while (((get_time_in_ms() - start) < time_sleep))
	{
		if (is_dead(philo))
			break ;
		usleep(200);
	}
}

int	ret_error(int ret, char *s)
{
	printf("%s\n", s);
	return (ret);
}

void	print_status(t_philo *philo, char *s)
{
	long	now;

	pthread_mutex_lock(philo->mutex_dead);
	pthread_mutex_lock(philo->mutex_write);
	now = get_time_in_ms() - philo->table->time_start;
	if (!(*philo->dead))
		printf("%ld %d %s\n", now, philo->id, s);
	pthread_mutex_unlock(philo->mutex_write);
	pthread_mutex_unlock(philo->mutex_dead);
}

int	main(int argc, char **argv)
{
	t_table	table;

	if (argc == 5 || argc == 6)
	{
		init_table(&table, argc);
		if (parsing_input(argc, argv, &table) < 0)
			return (1);
		if (init_mutex(&table) < 0)
			return (1);
		init_philo(&table);
		init_thread(table.philo);
		init_monitor_thread(&table);
		wait_thread(table.philo);
		free_thread(&table);
	}
	else
	{
		printf("Error: Wrong format\n");
	}
	return (0);
}
