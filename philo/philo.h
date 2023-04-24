/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyecheon <hyecheon@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 18:34:34 by hyecheon          #+#    #+#             */
/*   Updated: 2023/04/24 23:21:07 by hyecheon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyecheon <hyecheon@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 20:51:59 by hyecheon          #+#    #+#             */
/*   Updated: 2023/04/20 21:03:50 by hyecheon         ###   ########.fr       */
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
	int				end_flag;
	long long		start_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	status_mutex;
}	t_info;

typedef struct s_philo
{
	int				id;
	int				eat_count;
	long long		last_time;
	int				fork_left;
	int				fork_right;
	pthread_t		thread;
	t_info			*info;
}	t_philo;

//typedef struct s_philo
//{
//	int				id;
//	int				eat_count;
//	longlong		eat_time;
//	int				fork_left;
//	int				fork_right;
//	pthread_t		thread;
//	t_mutex			*mutex;
//	t_info			*info;
//}	t_philo;
//
//typedef struct s_mutex
//{
//	pthread_mutex_t	*forks;
//	pthread_mutex_t	print_mutex;
//}	t_mutex;

#endif
