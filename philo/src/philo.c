/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyecheon <hyecheon@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 20:47:42 by hyecheon          #+#    #+#             */
/*   Updated: 2023/05/05 15:57:44 by hyecheon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	philo_sleep(t_info *info, t_philo *philo)
{
	long long	sleep_time;

	philo_printf(info, philo->id, "is sleeping", "\033[38;5;183m");
	sleep_time = get_time();
	check_time(sleep_time, info->time_sleep);
}

void	*philo_do(void *argv)
{
	t_philo	*philo;
	t_info	*info;

	philo = (t_philo *)argv;
	info = philo->info;
	if (info->philo_num == 1)
	{
		philo_solo(info, philo);
		return (0);
	}
	if (philo->id % 2)
		usleep(1024);
	while (1)
	{
		philo_eat(info, philo);
		if (check_end(info))
			break ;
		philo_sleep(info, philo);
		if (check_end(info))
			break ;
		philo_printf(info, philo->id, "is thinking", "\033[38;5;141m");
	}
	return (0);
}

int	create_philo(t_info *info, t_philo *philo)
{
	int	i;

	i = 0;
	info->start_time = get_time();
	while (i < info->philo_num)
	{
		philo[i].last_time = get_time();
		if (pthread_create(&(philo[i].thread), NULL, \
		&philo_do, &(philo[i])) != 0)
		{
			return_error(info, philo);
			return (ERROR);
		}
//		usleep(128);
		i++;
	}
	philo_monitoring(info, philo);
	i = 0;
	while (i < info->philo_num)
		pthread_join(philo[i++].thread, NULL);
	return (0);
}
