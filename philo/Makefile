# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: xroca-pe <xroca-pe@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/25 12:03:58 by xroca-pe          #+#    #+#              #
#    Updated: 2024/05/07 13:27:04 by xroca-pe         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
CC = cc
CFLAGS = -Wall -Werror -Wextra 
RM = rm -f
INCLUDE = philo.h Makefile

SRC = philo.c \
	  utils.c \
	  init.c \
	  actions.c \
	  actions2.c
	  
OBJ := $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ) $(INCLUDE)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) -lpthread

%.o: %.c $(INCLUDE)
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	$(RM) $(OBJ) 

fclean: clean
	$(RM) $(NAME) 

re: fclean all

.PHONY: all clean fclean re