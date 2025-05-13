/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abin-moh <abin-moh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 16:06:46 by abin-moh          #+#    #+#             */
/*   Updated: 2025/05/13 12:38:55 by abin-moh         ###   ########.fr       */
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

int	ft_isdigit(int c)
{
	if ((c >= '0' && c <= '9'))
		return (1);
	return (0);
}

int	is_numeric(char *s)
{
	int i;

	i = 0;
	if (s[0] == '+')
		i++;
	while (s[i])
	{
		if (!ft_isdigit(s[i]))
			return (-1);
		i++;
	}
	return (0);
	
}

long	ft_atol(const char *nptr)
{
	int		sign;
	long	result;

	result = 0;
	sign = 1;
	while (*nptr == ' ' || *nptr == '\n' || *nptr == '\f'
		|| *nptr == '\r' || *nptr == '\t' || *nptr == '\v')
		nptr++;
	if (*nptr == '+' || *nptr == '-')
	{
		if (*nptr == '-')
			sign = -1;
		nptr++;
	}
	while (*nptr >= '0' && *nptr <= '9')
	{
		result = result * 10 + *nptr - '0';
		nptr++;
	}
	return (sign * result);
}

int	ret_error(int ret, char *s)
{
	printf("%s\n", s);
	return (ret);
}

int	put_value_to_table(t_table *table, long *num)
{
	table->num_philo = num[0];
	table->time_to_die = num[1];
	table->time_eat = num[2];
	table->time_sleep = num[3];
	if (table->num_need_eat >= 0)
		table->num_need_eat = num[4];
	if (table->num_philo > 200)
		return (ret_error(-1, "Error: exceed maximum 200 philos"));
	return (0);
}

int	parsing_input(int argc, char **argv, t_table *table)
{
	int		i;
	long	num[5];

	i = 0;
	while (++i < argc)
	{
		if (is_numeric(argv[i]) < 0)
			return (ret_error(-1, "Error: need numeric input"));
		num[i - 1] = ft_atol(argv[i]);
	}
	if (put_value_to_table(table, num) < 0)
		return (-1);
	return (0);
}

void	print_table(t_table *table)
{
	printf("=== Table Configuration ===\n");
	printf("Number of Philosophers : %ld\n", table->num_philo);
	printf("Time to Die            : %ld ms\n", table->time_to_die);
	printf("Time to Eat            : %ld ms\n", table->time_eat);
	printf("Time to Sleep          : %ld ms\n", table->time_sleep);
	printf("Number Must Eat        : %ld\n", table->num_need_eat);
	printf("===========================\n");
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
	}
}

void	print_status(t_philo *philo, char *s)
{
	long	now;

	pthread_mutex_lock(&philo->mutex_write);
	now = get_time_in_ms() - philo->table->time_start;
	printf("%l Philospher %d %s", now, philo->id, s);
	pthread_mutex_unlocklock(&philo->mutex_write);
}

void	no_one_is_dead(t_philo *philo)
{
	
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		usleep(1000);
	while (!no_one_is_dead(philo))
	{
		print_status(philo, "is thinking");
		pthread_mutex_lock(philo->l_fork);
		print_status(philo, "has taken left fork");
		pthread_mutex_lock(philo->r_fork);
		print_status(philo, "has taken right fork");
		pthread_mutex_lock(philo->mutex_meal);
		philo->last_meal_time = get_time_in_ms();
		print_status(philo, "is eating");
		pthread_mutex_unlock(philo->mutex_meal);
		pthread_mutex_unlock(philo->l_fork);
		pthread_mutex_unlock(philo->r_fork);
		print_status(philo, "is sleeping");
		ft_usleep(philo->table->time_sleep * 1000, philo);
	}
}

void	init_thread(t_philo *philo)
{
	int	i;

	philo->table->time_start = get_time_in_ms();
	i = -1;
	while (++i < philo->table->num_philo)
	{
		if (pthread_create(&philo[i].thread, NULL, routine, &philo[i]) != 0)
			return ;
	}
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
		//print_table(&table);
		init_thread(&table.philo);
	}
	else
	{
		printf("Error: Wrong format\n");
	}
	return (0);
}
