/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyecheon <hyecheon@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 21:20:37 by hyecheon          #+#    #+#             */
/*   Updated: 2023/04/24 21:21:48 by hyecheon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int	main(void)
{
	char	*str2 = "hello\n";
	char	*str3= "\033[0m";

	printf("\033[38;5;211m%s%s", str2, str3);
	printf("\033[38;5;218m%s%s", str2, str3);
	printf("\033[38;5;183m%s%s", str2, str3);
	printf("\033[38;5;141m%s%s", str2, str3);
	printf("\033[38;5;111m%s%s", str2, str3);
	printf("\033[38;5;204m%s%s", str2, str3);
	printf("\033[38;5;115m%s%s", str2, str3);
	return (0);
}
