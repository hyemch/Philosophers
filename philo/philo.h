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

//포크상태를 나타내는 int배열 선언->포크상태 == 1일때 포크를 뮤텍스로 보호
//각각의 필로소퍼가 end_flag를 가지고 있게 만들기.

typedef struct s_info
{
	int				philo_num;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				must_eat;
	int				end_flag;
	long long		start_time;
	int				*fork;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_mutex; //프린트
	pthread_mutex_t	status_mutex; //now - lasttime 관련 관리
	pthread_mutex_t	eat_mutex; //먹은 횟수 관리
}	t_info;

typedef struct s_philo
{
	int				id;
	int				eat_count;
	long long		last_time;
	int				fork_left;
	int				fork_right;
//	int 			check;
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
