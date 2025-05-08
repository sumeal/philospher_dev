/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abin-moh <abin-moh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 16:07:06 by abin-moh          #+#    #+#             */
/*   Updated: 2025/05/08 16:34:35 by abin-moh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <sys/time.h>

typedef struct s_table
{
	long	num_philo;
	long	time_to_die;
	long	time_eat;
	long	time_sleep;
	long	num_need_eat;

}	t_table;

#endif
