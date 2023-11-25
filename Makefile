NAME	:= minishell
CC		:= gcc 
INCLUDE	:= ./includes
CFLAGS	:= -ggdb -I $(INCLUDE) -I ./libft
LIBFT	= libft
FLAGS	= -Wall -Wextra -Werror

SRCDIR	:= src
SRC		:= src/builtin/builtin.c \
			src/builtin/run_builtin.c \
			src/builtin/run_builtin1.c \
			src/builtin/run_builtin2.c \
			src/builtin/run_builtin3.c \
			src/check/check.c \
			src/check/check_utils.c \
			src/dup2/dup2_fd.c \
			src/exec/exec_free.c \
			src/exec/exec_free2.c \
			src/exec/exec.c \
			src/exec/run_execve.c \
			src/exec/run_execve1.c \
			src/exec/single_or_multi_command.c \
			src/expander/expander.c \
			src/files/create_files_utils.c \
			src/files/create_files.c \
			src/heredoc/heredoc_utils.c \
			src/heredoc/heredoc.c \
			src/lexer/lexer.c \
			src/main/env.c \
			src/main/main.c \
			src/parser/parser.c \
			src/parser/parser_utils.c \
			src/parser/parser_utils_others.c \
			src/parser/welcome_to_parse.c \
			src/signal/signal.c \

OBJDIR	:= ./objectives
OBJ		:= $(SRC:%.c=$(OBJDIR)/%.o)

all: $(NAME)

$(NAME): $(OBJ)
	@echo "Compiling..."
	@make -C $(LIBFT)
	@cp libft/libft.a .
	@$(CC) $(FLAGS) $(CFLAGS) $(OBJ) libft.a -lreadline -o $@
	@echo "Done!"
	@echo  "░░██╗██╗██████╗░"
	@echo  "░██╔╝██║╚════██╗"
	@echo  "██╔╝░██║░░███╔═╝"
	@echo  "███████║██╔══╝░░"
	@echo  "╚════██║███████╗"
	@echo  "░░░░░╚═╝╚══════╝"

$(OBJDIR)/%.o: %.c
	@mkdir -p $(@D)
	@$(CC) $(FLAGS) $(CFLAGS) -c $< -o $@

clean:
	@echo "Cleaning..."
	@make clean -C $(LIBFT)
	@rm -rf libft.a
	@rm -rf $(OBJDIR)

fclean:
	@echo "Cleaning..."
	@make fclean -C $(LIBFT)
	@rm -rf libft.a
	@rm -rf $(OBJDIR)
	@rm -f $(NAME)

valgrind:
	valgrind --leak-check=full --show-leak-kinds=all ./$(NAME)

norm:
	norminette libft

re:	fclean all