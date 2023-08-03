NAME = minishell
SOURCES = main.c parser.c lexer.c prints.c executor.c pipes.c redirections.c error_handling.c builtins_child.c builtins_parent.c
OBJ_DIR = obj
OBJS = $(addprefix $(OBJ_DIR)/, $(SOURCES:.c=.o))
LIBFT = libft/libft.a
INCLUDES = -I libft/includes

CC = cc
RM = rm -f
CFLAGS = -Wall -Wextra -Werror
LEAKS_FLAGS = -fsanitize=address -fno-omit-frame-pointer
READLINE_FLAGS = -lreadline

all: $(NAME)	

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(READLINE_FLAGS) $(OBJS) $(LIBFT) $(INCLUDES) -o $(NAME)

$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
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