/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muzz <muzz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 16:06:46 by abin-moh          #+#    #+#             */
/*   Updated: 2025/05/12 10:40:27 by muzz             ###   ########.fr       */
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

int	init_fork(t_table *table)
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
			printf("Error: failed init fork %d\n". i);
			return (-1);
		}
	}
	return (0);
}

void	init_philo(t_table *table)
{
	int	i;


	table->philo = malloc(sizeof(t_philo) * table->num_philo);
	if (!table->philo)
		return (NULL);
	i = -1;
	while (++i < table->num_philo)
	{
		table->philo[i].id = i + 1;
		table->philo[i].l_fork = &table->forks[i];
		table->philo[i].r_fork = &table->forks[(i + 1) % table->num_philo];
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
		if (init_fork(&table) < 0)
			return (1);
		init_philo(&table);
		print_table(&table);
	}
	else
	{
		printf("Error: Wrong format\n");
	}
	return (0);
}
