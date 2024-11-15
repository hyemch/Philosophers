/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyecheon <hyecheon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 17:01:33 by hyecheon          #+#    #+#             */
/*   Updated: 2023/05/05 15:53:22 by hyecheon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	leak(void)
{
	system("leaks philo");
}

int	main(int argc, char **argv)
{
	t_info		info;
	t_philo		*philo;

//	atexit(leak);
	if (argc != 6 && argc != 5)
	{
		write(2, "Usage: ./philo [num] [die] [eat] [sleep] or ", 43);
		write(2, "./philo [num] [die] [eat] [sleep] [must eat]\n", 46);
		return (1);
	}
	memset(&info, 0, sizeof(t_info));
	if (init_arg(argv, &info) != 0)
		return (1);
	if (init_philo(&info, &philo) != 0)
	{
		free(philo);
		return (1);
	}
	if (create_philo(&info, philo) != 0)
		print_error("Error: pthread error.\n");
	philo_free(&info, philo);
	return (0);
}
