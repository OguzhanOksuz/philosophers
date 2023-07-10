NAME = philo

CC = gcc

CFLAGS = -Wall -Wextra -Werror

SRCS = my_main.c		\
		 philo.c		\
		 ft_atoi.c		

OBJS = $(M_SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
	rm -rf $(M_OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all fclean clean re
