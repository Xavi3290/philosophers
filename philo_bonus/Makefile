NAME = philo_bonus
CC = cc
CFLAGS = -Wall -Werror -Wextra -lphtread
RM = rm -f
INCLUDE = philo_bonus.h Makefile

SRC = philo_bonus.c \
	  utils_bonus.c \
	  init_bonus.c \
	  actions_bonus.c
	  
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