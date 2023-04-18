/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyecheon <hyecheon@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 20:51:59 by hyecheon          #+#    #+#             */
/*   Updated: 2023/04/18 21:11:51 by hyecheon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

# define ERROR -1

typedef struct s_info
{
	int				philo_num;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				must_eat;
	long long		start_time;
}	t_info;

typedef struct s_philo
{
	int				id;
	int				eat_count;
	long long		eat_time;
	int				fork_left;
	int				fork_right;
	pthread_t		thread;
	struct t_pthead	*pthread;
	struct t_info	*info;
}	t_philo;

typedef struct s_pthread
{
	pthread_mutex_t	forks;
	pthread_mutex_t	print_mutex;
}	t_pthread;

#endif
