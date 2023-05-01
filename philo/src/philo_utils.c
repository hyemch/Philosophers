/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyecheon <hyecheon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 17:11:55 by hyecheon          #+#    #+#             */
/*   Updated: 2023/05/01 16:15:06 by hyecheon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

long long	get_time(void)
{
	struct timeval	current;

	if ((gettimeofday(&current, NULL)) == -1)
	{
		write(2, "Error: gettimeofday error.\n", 27);
		return (ERROR);
	}
	return ((current.tv_sec * 1000) + (current.tv_usec / 1000));
}

void	check_time(long long last_time, long long check_time)
{
	long long	now_time;

	while (1)
	{
		now_time = get_time();
		if ((now_time - last_time) >= check_time)
			break ;
		usleep(256);
	}
}

void	philo_printf(t_info *info, int id, char *str, char *color)
{
	pthread_mutex_lock(&(info->print_mutex));
	if (!(check_end(info)))
	{
		printf("%lld ", get_time() - info->start_time);
		printf("\033[38;5;115m%d ", id + 1);
		printf("%s%s\n", color, str);
		printf("\033[0m");
	}
	if (ft_strncmp(str, "died", 4) == 0)
		return ;
	pthread_mutex_unlock(&(info->print_mutex));
}

int	return_error(t_info *info, t_philo *philo)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&(info->endflag_mutex));
	info->end_flag = 1;
	pthread_mutex_unlock(&(info->endflag_mutex));
	while (i < info->philo_num)
		pthread_join(philo[i++].thread, NULL);
	return (ERROR);
}
