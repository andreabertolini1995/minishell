NAME = minishell
SRCDIR = src
SOURCES = $(wildcard $(SRCDIR)/**/*.c $(SRCDIR)/*.c)
OBJ_DIR = obj
OBJS = $(patsubst $(SOURCES)/%.c,$(OBJ_DIR)/%.o,$(SOURCES))
LIBFT = libft/libft.a
INCLUDES = -I libft/includes -I include -g3 -lreadline

CC = cc
RM = rm -f
CFLAGS = -Wall -Wextra -Werror
LEAKS_FLAGS = -fsanitize=address -fno-omit-frame-pointer
READLINE_FLAGS = -lreadline

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(READLINE_FLAGS) $(OBJS) $(LIBFT) $(INCLUDES) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRCDIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	make -C libft

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

clean:
	make -C libft clean
	$(RM) -r $(OBJ_DIR)

fclean: clean
	make -C libft fclean
	$(RM) $(NAME)

re: fclean $(NAME)