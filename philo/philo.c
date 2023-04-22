/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyecheon <hyecheon@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 20:47:42 by hyecheon          #+#    #+#             */
/*   Updated: 2023/04/21 18:17:39 by hyecheon         ###   ########.fr       */
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
//int	init_philo_mutex(t_info *info, t_philo *philo)
//{
//	int	i;
//
//	i = 0;
//	while (i < info->philo_num)
//	{
//		if (pthread_mutex_init(&(philo[i].forks), NULL) < 0)
//		{
//			free(philo[i]->forks);
//			return (0);
//		}
//		i++;
//	}
//	return (1);
//}

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
		(*philo)[i].id = i + 1;
		(*philo)[i].fork_left = i;
		(*philo)[i].fork_right = (i + 1) % info->philo_num;
		(*philo)[i].eat_count = 0;
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
	return (0);
}

//void	*philo_onlyone(t_philo *philo)
//{
//	pthread_mutex_lock(&philo->info->forks[0]);
//	printf("1 has taken a fork\n");
//	pthread_mutex_unlock(&philo->info->forks[0]);
//	return (0);
//}

void	philo_printf(t_info *info, int id, char *str)
{
	pthread_mutex_lock(&(info->print_mutex));
	if (!(info->end_flag))
	{
		printf("%lld ", get_time() - info->start_time);
		printf("%d ", id + 1);
		printf("%s\n", str);
	}
	pthread_mutex_unlock(&(info->print_mutex));
	return ;
}

int	check_time(long long last_time, t_info *info)
{
	long long	now_time;

	while (1)
	{
		now = get_time();
		if ((now_time - last_time) >= info->time_eat)
			break ;
		usleep(10);
	}
}

void	*philo_sleep(t_info *info, t_philo *philo)
{
	long long	sleep_time;

	philo_printf(info, philo->id, "is sleeping");
	sleep_time = get_time();
	check_time(sleep_time);
}

void	*eat_even(t_info *info, t_philo *philo)
{
	pthread_mutex_lock(&(info->forks[philo->fork_right]));
	philo_printf(info, philo->id, "has taken a fork");
	pthread_mutex_lock(&(info->forks[philo->fork_left]));
	philo_printf(info, philo->id, "has taken a fork");
	philo_printf(info, philo->id, "is eating");
	philo->last_time = get_time();
	check_time(philo->last_time);
	pthread_mutex_unlock(&(info->forks[philo->fork_left]));
	pthread_mutex_unlock(&(info->forks[philo->fork_right]));
}
void	*eat_odd(t_info *info, t_philo *philo)
{
	pthread_mutex_lock(&(info->forks[philo->fork_left]));
	philo_printf(info, philo->id, "has taken a fork");
	pthread_mutex_lock(&(info->forks[philo->fork_right]));
	philo_printf(info, philo->id, "has taken a fork");
	philo_printf(info, philo->id, "is eating");
	philo->last_time = get_time();
	check_time(philo->last_time);
	pthread_mutex_unlock(&(info->forks[philo->fork_right]));
	pthread_mutex_unlock(&(info->forks[philo->fork_left]));
}

void	*philo_eat(t_info *info, t_philo *philo)
{
	if (info->philo_num == 1)
	{
		pthread_mutex_lock(&(info->forks[0]));
		philo_printf(info, philo->id, "has taken a fork");
		pthread_mutex_unlock(&(info->forks[0]));
		return ;
	}
	if (info->philo_num % 2)
		eat_odd(info, philo);
	else
		eat_even(info, philo);
}

void	*philo_do(void *argv)
{
	t_philo	*philo;
	t_info	*info;

	philo = (t_philo *)argv;
	info = philo->info;
	if (philo->id % 2)
		usleep(100);
	while (1)
	{
		philo_eat(info, philo);
		if (info->must_eat != 0 && info->must_eat == philo->eat_count)
			break ;
		philo_sleep(info, philo);
		philo_printf(info, philo->id, "is thinking");
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
	i = 0;
	while (i < info->philo_num)
	{
		if (pthread_join(philo[i].thread, NULL) != 0)
			return (ERROR);
		i++;
	}
	//스레드 종료 함수
	//pthread_join(philo[i].thread, NULL);
	return (0);
}

int	main(int argc, char **argv)
{
	t_info		info;
	t_philo		*philo;
	int			i;

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
	i = 0;
	while (i < info.philo_num)
	{
		printf("%d %lld\n", philo[i].eat_count, philo[i].last_time - info.start_time);
		i++;
	}
	return (0);
}
