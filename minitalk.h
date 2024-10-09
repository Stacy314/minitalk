/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anastasiia <anastasiia@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 15:44:15 by apechkov          #+#    #+#             */
/*   Updated: 2024/10/09 13:30:39 by anastasiia       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include "../libft/libft.h"
# include <signal.h>

/*  int     counter;   // Лічильник бітів
    int     value;     // Тимчасова змінна для складання символа
    char    *data;    // Строка, яку потрібно надіслати*/

typedef struct s_message
{
	int		counter;
	int		value;
	char	*data;
}	t_message;

#endif
