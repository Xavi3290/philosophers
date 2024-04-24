
NAME = philo
CC = cc
CFLAGS = -Wall -Werror -Wextra -lphtread
RM = rm -f
INCLUDE = philo.h Makefile

SRC = philo.c \
	  utils.c \
	  init.c \
	  actions.c
	  
OBJ := $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ) $(INCLUDE)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ)

%.o: %.c $(INCLUDE)
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	$(RM) $(OBJ) 

fclean: clean
	$(RM) $(NAME) 

re: fclean all

.PHONY: all clean fclean re