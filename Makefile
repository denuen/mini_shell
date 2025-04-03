NAME		= mini_shell
CC			= gcc
FLAGS		= -g -Wall -Wextra -Werror
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

CFILES		 = general_utils.c main.c ms_split.c ms_split_utils.c \
			$(BUILT-IN_DIR)cd.c $(BUILT-IN_DIR)display_utils.c $(BUILT-IN_DIR)echo.c $(BUILT-IN_DIR)env.c \
			$(BUILT-IN_DIR)exit.c $(BUILT-IN_DIR)export.c $(BUILT-IN_DIR)pwd.c $(BUILT-IN_DIR)unset.c \
			$(AST_DIR)ast.c $(AST_DIR)ast_op.c $(ENV_DIR)env.c $(ENV_DIR)env_op.c \
			$(EXECUTOR_DIR)executor.c $(EXECUTOR_DIR)operators.c $(EXECUTOR_DIR)redirections.c $(EXECUTOR_DIR)signals.c \
			$(PARSING_DIR)commands.c $(PARSING_DIR)errors.c $(PARSING_DIR)expansion.c $(PARSING_DIR)operations.c \
			$(PARSING_DIR)parsing.c $(PARSING_DIR)parsing_utils.c $(PARSING_DIR)redirections.c \
			$(PARSING_DIR)wildcard.c $(PARSING_DIR)wildcard_utils.c

SRCS		= $(addprefix $(SRCS_DIR), general_utils.c main.c ms_split.c ms_split_utils.c) \
			$(BUILT-IN_DIR)cd.c $(BUILT-IN_DIR)display_utils.c $(BUILT-IN_DIR)echo.c $(BUILT-IN_DIR)env.c \
			$(BUILT-IN_DIR)exit.c $(BUILT-IN_DIR)export.c $(BUILT-IN_DIR)pwd.c $(BUILT-IN_DIR)unset.c \
			$(AST_DIR)ast.c $(AST_DIR)ast_op.c $(ENV_DIR)env.c $(ENV_DIR)env_op.c \
			$(EXECUTOR_DIR)executor.c $(EXECUTOR_DIR)operators.c $(EXECUTOR_DIR)redirections.c $(EXECUTOR_DIR)signals.c \
			$(PARSING_DIR)commands.c $(PARSING_DIR)errors.c $(PARSING_DIR)expansion.c $(PARSING_DIR)operations.c \
			$(PARSING_DIR)parsing.c $(PARSING_DIR)parsing_utils.c $(PARSING_DIR)redirections.c \
			$(PARSING_DIR)wildcard.c $(PARSING_DIR)wildcard_utils.c

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
