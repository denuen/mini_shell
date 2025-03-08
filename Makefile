NAME		= mini_shell
CC			= gcc
FLAGS		= -Wall -Wextra -Werror
SRCS_DIR	= srcs/
H_DIR		= includes
DIR_LIBFT	= libft
H_DIR_LIBFT = libft/includes
LIBFT		= $(DIR_LIBFT)/libft.a

CFILES		= # Add files.c here
SRCS		= $(addprefix $(SRCS_DIR), $(CFILES))
OBJS		= $(SRCS:%.c=%.o)

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(FLAGS) $(OBJS) $(LIBFT) -o $(NAME)

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
