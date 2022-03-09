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

#include "minitalk.h"

void	ft_handler(int sig, siginfo_t *info, void *ucontext)
{
	static char	c;
	static int	bit;
	static int	client_pid;

	(void)ucontext;
	if (info->si_pid)
		client_pid = info->si_pid;
	if (sig == SIGUSR1)
		c |= (0x80 >> bit);
	bit++;
	if (bit == 8)
	{
		if (c == '\0')
		{
			ft_putchar_fd(c, 1);
			if (kill(client_pid, SIGUSR2) == -1)
				exit(1);
		}
		else
			ft_putchar_fd(c, 1);
		bit = 0;
		c = 0;
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
	ft_putstr_fd("PID : ", 1);
	ft_putnbr_fd(pid, 1);
	ft_putchar_fd('\n', 1);
	while (1)
		pause();
	return (0);
}
