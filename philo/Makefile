NAME = philo

CC = gcc

CFLAGS = -Wall -Wextra -Werror

SRCS =	my_main.c		\
		init_philo.c	\
		utils.c			\
		threads.c		\
		my_free.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all fclean clean re
