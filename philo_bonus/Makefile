# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: xavi <xavi@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/25 12:05:21 by xroca-pe          #+#    #+#              #
#    Updated: 2024/05/02 18:07:06 by xavi             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo_bonus
CC = cc
CFLAGS = -Wall -Werror -Wextra
RM = rm -f
INCLUDE = philo_bonus.h Makefile

SRC = philo_bonus.c \
	  utils_bonus.c \
	  init_bonus.c \
	  actions_bonus.c
	  
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