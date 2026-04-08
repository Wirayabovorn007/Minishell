NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror

INCLUDES = -Iinclude

OBJ_DIR = obj

SRCS = \
src/main.c \
\
src/parser/tokenize.c \
src/parser/tokenize_utils.c \
src/parser/parser.c \
src/parser/parser_utils.c \
src/parser/build_cmd.c \
\
src/builtin/echo.c \
src/builtin/cd.c \
src/builtin/pwd.c \
src/builtin/export.c \
src/builtin/unset.c \
src/builtin/env.c \
src/builtin/exit.c \
\
src/exec/execute.c \
src/exec/pipe.c \
src/exec/redirection.c \
src/exec/heredoc.c \
\
src/signal/signal.c \
\
src/utils/utils.c \
src/utils/free_utils.c \
src/utils/ft_split.c

OBJS = $(SRCS:src/%.c=$(OBJ_DIR)/%.o)

LIBS = -lreadline

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME)

$(OBJ_DIR)/%.o: src/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re