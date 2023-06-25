CC = gcc
CFLAGS = -Wall -Wextra -Werror -I.

SRCS = $(shell find . -name "*.c")
OBJS = $(SRCS:.c=.o)
NAME = safeAlloc.a

all:
	$(CC) $(CFLAGS) -c $(SRCS)
	ar rcs $(NAME) $(OBJS)

re: fclean all

clean:
	rm -rf $(OBJS)

fclean:
	rm -rf $(OBJS) $(NAME)