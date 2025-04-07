NAME		= mini_shell
CC			= gcc
FLAGS		= -Wall -Wextra -Werror
SRCS_DIR	= srcs/
BUILT-IN_DIR = $(SRCS_DIR)built-ins/
AST_DIR = $(SRCS_DIR)data_structures/ast/
ENV_DIR = $(SRCS_DIR)data_structures/env/
EXECUTOR_DIR = $(SRCS_DIR)executor/
PARSING_DIR = $(SRCS_DIR)parsing/
H_DIR		= includes
DIR_LIBFT	= libft
H_DIR_LIBFT = libft/includes
LIBFT		= $(DIR_LIBFT)/libft.a

BUILT_INS = cd.c display_utils.c echo.c env.c exit.c export.c pwd.c unset.c

AST = ast.c ast_op.c

ENV = env.c env_op.c

EXECUTOR = executor.c operators.c redirections.c signals.c

PARSING = commands.c errors.c expansion.c operators.c redirections.c wildcards.c wildcards_utils.c ms_split.c \
		ms_split_utils.c ms_split_checks.c parsing.c parsing_utils.c

SRCS		= $(addprefix $(BUILT-IN_DIR), $(BUILT_INS)) \
			$(addprefix $(AST_DIR), $(AST)) \
			$(addprefix $(ENV_DIR), $(ENV)) \
			$(addprefix $(EXECUTOR_DIR), $(EXECUTOR)) \
			$(addprefix $(PARSING_DIR), $(PARSING)) \
			$(SRCS_DIR)main.c $(SRCS_DIR)general_utils.c

OBJS		= $(SRCS:%.c=%.o)

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(FLAGS) $(OBJS) $(LIBFT) -lreadline -o $(NAME)

$(LIBFT):
	@$(MAKE) -C $(DIR_LIBFT)

%.o: %.c
	$(CC) $(FLAGS) -I $(H_DIR) -I $(H_DIR_LIBFT) -c $< -o $@

clean:
	rm -f $(OBJS)
	@$(MAKE) -C $(DIR_LIBFT) clean

fclean: clean
	rm -f $(NAME)
	@$(MAKE) -C $(DIR_LIBFT) fclean

re: fclean all

.PHONY: all clean fclean re
