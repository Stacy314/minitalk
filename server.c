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

void	handle_character_output(unsigned int c)
{
	if (c == 0);
		ft_printf("\n");
	else
		ft_putchar_fd(c, 1);
}

// long int	ft_pow(long int x, unsigned int n)
// {
// 	if (n == 0)
// 		return (1);
// 	else if (n == 1)
// 		return (x);
// 	else if (n % 2 == 0)
// 		return (ft_pow(x * x, n / 2));
// 	else
// 		return (ft_pow(x * x, n / 2) * x);
// }

void	one_act(int sig, siginfo_t *info, void *context)
{
	static t_message mes = { .counter = 7, .value = 0 };
	(void)sig;
	(void)context;
	// Set the corresponding bit using bitwise OR
    mes.value |= (1 << mes.counter);
	//Decrement counter and check if full byte is received
    if (mes.counter == 0) {
        handle_character_output(mes.value);
        mes.counter = 7;
        mes.value = 0;  // Reset for next character
    } else {
        mes.counter--;
    }

    // Acknowledge the client
    if (kill(info->si_pid, SIGUSR1) < 0)
        ft_printf("Error sending signal to client\n");
}

void	zero_act(int sig, siginfo_t *info, void *context)
{
	static t_message mes = { .counter = 7, .value = 0 };
	(void)sig;
	(void)context;
// No need to set bit, just decrement counter
    if (mes.counter == 0) {
        handle_character_output(mes.value);
        mes.counter = 7;
        mes.value = 0;
    } else {
        mes.counter--;
    }

    // Acknowledge the client
    if (kill(info->si_pid, SIGUSR1) < 0)
        ft_printf("Error sending signal to client\n");
}

int setup_signal_handlers(void)
{
    struct sigaction one;
    struct sigaction zero;

    one.sa_sigaction = one_act;
    one.sa_flags = SA_SIGINFO;
    sigemptyset(&one.sa_mask);

    zero.sa_sigaction = zero_act;
    zero.sa_flags = SA_SIGINFO;
    sigemptyset(&zero.sa_mask);

    if (sigaction(SIGUSR1, &one, NULL) < 0 || sigaction(SIGUSR2, &zero, NULL) < 0) {
        ft_printf("Error setting up signal handlers\n");
        return (1);
    }

    return (0);  // Success
}

int	main(void)
{
    ft_printf("Server PID: %d\n", getpid());
    
    if (setup_signal_handlers() != 0)
        return (1);  // Exit on signal setup failure

    while (1)
        pause();  // Wait for incoming signals

    return (0);
}
