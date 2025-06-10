# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: apechkov <apechkov@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/23 17:22:15 by apechkov          #+#    #+#              #
#    Updated: 2024/05/29 17:51:53 by apechkov         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

################################################################################
#                                                                              #
#	                                Vars                                       #
#                                                                              #
################################################################################

CC = cc
CFLAGS = -Wall -Wextra -Werror
CLIENT_SRCS = client.c
SERVER_SRCS = server.c
LIBFT_PATH = libft
PRINTF_PATH = ./ft_printf
LIBFT = $(LIBFT_PATH)/libft.a
PRINTF = $(PRINTF_PATH)/libftprintf.a
CLIENT_NAME = client
SERVER_NAME = server
SILENT = @

################################################################################
#                                                                              #
#	                                Rules                                      #
#                                                                              #
################################################################################

all: $(CLIENT_NAME) $(SERVER_NAME)
	@echo "███╗░░░███╗██╗███╗░░██╗██╗████████╗░█████╗░██╗░░░░░██╗░░██╗"
	@echo "████╗░████║██║████╗░██║██║╚══██╔══╝██╔══██╗██║░░░░░██║░██╔╝"
	@echo "██╔████╔██║██║██╔██╗██║██║░░░██║░░░███████║██║░░░░░█████═╝░"
	@echo "██║╚██╔╝██║██║██║╚████║██║░░░██║░░░██╔══██║██║░░░░░██╔═██╗░"
	@echo "██║░╚═╝░██║██║██║░╚███║██║░░░██║░░░██║░░██║███████╗██║░╚██╗"
	@echo "╚═╝░░░░░╚═╝╚═╝╚═╝░░╚══╝╚═╝░░░╚═╝░░░╚═╝░░╚═╝╚══════╝╚═╝░░╚═╝"

$(CLIENT_NAME): $(CLIENT_SRCS) $(LIBFT) $(PRINTF)
	$(SILENT)$(CC) $(CFLAGS) -o $@ $(CLIENT_SRCS) -L$(LIBFT_PATH) -lft -L$(PRINTF_PATH) -lftprintf

$(SERVER_NAME): $(SERVER_SRCS) $(LIBFT)  $(PRINTF)
	$(SILENT)$(CC) $(CFLAGS) -o $@ $(SERVER_SRCS) -L$(LIBFT_PATH) -lft -L$(PRINTF_PATH) -lftprintf

$(LIBFT):
	$(SILENT)$(MAKE) -s -C $(LIBFT_PATH)  > /dev/null

$(PRINTF):
	$(SILENT)$(MAKE) -s -C $(PRINTF_PATH)  > /dev/null
clean:
	$(SILENT)$(MAKE) -s -C $(LIBFT_PATH) clean
	$(SILENT)$(MAKE) -s -C $(PRINTF_PATH) clean


fclean: clean
	$(SILENT)$(MAKE) -s -C $(LIBFT_PATH) fclean
	$(SILENT)$(MAKE) -s -C $(PRINTF_PATH) fclean
	$(SILENT)rm -f $(CLIENT_NAME) $(SERVER_NAME)

re: fclean all

.PHONY: all clean fclean re