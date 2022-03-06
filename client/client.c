/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdrudi <fdrudi@student.42roma.it>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 17:17:10 by fdrudi            #+#    #+#             */
/*   Updated: 2022/03/03 17:17:10 by fdrudi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

int	ft_atoi(const char *str)
{
	int	x;
	int	y;

	y = 0;
	x = 1;
	while (*str == 32 || (*str >= 9 && *str <= 13))
		str++;
	if (*str == 43 || *str == 45)
	{
		if (*str == 45)
			x *= -1;
		str++;
	}
	while (*str <= 57 && *str >= 48)
	{
		y = (y * 10) + ((*str - 48) % 10);
		str++;
	}
	y *= x;
	return (y);
}

/* void	handler_one(int sig)
{
//	sig = 12;
	printf("\nQui tutto bene %d\n", sig);
}
 */

void	ft_send(int pid, char byte)
{
	int	count;
	int	bit;

	count = 0;
	while (count < 7)
	{
		bit = (byte >> count) & 1;
		printf("\nByte : %d         Bit : %d\n", byte, bit);
		count++;
	}
}

int	main(int argc, char *argv[])
{
	char str[5] = "ciao";
	int	i = 0;
	int	pid;

	pid = ft_atoi(argv[1]);
	while (str[i] != '\0')
	{
		ft_send(pid, str[i]);
		i++;
	}
/* 	struct sigaction sa = { 0 };
	sa.sa_flags = SA_RESTART;
	sa.sa_handler = &handler_one;
	sigaction(SIGUSR1, &sa, NULL);
	kill(getpid(), SIGUSR1);
	sigaction(SIGUSR2, &sa, NULL);
	kill(getpid(), SIGUSR2);
	while (str[i] != '\0')
	{
		x = str[i];
		kill(getpid(), SIGUSR1);
		i++;
	} */
	return (0);
}
