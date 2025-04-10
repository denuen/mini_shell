NAME			= mini_shell
CC				= gcc
FLAGS			= -Wall -Wextra -Werror

SRCS_DIR		= srcs/
BUILT-IN_DIR	= $(SRCS_DIR)built-ins/
AST_DIR			= $(SRCS_DIR)data_structures/ast/
ENV_DIR			= $(SRCS_DIR)data_structures/env/
EXECUTOR_DIR	= $(SRCS_DIR)executor/
PARSING_DIR		= $(SRCS_DIR)parsing/
H_DIR			= includes
DIR_LIBFT		= libft
H_DIR_LIBFT		= libft/includes
LIBFT			= $(DIR_LIBFT)/libft.a

C_BUILT_INS		= cd.c display_utils.c echo.c env.c exit.c export.c pwd.c unset.c
C_AST			= ast.c ast_op.c
C_ENV			= env.c env_op.c
C_EXECUTOR		= executor.c operators.c redirections.c signals.c
C_PARSING		= commands.c errors.c expansion.c operators.c redirections.c wildcards.c \
					wildcards_utils.c ms_split.c ms_split_utils.c ms_split_checks.c \
					parsing.c parsing_utils.c path_utils.c
C_GENERAL		= main.c general_utils.c

SRCS			= $(addprefix $(BUILT-IN_DIR), $(C_BUILT_INS)) \
					$(addprefix $(AST_DIR), $(C_AST)) \
					$(addprefix $(ENV_DIR), $(C_ENV)) \
					$(addprefix $(EXECUTOR_DIR), $(C_EXECUTOR)) \
					$(addprefix $(PARSING_DIR), $(C_PARSING)) \
					$(addprefix $(SRCS_DIR), $(C_GENERAL))

OBJS			= $(SRCS:%.c=%.o)

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(FLAGS) $(OBJS) $(LIBFT) -lreadline -o $(NAME)

$(LIBFT):
	@$(MAKE) -C $(DIR_LIBFT) --silent

%.o: %.c
	$(CC) $(FLAGS) -I $(H_DIR) -I $(H_DIR_LIBFT) -c $< -o $@

clean:
	rm -f $(OBJS)
	@$(MAKE) -C $(DIR_LIBFT) clean --silent

fclean: clean
	rm -f $(NAME)
	@$(MAKE) -C $(DIR_LIBFT) fclean --silent

re: fclean all

.PHONY: all clean fclean re
