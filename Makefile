NAME = minishell

HEADER = includes/minishell.h 

CFLAGS = -g 

#LDFLAGS = -lreadline 

CC = gcc 

LIBFT = libraries/libft/libft.a

OBJS_DIR = objs
SRC_DIR = src
INCLUDE_DIR = includes
READLINE_DIR = $(shell brew --prefix readline)
READLINE_LIB = -lreadline -lhistory -L $(READLINE_DIR)/lib

INC := -I $(INCLUDE_DIR)

SRCS = main.c lexer.c is_check.c init_shell.c free.c handle_quote.c parser.c \
		builtins/echo.c builtins/env.c builtins/cd.c builtins/export.c \
		builtins/unset.c builtins/exit.c builtins/pwd.c signal.c builtins/export_utils.c \
		redirections.c expander.c executor.c error.c pipes.c pipes_utils.c heredoc.c \
		check_files.c expander_utils.c init_cmdtable.c

OBJS = $(addprefix $(OBJS_DIR)/,$(SRCS:.c=.o))

all: $(LIBFT) $(NAME)

$(OBJS_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INC) -c -o $@ $<

$(LIBFT):
	$(MAKE) -C libraries/libft

$(NAME): $(LIBFT) $(OBJS) 
	@$(CC) $(CFLAGS) $(INC) $(READLINE_LIB) $^ -o $(NAME)
	@echo "\033[92mFiles made 🤔\033[0m"

run: $(NAME)
	./$(NAME)

clean:
	@rm -rf $(OBJS_DIR)
	@make clean -C libraries/libft
	@echo "\033[1;34mA\033[1;31ml\033[1;32ml \033[1;33mc\033[1;30ml\033[1;35me\033[1;36ma\033[1;37mn\033[0m"

fclean:
	@rm -rf $(OBJS_DIR)
	@rm -f $(NAME)
	@make fclean -C libraries/libft
	@echo "\033[0;31mFiles killed💀❌\033[0m"

re:	fclean all

.PHONY: all clean fclean re