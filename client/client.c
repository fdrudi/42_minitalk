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

void	ft_putstr(char *s)
{
	if (s == NULL)
		return ;
	while (*s != '\0')
	{
		write(1, &*s, 1);
		s++;
	}
}

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

void	ft_signal_receiver(int sig)
{
	static int	i;

	if (sig == SIGUSR1 && i == 0)
	{
		ft_putstr("\nMessage delivered ");
		i = 1;
	}
	if (sig == SIGUSR2)
	{
		ft_putstr("---> Messagge arrived\n");
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
		//if (byte & (0x80 >> count))
		/* if ((byte >> count) & 1)
			if (kill(pid, SIGUSR1) == -1)
				exit(1);
		else
			if (kill(pid, SIGUSR2) == -1)
				exit(1);
		count++;
		usleep(100); */
	}
}

void	ft_send_str(char *str, int pid)
{
	int	i;

	i = -1;
	while (str[++i] != '\0')
		ft_send_bits(pid, str[i]);
	ft_send_bits(pid, '\0');
}

int	main(int argc, char *argv[])
{
	int	pid;

	if (argc != 3)
	{
		ft_putstr("Invalid number of arguments\n");
		exit(1);
	}
	signal(SIGUSR1, ft_signal_receiver);
	signal(SIGUSR2, ft_signal_receiver);
	pid = ft_atoi(argv[1]);
	ft_send_str(argv[2], pid);
}
