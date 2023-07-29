NAME = philo

CC = gcc

CFLAGS = -Wall -Wextra -Werror

CFLAGS_THREAD = -Wall -Wextra -Werror -fsanitize=thread

CFLAGS_ADDRESS = -Wall -Wextra -Werror -fsanitize=address

SRCS =	my_main.c		\
		init_philo.c	\
		utils.c			\
		threads.c		

OBJS = $(SRCS:.c=.o)

all: $(NAME)

data: fclean $(OBJS)
	$(CC) $(CFLAGS_THREAD) $(OBJS) -o $(NAME)

adres: fclean $(OBJS) 
	$(CC) $(CFLAGS_ADDRESS) $(OBJS) -o $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all fclean clean re
