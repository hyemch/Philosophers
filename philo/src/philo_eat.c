/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_eat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyecheon <hyecheon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 17:09:31 by hyecheon          #+#    #+#             */
/*   Updated: 2023/04/30 17:09:31 by hyecheon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	eat_even(t_info *info, t_philo *philo)
{
	pthread_mutex_lock(&(info->forks[philo->fork_right]));
	philo_printf(info, philo->id, "has taken a fork", "\033[38;5;211m");
	pthread_mutex_lock(&(info->forks[philo->fork_left]));
	philo_printf(info, philo->id, "has taken a fork", "\033[38;5;211m");
	info->fork[philo->fork_left] = 1;
	info->fork[philo->fork_right] = 1;
	philo_printf(info, philo->id, "is eating", "\033[38;5;218m");
	pthread_mutex_lock(&(info->status_mutex));
	philo->last_time = get_time();
	pthread_mutex_unlock(&(info->status_mutex));
	check_time(philo->last_time, info->time_eat);
	info->fork[philo->fork_left] = 0;
	info->fork[philo->fork_right] = 0;
	pthread_mutex_unlock(&(info->forks[philo->fork_right]));
	pthread_mutex_unlock(&(info->forks[philo->fork_left]));
}

void	eat_odd(t_info *info, t_philo *philo)
{
	pthread_mutex_lock(&(info->forks[philo->fork_left]));
	philo_printf(info, philo->id, "has taken a fork", "\033[38;5;211m");
	pthread_mutex_lock(&(info->forks[philo->fork_right]));
	philo_printf(info, philo->id, "has taken a fork", "\033[38;5;211m");
	info->fork[philo->fork_left] = 1;
	info->fork[philo->fork_right] = 1;
	philo_printf(info, philo->id, "is eating", "\033[38;5;218m");
	pthread_mutex_lock(&(info->status_mutex));
	philo->last_time = get_time();
	pthread_mutex_unlock(&(info->status_mutex));
	check_time(philo->last_time, info->time_eat);
	info->fork[philo->fork_left] = 0;
	info->fork[philo->fork_right] = 0;
	pthread_mutex_unlock(&(info->forks[philo->fork_right]));
	pthread_mutex_unlock(&(info->forks[philo->fork_left]));
}

void	philo_solo(t_info *info, t_philo *philo)
{
	pthread_mutex_lock(&(info->forks[0]));
	philo_printf(info, philo->id, "has taken a fork", "\033[38;5;211m");
	info->fork[0] = 1;
	info->fork[0] = 0;
	pthread_mutex_unlock(&(info->forks[0]));
}

void	philo_eat(t_info *info, t_philo *philo)
{
	if (!(philo->id % 2))
		eat_odd(info, philo);
	else
		eat_even(info, philo);
	pthread_mutex_lock(&(info->status_mutex));
	philo->eat_count++;
	pthread_mutex_unlock(&(info->status_mutex));
}
