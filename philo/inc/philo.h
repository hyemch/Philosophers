/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyecheon <hyecheon@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 20:51:59 by hyecheon          #+#    #+#             */
/*   Updated: 2023/05/01 16:14:20 by hyecheon         ###   ########.fr       */
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
	int				*fork;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	status_mutex;
	pthread_mutex_t	endflag_mutex;
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

/*utils.c*/
size_t		ft_strlen(const char *str);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
int			atol_utils(const char *str, long *result);
long		ft_atol(const char *str);
void		atol_intarr(char **arr);

/*init.c*/
int			print_error(char *str);
int			init_philo_mutex(t_info *info);
int			init_philo(t_info *info, t_philo **philo);
int			init_arg(char **argv, t_info *info);

/*philo.c*/
void		philo_sleep(t_info *info, t_philo *philo);
void		*philo_do(void *argv);
int			create_philo(t_info *info, t_philo *philo);

/*philo_eat.c*/
void		eat_even(t_info *info, t_philo *philo);
void		eat_odd(t_info *info, t_philo *philo);
void		philo_solo(t_info *info, t_philo *philo);
void		philo_eat(t_info *info, t_philo *philo);

/*philo_utils.c*/
long long	get_time(void);
void		check_time(long long last_time, long long check_time);
void		philo_printf(t_info *info, int id, char *str, char *color);
int			return_error(t_info *info, t_philo *philo);

/*philo_monitoring.c*/
int			check_end(t_info *info);
int			philo_end(t_info *info, t_philo *philo);
void		philo_monitoring(t_info *info, t_philo *philo);
void		philo_free(t_info *info, t_philo *philo);

#endif
