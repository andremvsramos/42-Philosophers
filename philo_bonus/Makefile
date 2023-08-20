# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: marvin <marvin@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/24 12:17:44 by andvieir          #+#    #+#              #
#    Updated: 2023/08/20 15:08:47 by marvin           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= philo_bonus
HEADER		= phi_bonus.h

#----------DIRS----------#

SRC =	init_bonus.c \
	main_bonus.c \
	states_bonus.c \
	processes_bonus.c \
	utils_bonus.c \
	utils_libft_bonus.c \
	ft_itoa_bonus.c \
	god_bonus.c \
	cleanup_bonus.c \

#--------COMMANDS--------#
CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread -g
AR = ar rcs
RM = rm -rf

OBJ = ${SRC:.c=.o}

#---------ASCII---------#
PROJECT =																	\
"																		\n	\
\t______  _     _ _			_						\n	\
\t|  __ \| |   (_) |                     | |						\n	\
\t| |__) | |__  _| | ___  ___  ___  _ __ | |__   ___ _ __ ___		\n	\
\t|  ___/| '_ \| | |/ _ \/ __|/ _ \| '_ \| '_ \ / _ \ '__/ __|	\n	\
\t| |    | | | | | | (_) \__ \ (_) | |_) | | | |  __/ |  \__ \	\n	\
\t|_|    |_| |_|_|_|\___/|___/\___/| .__/|_| |_|\___|_|  |___/	\n	\
\t				 | |							\n	\
\t				 |_|							\n	\
"

LG =

#---------RULES---------#
.c.o:
			@$(CC) $(CFLAGS) -c -I $(HEADER) $< -o ${<:.c=.o}

all: 		$(NAME)
			@clear
			@echo "\033[1;32m\v\t\t\t\tCompiled!"
			@echo "\033[0;36m"$(PROJECT)


$(NAME): 	$(OBJ)
			@$(CC) $(CFLAGS) $(OBJ) -o $(NAME)


clean:
			@$(RM) $(OBJ) $(BONUS_OBJ)

fclean: 	clean
			@$(RM) $(NAME)
			@clear

re:	fclean all
