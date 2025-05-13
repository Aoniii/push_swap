NAME			=	push_swap
NAME_BONUS		=	checker
SRCS			=	main.c \
					sources/stack/stack_clear.c \
					sources/stack/stack_delone.c \
					sources/stack/stack_new.c \
					sources/parsing.c \
					sources/creat.c \
					sources/swap.c \
					sources/push.c \
					sources/rotate.c \
					sources/reverse_rotate.c \
					sources/sort.c \
					sources/utils.c \
					sources/sort_big.c \
					sources/utils2.c \
					sources/calculate.c
SRCS_BONUS		=	main_bonus.c \
					sources/stack/stack_clear.c \
					sources/stack/stack_delone.c \
					sources/stack/stack_new.c \
					sources/parsing.c \
					sources/creat.c \
					sources/swap.c \
					sources/push.c \
					sources/rotate.c \
					sources/reverse_rotate.c \
					sources/utils.c \
					sources/utils2.c \
					get_next_line/get_next_line_bonus.c \
					get_next_line/get_next_line_utils_bonus.c \
					bonus/checker_bonus.c
OBJS			=	$(SRCS:.c=.o)
OBJS_BONUS		=	$(SRCS_BONUS:.c=.o)
OBJS_DIR 		=	objects
OBJS_PATH		=	$(addprefix $(OBJS_DIR)/, $(OBJS))
OBJS_PATH_BONUS	=	$(addprefix $(OBJS_DIR)/, $(OBJS_BONUS))
LIBFT			=	libft
GNL				=	get_next_line
CC				=	gcc
CFLAGS			=	-Wall -Wextra -Werror -I. -I$(LIBFT) -L$(LIBFT) -lft

$(OBJS_DIR)/%.o: %.c
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS_PATH)
	make bonus -C $(LIBFT)
	$(CC) $(OBJS_PATH) -o $(NAME) $(CFLAGS)

$(NAME_BONUS): $(OBJS_PATH_BONUS)
	make bonus -C $(LIBFT)
	$(CC) $(OBJS_PATH_BONUS) -o $(NAME_BONUS) $(CFLAGS)

all: $(NAME)

clean:
	make clean -C $(LIBFT)
	rm -f $(OBJS)
	rm -f $(OBJS_BONUS)
	rm -rf $(OBJS_DIR)

fclean: clean
	make fclean -C $(LIBFT)
	rm -f $(NAME)
	rm -f $(NAME_BONUS)

re: fclean all

bonus: $(NAME_BONUS)

.PHONY: all clean fclean re bonus
