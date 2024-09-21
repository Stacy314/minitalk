/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apechkov <apechkov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 15:43:50 by apechkov          #+#    #+#             */
/*   Updated: 2024/09/20 17:43:27 by apechkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include "libft/libft.h"

# include <unistd.h>
# include <signal.h>
# include <stdlib.h>
//#include <asm-generic/siginfo.h>
//#include <asm-generic/signal.h>

typedef struct s_message
{
	//char	*data;   // Використовується для зберігання рядка (message) в клієнті
	int		counter; // Використовується для лічильника бітів у передачі/отриманні
	int		value;   // Використовується на сервері для зберігання декодованого символу
}	t_message;

//t_message	g_mes;

#endif