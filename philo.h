/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muzz <muzz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 16:07:06 by abin-moh          #+#    #+#             */
/*   Updated: 2025/05/12 10:38:40 by muzz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct s_table
{
	long			num_philo;
	long			time_to_die;
	long			time_eat;
	long			time_sleep;
	long			num_need_eat;
	pthread_mutex_t	mutex_write;
	pthread_mutex_t mutex_meal;
	pthread_mutex_t mutex_dead;
	pthread_mutex_t	forks;
	t_philo	*philo;
}	t_table;

typedef struct s_philo
{
	int			id;
	pthread_t	thread;
	long		last_meal_time;
	long		meals_eaten;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*mutex_write;
	pthread_mutex_t	*mutex_meal;
	pthread_mutex_t	*mutex_dead;
	t_table		*table;
}	t_philo;

#endif
