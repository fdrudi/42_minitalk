/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdrudi <fdrudi@student.42roma.it>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 10:12:38 by fdrudi            #+#    #+#             */
/*   Updated: 2022/03/06 10:12:38 by fdrudi           ###   ########.fr       */
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

void	ft_putnbr(int n)
{
	if (n == -2147483648)
	{
		write(1, "-", 1);
		write(1, "2", 1);
		n = 147483648;
	}
	if (n < 0)
	{
		write(1, "-", 1);
		n *= -1;
	}
	if (n >= 10)
	{
		ft_putnbr(n / 10);
		ft_putnbr(n % 10);
	}
	else
	{
		n = n + 48;
		write(1, &n, 1);
	}
}

void	ft_handler(int	sig, siginfo_t *info, void *ucontext)
{
	static char	c = 0xFF;
	static int	bit = 0;
	static int	client_pid = 0;

	(void)ucontext;
	if ((info)->si_pid)
		client_pid = info->si_pid;
	if (sig == SIGUSR1)
		c |= 0x80 >> bit;
	else if (sig == SIGUSR2)
		c ^= 0x80 >> bit;
	bit++;
	if (bit == 8)
	{
		if (!c)
		{
			write(1, &c, 1);
			if (kill(client_pid, SIGUSR2) == -1)
				exit(1);
		}
		else
			write(1, &c, 1);
		bit = 0;
		c = 0xFF;
	}
	if (kill(client_pid, SIGUSR1) == -1)
		exit(1);
}

int	main(void)
{
	int					pid;
	struct sigaction	sa;

	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = ft_handler;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	pid = getpid();
	ft_putstr("PID : ");
	ft_putnbr(pid);
	write(1, "\n", 1);
	while (1)
		pause();
	return (0);
}
