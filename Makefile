NAME = minishell
SOURCES = main.c
OBJS = $(SOURCES:.c=.o)

CC = cc
RM = rm -f
CFLAGS = -Wall -Wextra -Werror
THREADS_LEAKS_FLAGS = -fsanitize=address -fno-omit-frame-pointer
READLINE_FLAGS = -lreadline

all: $(NAME)	

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(LEAKS_FLAGS) $(READLINE_FLAGS) $(OBJS) -o $(NAME)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean $(NAME)