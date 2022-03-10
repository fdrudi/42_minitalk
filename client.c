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

#include "minitalk.h"

void	ft_signal_receiver(int sig)
{
	static int	i;

	if (sig == SIGUSR1 && i == 0)
	{
		ft_putstr_fd("\n| Message delivered | ", 1);
		i = 1;
	}
	if (sig == SIGUSR2)
	{
		ft_putstr_fd("---> | Messagge arrived |\n", 1);
		i = 0;
		exit(0);
	}
}

void	ft_send_bits(int pid, char byte)
{
	int	count;

	count = 0;
	while (count < 8)
	{
		if (byte & 0x80)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		byte <<= 1;
		count++;
		usleep(500);
	}
}

void	ft_send_str(char *str, int pid)
{
	int	i;

	i = -1;
	while (str[++i] != '\0')
		ft_send_bits(pid, str[i]);
	ft_send_bits(pid, '\n');
	ft_send_bits(pid, '\0');
}

int	main(int argc, char *argv[])
{
	int	pid;

	if (argc != 3)
	{
		ft_putstr_fd("Invalid number of arguments\n", 1);
		exit(1);
	}
	signal(SIGUSR1, ft_signal_receiver);
	signal(SIGUSR2, ft_signal_receiver);
	pid = ft_atoi(argv[1]);
	ft_send_str(argv[2], pid);
}
