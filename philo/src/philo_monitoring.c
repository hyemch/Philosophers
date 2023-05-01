/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_end.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyecheon <hyecheon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 17:15:47 by hyecheon          #+#    #+#             */
/*   Updated: 2023/04/30 17:15:47 by hyecheon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	check_end(t_info *info)
{
	pthread_mutex_lock(&(info->endflag_mutex));
	if (info->end_flag == 1)
	{
		pthread_mutex_unlock(&(info->endflag_mutex));
		return (1);
	}
	pthread_mutex_unlock(&(info->endflag_mutex));
	return (0);
}

int	philo_end(t_info *info, t_philo *philo)
{
	int			i;
	int			cnt;

	i = 0;
	cnt = 0;
	while (i < info->philo_num)
	{
		pthread_mutex_lock(&(info->status_mutex));
		if ((get_time() - philo[i].last_time) > info->time_die)
		{
			philo_printf(info, philo[i].id, "died", "\033[38;5;204m");
			pthread_mutex_unlock(&(info->status_mutex));
			return (1);
		}
		if (info->must_eat != 0)
		{
			if (philo[i].eat_count >= info->must_eat)
				cnt++;
		}
		pthread_mutex_unlock(&(info->status_mutex));
		i++;
	}
	if (cnt == info->philo_num)
		return (1);
	return (0);
}

void	philo_monitoring(t_info *info, t_philo *philo)
{
	while (1)
	{
		if (philo_end(info, philo))
			break ;
		usleep(128);
	}
	pthread_mutex_lock(&(info->endflag_mutex));
	info->end_flag = 1;
	pthread_mutex_unlock(&(info->endflag_mutex));
	pthread_mutex_unlock(&(info->print_mutex));
}

void	philo_free(t_info *info, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < info->philo_num)
	{
		pthread_mutex_destroy(&info->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&info->print_mutex);
	pthread_mutex_destroy(&info->status_mutex);
	pthread_mutex_destroy(&info->endflag_mutex);
	free(info->fork);
	free(info->forks);
	free(philo);
}
