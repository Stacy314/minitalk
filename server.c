/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apechkov <apechkov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 15:44:06 by apechkov          #+#    #+#             */
/*   Updated: 2024/09/20 18:38:38 by apechkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	handle_character_output(int c)
{
	if (g_mes.value == 0)  // Якщо кінець строки, вивести новий рядок
		ft_printf("\n");
	else
		ft_putchar_fd(c, 1);  // Використовуємо вашу функцію для виводу символу
	g_mes.counter = 7;
	g_mes.value = 0;
}

long int	ft_pow(long int x, unsigned int n)
{
	if (n == 0)
		return (1);
	else if (n == 1)
		return (x);
	else if (n % 2 == 0)
		return (ft_pow(x * x, n / 2));
	else
		return (ft_pow(x * x, n / 2) * x);
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
			exit (1);
		}
		return ;
	}
	g_mes.value += ft_pow(2, g_mes.counter);
	if (g_mes.counter == 0)
		handle_character_output(g_mes.value);
	else
		g_mes.counter--;
	kill (info->si_pid, SIGUSR1);
}

void	zero_act(int sig, siginfo_t *info, void *context)
{
	(void)sig;
	(void)context;
	if (g_mes.counter == 0)
		handle_character_output(g_mes.value);
	else
		g_mes.counter--;
	kill (info->si_pid, SIGUSR1);
}

int	main(void)
{
	struct sigaction	one;
	struct sigaction	zero;

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
