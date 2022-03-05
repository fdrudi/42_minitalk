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

int x = 0;

void	handler_one(int sig)
{
	sig = x;
	printf("\nQui tutto bene %c\n", sig);
}


int	main(int argc, char *argv[])
{
	char str[5] = "ciao";
	int	i = 0;

	struct sigaction sa = { 0 };
	sa.sa_flags = SA_RESTART;
	sa.sa_handler = &handler_one;
	sigaction(SIGUSR1, &sa, NULL);
	while (str[i] != '\0')
	{
		x = str[i];
		kill(getpid(), SIGUSR1);
		i++;
	}
	return (0);
}
