/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anastasiia <anastasiia@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 15:44:06 by apechkov          #+#    #+#             */
/*   Updated: 2024/10/09 13:22:03 by anastasiia       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

t_message	g_mes;

void	save_char_to_buffer(char c)
{
	static char	*buffer = NULL;
	static int	length = 0;
	char		*new_buffer;
	int			i;

	new_buffer = (char *)malloc(sizeof(char) * (length + 2));
	if (!new_buffer)
	{
		ft_printf("Fatal error: malloc\n");
		exit(1);
	}
	i = -1;
	while (++i < length)
		new_buffer[i] = buffer[i];
	new_buffer[length] = c;
	new_buffer[length + 1] = '\0';
	free(buffer);
	buffer = new_buffer;
	length++;
	if (c == '\0')
	{
		ft_printf("%s\n", buffer);
		buffer = NULL;
		length = 0;
	}
}

void	one_act(int sig, siginfo_t *info, void *context)
{
	(void)sig;
	(void)context;
	if (g_mes.counter == 7)
	{
		if (kill(info->si_pid, SIGUSR1) < 0)
		{
			ft_printf("Fatal error: kill\n");
			exit(1);
		}
		return ;
	}
	g_mes.value += (1 << g_mes.counter);
	if (g_mes.counter == 0)
	{
		save_char_to_buffer(g_mes.value);
		g_mes.counter = 7;
		g_mes.value = 0;
	}
	else
		g_mes.counter--;
	kill(info->si_pid, SIGUSR1);
}

void	zero_act(int sig, siginfo_t *info, void *context)
{
	(void)sig;
	(void)context;
	if (g_mes.counter == 0)
	{
		save_char_to_buffer(g_mes.value);
		g_mes.counter = 7;
		g_mes.value = 0;
	}
	else
		g_mes.counter--;
	kill (info->si_pid, SIGUSR1);
}

int	main(void)
{
	struct sigaction	one;
	struct sigaction	zero;

	sigemptyset(&one.sa_mask);
	sigemptyset(&zero.sa_mask);
	ft_printf("Server PID: %d\n", getpid());
	one.sa_sigaction = one_act;
	one.sa_flags = SA_SIGINFO;
	zero.sa_sigaction = zero_act;
	zero.sa_flags = SA_SIGINFO;
	g_mes.counter = 7;
	g_mes.value = 0;
	if (sigaction(SIGUSR1, &one, NULL) < 0)
	{
		ft_printf("Fatal error: sigaction\n");
		return (1);
	}
	if (sigaction(SIGUSR2, &zero, NULL) < 0)
	{
		ft_printf("Fatal error: sigaction\n");
		return (1);
	}
	while (1)
		pause();
	return (0);
}
