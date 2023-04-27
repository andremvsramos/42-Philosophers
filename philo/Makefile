# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: andvieir <andvieir@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/24 12:17:44 by andvieir          #+#    #+#              #
#    Updated: 2023/04/27 10:45:44 by andvieir         ###   ########.fr        #
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
	utils_2.c \

#--------COMMANDS--------#
CC = clang
CFLAGS = -Wall -Wextra -Werror -pthread -g -fsanitize=thread
EXTRA = -pthread -fsanitize=thread -g
AR = ar rcs
RM = rm -rf

OBJ = ${SRC:.c=.o}

#---------RULES---------#
.c.o:
			$(CC) $(CFLAGS) -c -I $(HEADER) $< -o ${<:.c=.o}

all: 		$(NAME)

$(NAME): 	$(OBJ)
			$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

clean:
			@$(RM) $(OBJ) $(BONUS_OBJ)

fclean: 	clean
			@$(RM) $(NAME)

re: fclean all
