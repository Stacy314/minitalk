/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apechkov <apechkov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 15:44:15 by apechkov          #+#    #+#             */
/*   Updated: 2024/09/20 18:44:56 by apechkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void send_bit(pid_t server_pid, int bit)
{
    if (bit == 1)
        kill(server_pid, SIGUSR1);
    else
        kill(server_pid, SIGUSR2);
}

void send_next_bit(pid_t server_pid, siginfo_t *info, void *context)
{
    static t_message mes;

    (void)sig;
    (void)context;

    if (mes.counter == 0) {  // All bits of current char sent, move to next
        if (*mes.data == '\0') {  // If end of string, terminate
            exit(0);
        }
        mes.data++;
        mes.counter = 7;
    } else {
        mes.counter--;
    }

    // Send the next bit
    send_bit(server_pid, (*mes.data >> mes.counter) & 0x01);
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

int setup_signal_handlers(void)
{
    struct sigaction send;
    //struct sigaction empty;

    // Set up handler for SIGUSR1
    send.sa_sigaction = send_next_bit;
    send.sa_flags = SA_SIGINFO;
    sigemptyset(&send.sa_mask); //new
    if (sigaction(SIGUSR1, &send, NULL) < 0)
    {
        ft_printf("Error setting up signal handlers\n");
        return (1);
    }

    // // Set up handler for SIGUSR2
    // empty.sa_sigaction = send_act;
    // empty.sa_flags = SA_SIGINFO;
    // if (sigaction(SIGUSR2, &empty, NULL) < 0)
    // {
    //     ft_printf("Fatal error: sigaction\n");
    //     return (1);
    // }

    return (0); // Success
}

int validate_pid(char *pid_str)
{
    int i = 0;

    while (pid_str[i]) {
        if (!ft_isdigit(pid_str[i]))
            return (0);  // Not a valid number
        i++;
    }
    return (1);  // Valid PID
}

int main(int ac, char **av)
{
    pid_t server_pid;

    if (ac != 3)
    {
        ft_printf("Usage: ./client [server_pid] [value]\n");
        return (1);
    }
    if (!validate_pid(argv[1]))
    {
        ft_printf("Invalid PID\n");
        return (1);
    }
    server_pid = ft_atoi(argv[1]);

    if (setup_signal_handlers() != 0)
        return (1); // Error in signal setup
    t_message mes;
    mes.data = argv[2];
    mes.counter = 7;
    send_bit(server_pid, (*mes.data >> mes.counter) & 0x01);  // Send first bit
    // Check server PID
    // if (!check_pid(av[1]))
    // {
    //     ft_printf("Fatal error: Wrong PID\n");
    //     return (1);
    // }

    // Send initial signal to server
    // if (kill(ft_atoi(av[1]), SIGUSR1) < 0)
    // {
    //     ft_printf("Fatal error: kill\n");
    //     return (1);
    // }
    while (1)
        pause();
    return (0);
}
// int	main(int ac, char **av)
// {
// 	struct sigaction	send;
// 	struct sigaction	empty;

// 	if (ac != 3)
// 	{
// 		ft_printf("Usage: ./client [server_pid] [value]\n");
// 		return (1);
// 	}
// 	send.sa_sigaction = send_act;
// 	send.sa_flags = SA_SIGINFO;
// 	if (sigaction(SIGUSR1, &send, NULL) < 0)
// 	{
// 		ft_printf("Fatal error: sigaction\n");
// 		return (1);
// 	}
// 	empty.sa_sigaction = send_act;
// 	empty.sa_flags = SA_SIGINFO;
// 	if (sigaction(SIGUSR2, &empty, NULL) < 0)
// 	{
// 		ft_printf("Fatal error: sigaction\n");
// 		return (1);
// 	}
// 	g_mes.counter = 7;
// 	g_mes.data = av[2];
// 	g_mes.data[ft_strlen(g_mes.data)] = '\0';
// 	if (!check_pid(av[1]))
// 	{
// 		ft_printf("Fatal error: Wrong PID\n");
// 		return (1);
// 	}
// 	if (kill(ft_atoi(av[1]), SIGUSR1) < 0)
// 		ft_printf("Fatal error: kill\n");
// 	while (1)
// 		pause();
// 	return (0);
// }
