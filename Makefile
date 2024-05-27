NAME		=	push_swap
SRCS		=	main.c \
				sources/parsing.c \
				sources/swap.c \
				sources/push.c \
				sources/rotate.c \
				sources/reverse_rotate.c
OBJS		=	$(SRCS:.c=.o)
OBJS_DIR 	=	objects
OBJS_PATH	=	$(addprefix $(OBJS_DIR)/, $(OBJS))
LIBFT		=	libft
CC			=	gcc
CFLAGS		=	-Wall -Wextra -Werror -I. -I$(LIBFT) -L$(LIBFT) -lft

$(OBJS_DIR)/%.o: %.c
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS_PATH)
	make bonus -C $(LIBFT)
	$(CC) $(OBJS_PATH) -o $(NAME) $(CFLAGS)

all: $(NAME)

clean:
	make clean -C $(LIBFT)
	rm -f $(OBJS)
	rm -rf $(OBJS_DIR)

fclean: clean
	make fclean -C $(LIBFT)
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
