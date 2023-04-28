/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyecheon <hyecheon@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 20:47:42 by hyecheon          #+#    #+#             */
/*   Updated: 2023/04/28 19:43:39 by hyecheon         ###   ########.fr       */
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

int	init_philo_mutex(t_info *info)
{
	int	i;

	if (pthread_mutex_init(&(info->print_mutex), NULL) != 0)
		return (0);
	if (pthread_mutex_init(&(info->status_mutex), NULL) != 0)
		return (0);
	if (pthread_mutex_init(&(info->eat_mutex), NULL) != 0)
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
	pthread_mutex_unlock(&(info->print_mutex));
}

int	check_eat(t_info *info, t_philo *philo)
{
	pthread_mutex_lock(&(info->eat_mutex));
	if (philo->eat_check)
	{
		pthread_mutex_unlock(&(info->eat_mutex));
		return (1);
	}
	pthread_mutex_unlock(&(info->eat_mutex));
	return (0);
}

//int	check_eat(t_info *info, t_philo *philo)
//{
//	int	i;
//
//	i = 0;
//	if (info->must_eat != 0)
//	{
//		while (i < info->philo_num)
//		{
//			pthread_mutex_lock(&(info->eat_mutex));
//			if (info->must_eat > philo[i].eat_count)
//			{
//				pthread_mutex_unlock(&(info->eat_mutex));
//				return (0);
//			}
//			pthread_mutex_unlock(&(info->eat_mutex));
//			i++;
//		}
//		return (1);
//	}
//	return (0);
//}

void	check_time(long long last_time, long long check_time)
{
	long long	now_time;

	while (1)
	{
		now_time = get_time();
		if ((now_time - last_time) >= check_time)
			break ;
		usleep(128);
	}
}

void	philo_sleep(t_info *info, t_philo *philo)
{
	long long	sleep_time;

	philo_printf(info, philo->id, "is sleeping", "\033[38;5;183m");
	sleep_time = get_time();
	check_time(sleep_time, info->time_sleep);
}

void	eat_even(t_info *info, t_philo *philo)
{
	pthread_mutex_lock(&(info->forks[philo->fork_right]));
	philo_printf(info, philo->id, "has taken a fork", "\033[38;5;211m");
	pthread_mutex_lock(&(info->forks[philo->fork_left]));
	philo_printf(info, philo->id, "has taken a fork", "\033[38;5;211m");
	info->fork[philo->fork_left] = 1;
	info->fork[philo->fork_right] = 1;
	philo_printf(info, philo->id, "is eating", "\033[38;5;218m");
	info->fork[philo->fork_left] = 0;
	info->fork[philo->fork_right] = 0;
	pthread_mutex_lock(&(info->status_mutex));
	philo->last_time = get_time();
	pthread_mutex_unlock(&(info->status_mutex));
	check_time(philo->last_time, info->time_eat);
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
	info->fork[philo->fork_left] = 0;
	info->fork[philo->fork_right] = 0;
	pthread_mutex_lock(&(info->status_mutex));
	philo->last_time = get_time();
	pthread_mutex_unlock(&(info->status_mutex));
	check_time(philo->last_time, info->time_eat);
	pthread_mutex_unlock(&(info->forks[philo->fork_right]));
	pthread_mutex_unlock(&(info->forks[philo->fork_left]));
}

void	philo_solo(t_info *info, t_philo *philo)
{
	pthread_mutex_lock(&(info->forks[0]));
	philo_printf(info, philo->id, "has taken a fork", "\033[38;5;211m");
	info->fork[0] = 1;
	pthread_mutex_unlock(&(info->forks[0]));
}

void	philo_eat(t_info *info, t_philo *philo)
{
	if (philo->id % 2)
		eat_odd(info, philo);
	else
		eat_even(info, philo);
	pthread_mutex_lock(&(info->eat_mutex));
	philo->eat_count++;
	pthread_mutex_unlock(&(info->eat_mutex));
}

int	check_philo(t_info *info, t_philo *philo)
{
	int	i;
	int	cnt;

	i = 0;
	if (info->must_eat == 0)
		return (0);
	pthread_mutex_lock(&(info->eat_mutex));
	while (i < info->philo_num)
	{
		if (philo[i].eat_count == info->must_eat)
			philo[i].eat_check = 1;
		i++;
	}
	i = 0;
	cnt = 0;
	while (i < info->philo_num)
	{
		if (philo[i].eat_check)
			cnt++;
		i++;
	}
	pthread_mutex_unlock(&(info->eat_mutex));
	return (cnt);
}

int	philo_death(t_info *info, t_philo *philo)
{
	long long	now;
	int			i;

	i = 0;
	while (i < info->philo_num)
	{
		pthread_mutex_lock(&(info->status_mutex));
		now = get_time();
		if ((now - philo[i].last_time) > info->time_die)
		{
			philo_printf(info, philo[i].id, "died", "\033[38;5;204m");
			pthread_mutex_unlock(&(info->status_mutex));
			pthread_mutex_lock(&(info->endflag_mutex));
			info->end_flag = 1;
			pthread_mutex_unlock(&(info->endflag_mutex));
			return (1);
		}
		pthread_mutex_unlock(&(info->status_mutex));
		i++;
	}
	return (0);
}

void	philo_monitoring(t_info *info, t_philo *philo)
{
	while (1)
	{
		if (check_philo(info, philo) == info->philo_num)
			break ;
		if (philo_death(info, philo))
			break ;
		usleep(256);
	}
	pthread_mutex_lock(&(info->endflag_mutex));
	info->end_flag = 1;
	pthread_mutex_unlock(&(info->endflag_mutex));
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
	free(info->fork);
	free(philo);
	pthread_mutex_destroy(&info->print_mutex);
	pthread_mutex_destroy(&info->status_mutex);
	pthread_mutex_destroy(&info->eat_mutex);
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
	if (!(philo->id % 2))
		usleep(256);
	while (!(check_end(info)))
	{
		philo_eat(info, philo);
		if (check_end(info))
			break ;
		philo_sleep(info, philo);
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
			return (ERROR);
		i++;
	}
	philo_monitoring(info, philo);
	i = 0;
	while (i < info->philo_num)
	{
		if (pthread_join(philo[i].thread, NULL) != 0)
			return (ERROR);
		i++;
	}
	philo_free(info, philo);
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
	if (create_philo(&info, philo) != 0)
		print_error("Error: pthread error.\n");
	return (0);
}
