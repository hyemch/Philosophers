/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyecheon <hyecheon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 17:06:51 by hyecheon          #+#    #+#             */
/*   Updated: 2023/04/30 17:06:51 by hyecheon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	print_error(char *str)
{
	write(2, str, ft_strlen(str));
	return (0);
}

int	init_philo_mutex(t_info *info)
{
	int	i;

	if (pthread_mutex_init(&(info->print_mutex), NULL) != 0)
		return (0);
	if (pthread_mutex_init(&(info->status_mutex), NULL) != 0)
		return (0);
	if (pthread_mutex_init(&(info->endflag_mutex), NULL) != 0)
		return (0);
	info->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) \
	* info->philo_num);
	if (!(info->forks))
		return (0);
	i = 0;
	while (i < info->philo_num)
	{
		if (pthread_mutex_init(&(info->forks)[i], NULL) != 0)
		{
			free(info->forks);
			return (0);
		}
		i++;
	}
	return (1);
}

int	init_philo(t_info *info, t_philo **philo)
{
	int				i;

	*philo = (t_philo *)malloc(sizeof(t_philo) * info->philo_num);
	if (!*philo)
		print_error("philo malloc error\n");
	if (!(init_philo_mutex(info)))
		print_error("Error : mutex init error\n");
	i = 0;
	while (i < info->philo_num)
	{
		(*philo)[i].info = info;
		(*philo)[i].id = i;
		(*philo)[i].fork_left = (i + info->philo_num - 1) % info->philo_num;
		(*philo)[i].fork_right = i;
		(*philo)[i].eat_count = 0;
		(*philo)[i].eat_check = 0;
		i++;
	}
	return (0);
}

int	init_arg(char **argv, t_info *info)
{
	int	i;

	atol_intarr(argv);
	info->philo_num = (int)ft_atol(argv[1]);
	info->time_die = (int)ft_atol(argv[2]);
	info->time_eat = (int)ft_atol(argv[3]);
	info->time_sleep = (int)ft_atol(argv[4]);
	if (argv[5] != NULL)
		info->must_eat = (int)ft_atol(argv[5]);
	if (info->philo_num <= 0 || info->time_die <= 0 || info->time_eat <= 0 \
	|| info->time_sleep <= 0)
		print_error("Error: argument error.\n");
	if (argv[5] != NULL && info->must_eat <= 0)
		print_error("Error: argument error.\n");
	info->fork = (int *)malloc(sizeof(int) * info->philo_num);
	if (!(info->fork))
		print_error("Error: argument error.\n");
	i = 0;
	while (i < info->philo_num)
	{
		info->fork[i] = 0;
		i++;
	}
	return (0);
}
