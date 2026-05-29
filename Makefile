NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror

INCLUDES = -Iinclude
OBJ_DIR = obj

SRCS = \
src/main.c \
src/parser/tokenize_utils.c \
src/parser/tokenize.c \
src/parser/parser.c \
src/parser/build_cmd.c \
src/parser/syntax_check.c \
src/parser/quote_utils.c \
src/parser/env_utils.c \
src/parser/expand.c \
src/parser/quote_tokenize.c \
src/builtins/builtin.c \
src/builtins/echo.c \
src/builtins/pwd.c \
src/builtins/env.c \
src/builtins/cd.c \
src/builtins/exit.c \
src/builtins/export.c \
src/builtins/unset.c \
src/builtins/builtins_utils.c \
src/builtins/export_utils.c \
utils/array_utils.c \
utils/free_utils.c \
utils/ft_itoa.c \
utils/ft_split.c \
utils/ft_strncmp.c \
utils/string_utils.c \
utils/utils.c \
utils/exec_utils.c \
src/signal/signal.c \
src/execute/execute.c \
src/execute/redirect.c \
src/execute/heredoc.c \

OBJS = $(SRCS:%.c=$(OBJ_DIR)/%.o)

LIBS = -lreadline

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME)

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re