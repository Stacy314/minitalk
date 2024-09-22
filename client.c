/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anastasiia <anastasiia@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 15:44:15 by apechkov          #+#    #+#             */
/*   Updated: 2024/09/21 16:55:32 by anastasiia       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	send_act(int sig, siginfo_t *info, void *context)
{
	char	c;

	(void)sig;
	(void)context;
	c = *g_mes.data;
	if ((c >> g_mes.counter) & 0x01)
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

// int	check_pid(char *c_pid)
// {
// 	int		i_pid;
// 	char	*compare_pid;

// 	i_pid = ft_atoi(c_pid);
// 	compare_pid = ft_itoa(i_pid);
// 	if (ft_strlen(c_pid) != ft_strlen(compare_pid))
// 		return (0);
// 	return (1);
// }

/*Sets up signal handlers for the SIGUSR1 and SIGUSR2 signals using the 
sigaction system call.*/
int setup_signal_handlers(void)
{
    struct sigaction send;
    struct sigaction empty;

    send.sa_sigaction = send_act;
    send.sa_flags = SA_SIGINFO;
    // if (sigaction(SIGUSR1, &send, NULL) < 0)
    // {
    //     ft_printf("Fatal error: sigaction\n");
    //     return (0);
    // }
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

int main(int ac, char **av)
{
    if (ac != 3)
    {
        ft_printf("Usage: ./client [server_pid] [value]\n");
        return (1);
    }
    if (!setup_signal_handlers())
        return (1);
    g_mes.counter = 7;
    g_mes.data = av[2];
    g_mes.data[ft_strlen(g_mes.data)] = '\0';

    // Check server PID
    // if (!check_pid(av[1]))
    // {
    //     ft_printf("Fatal error: Wrong PID\n");
    //     return (1);
    // }

    // Send initial signal to server
    if (kill(ft_atoi(av[1]), SIGUSR1) < 0)
    {
        ft_printf("Fatal error: kill\n");
        return (1);
    }
    while (1)
        pause();
    return (0);
}
