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

void	handler(int	sig)
{
	printf("%d", sig);
}

int	main(void)
{
	int	pid;

	pid = getpid();
	printf("PID : %d\n", pid);
	signal(SIGUSR1, handler);
	while (1)
		pause();

	return (0);
}
