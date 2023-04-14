/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyecheon <hyecheon@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 20:47:42 by hyecheon          #+#    #+#             */
/*   Updated: 2023/04/14 22:11:07 by hyecheon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (*(str + i) != '\0')
		i++;
	return (i);
}

void	print_error(char *str)
{
	write(2, str, ft_strlen(str));
	exit (1);
}

int	atol_utils(const char *str, long *result)
{
	while (*str)
	{
		if (*str >= '0' && *str <= '9')
		{
			*result = *result * 10 + (*str - '0');
			if (*result < 0)
				return (ERROR);
		}
		else
			return (ERROR);
		str++;
	}
	return (0);
}

long	ft_atol(const char *str)
{
	int		sign;
	long	result;

	sign = 1;
	result = 0;
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign *= -1;
		str++;
	}
	if (atol_utils(str, &result) == ERROR)
		return (ERROR);
	return (result * sign);
}

void	atol_intarr(char **arr)
{
	int		i;
	long	check_num;

	i = 1;
	while (arr[i] != NULL)
	{
		check_num = ft_atol(arr[i]);
		if (check_num < -2147483648 || 2147483647 < check_num)
			print_error("Error: Use the int range values.\n");
		i++;
	}
}

int	init_philo_mutex(t_info *info)
{
	int	i;

	info->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) \
	* info->philo_num);
	if (!(info->forks))
		return (0);
	i = 0;
	while (i < info->philo_num)
	{
		if (pthread_mutex_init(&(info->forks)[i], NULL) < 0)
		{
			free(info->forks);
			return (0);
		}
		i++;
	}
	return (1);
}

int	get_time(void)
{
	struct timeval	current;

	gettimeofday(&current, NULL);
	return (current.tv_sec * 1000 * 1000);
}

int	init_philo(t_info *info, t_philo **philo)
{
	int	i;

	*philo = (t_philo *)malloc(sizeof(t_philo) * info->philo_num);
	if (!*philo)
		print_error("philo malloc error\n");
	i = 0;
	while (i < info->philo_num)
	{
		philo[i]->info = info;
		philo[i]->id = i;
		philo[i]->eat_count = 0;
		philo[i]->last_time = get_time();
		philo[i]->fork_left = &(info->forks)[i];
		philo[i]->fork_right = &(info->forks)[(i + 1) % info->philo_num];
		i++;
	}
	return (0);
}

int	init_arg(char **argv, t_info *info)
{
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
	if (!(init_philo_mutex(info)))
		print_error("Error : mutex init error\n");
	return (0);
}

int	main(int argc, char **argv)
{
	t_info		info;
	t_philo		*philo;

	if (argc != 6 && argc != 5)
	{
		write(2, "Usage: ./philo [num] [die] [eat] [sleep] or ", 43);
		write(2, "./philo [num] [die] [eat] [sleep] [must eat]\n", 46);
		exit(EXIT_FAILURE);
	}
	memset(&info, 0, sizeof(t_info));
	init_arg(argv, &info);
	init_philo(&info, &philo);
	printf("%d %d\n", philo->eat_count, philo->last_time);
	return (0);
}
