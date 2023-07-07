NAME = philo

BNAME = philo_bonus

CC = gcc

CFLAGS = -Wall -Wextra -Werorr

#-------MANDATORY-----------

M_SRCS = main.c	\

M_OBJS = $(M_SRCS:.c=.o)

#-------BONUS---------------

B_SRCS = 

B_OBJS = $(B_SRCS:.c=.o)

#---------------------------

mandatory: $(NAME)

bonus: $(BNAME)

all: mandatory bonus

$(NAME): $(M_OBJS)
	$(CC) $(CFLAGS) $(M_OBJS) -o $(NAME)

$(BNAME): $(B_OBJS)
	$(CC) $(CFLAGS) $(B_OBJS) -o $(BNAME)

clean:
	rm -rf $(M_OBJS)
	rm -rf $(B_OBJS)

fcelan: clean
	rm -rf $(NAME)
	rm -rf $(BNAME)

re: fclean all

.PHONY: all clean re bonus mandatory
