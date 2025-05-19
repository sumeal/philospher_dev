/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muzz <muzz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 16:06:46 by abin-moh          #+#    #+#             */
/*   Updated: 2025/05/19 15:30:32 by muzz             ###   ########.fr       */
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
	while (((get_time_in_ms() - start) < time_sleep) && philo->table->dead != 1)
		usleep(200);
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
		printf("%ld Philospher %d %s\n", now, philo->id, s);
	pthread_mutex_unlock(philo->mutex_write);
	pthread_mutex_unlock(philo->mutex_dead);

}

int	main(int argc, char **argv)
{
	t_table	table;

	if (argc == 5 || argc == 6)
	{
		printf("1\n");
		init_table(&table, argc);
		printf("2\n");
		if (parsing_input(argc, argv, &table) < 0)
			return (1);
		printf("3\n");
		if (init_mutex(&table) < 0)
			return (1);
		printf("4\n");
		init_philo(&table);
		printf("5\n");
		init_thread(table.philo);
		printf("6\n");
		init_monitor_thread(&table);
		wait_thread(table.philo);
		printf("7\n");
	}
	else
	{
		printf("Error: Wrong format\n");
	}
	return (0);
}
