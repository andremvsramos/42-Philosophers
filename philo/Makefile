# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: marvin <marvin@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/24 12:17:44 by andvieir          #+#    #+#              #
#    Updated: 2023/08/20 14:53:37 by marvin           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= philo
HEADER		= phi.h

#----------DIRS----------#

SRC =	init.c \
	main.c \
	states.c \
	threads.c \
	utils.c \
	utils_libft.c \
	mutex_utils.c \
	routines.c \
	god.c \
	cleanup.c \

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


#---------RULES---------#
.c.o:
			@$(CC) $(CFLAGS) -c -I $(HEADER) $< -o ${<:.c=.o}

all: 		$(NAME)
			@clear
			@echo "\033[1;32m\v\t\t\tCompiled without Fsanitizer!"
			@echo "\033[0;36m"$(PROJECT)


$(NAME): 	$(OBJ)
			@$(CC) $(CFLAGS) $(OBJ) -o $(NAME)


clean:
			@$(RM) $(OBJ) $(BONUS_OBJ)

fclean: 	clean
			@$(RM) $(NAME)
			@clear

re:	fclean all
