/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anastasiia <anastasiia@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 15:44:15 by apechkov          #+#    #+#             */
/*   Updated: 2024/10/14 23:03:20 by anastasiia       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

t_message	g_mes;

void	send_act(int sig, siginfo_t *info, void *context)
{
	char	c;

	(void)sig;
	(void)context;
	c = *g_mes.data;
	if ((c >> g_mes.counter) & 1)
	{
		if (kill (info->si_pid, SIGUSR1) < 0)
			ft_printf("Fatal error: kill\n");
	}
	else
	{
		if (kill(info->si_pid, SIGUSR2) < 0)
			ft_printf("Fatal error: kill\n");
	}
	if (g_mes.counter == 0)
	{
		if (!c)
			exit(0);
		g_mes.data++;
		g_mes.counter = 7;
	}
	else
		g_mes.counter--;
}

int	signal_handler(void)
{
	struct sigaction	send;
	struct sigaction	empty;

	ft_bzero(&send, (unsigned long) sizeof(struct sigaction));
	ft_bzero(&empty, sizeof(struct sigaction));
	send.sa_sigaction = send_act;
	send.sa_flags = SA_SIGINFO;
	empty.sa_sigaction = send_act;
	empty.sa_flags = SA_SIGINFO;
	if ((sigaction(SIGUSR2, &empty, NULL) < 0)
		|| (sigaction(SIGUSR1, &send, NULL) < 0))
	{
		ft_printf("Fatal error: sigaction\n");
		return (0);
	}
	return (1);
}

int	main(int ac, char **av)
{
	if (ac != 3)
	{
		ft_printf("Usage: ./client [server_pid] [value]\n");
		return (1);
	}
	if (!signal_handler())
		return (1);
	g_mes.counter = 7;
	g_mes.data = av[2];
	g_mes.data[ft_strlen(g_mes.data)] = '\0';
	if (kill(ft_atoi(av[1]), SIGUSR1) < 0)
	{
		ft_printf("Fatal error: kill\n");
		return (1);
	}
	while (1)
		pause();
	return (0);
}
