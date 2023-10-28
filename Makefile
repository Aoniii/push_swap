NAME = push_swap

SRCS = sources/ft_args.c \
	sources/ft_stack.c \
	sources/ft_utils.c \
	sources/ft_atoll.c \
	sources/ft_swap.c \
	sources/ft_push.c \
	sources/ft_rotate.c \
	sources/ft_reverse_rotate.c \
	sources/ft_sort.c \
	sources/ft_get.c \
	sources/ft_index.c \
	sources/ft_sort_big.c \
	main.c

CFLAGS = -Wall -Wextra -Werror -I includes

RED = \e[31m
GREEN = \e[32m
YELLOW = \e[33m
CYAN = \e[36m
LRED = \e[91m
LGREEN = \e[92m
RESET = \e[0m

define logo
	clear
	@printf "$(CYAN)"
	@printf "\n"
	@printf "  ██████╗ ██╗   ██╗███████╗██╗  ██╗    ███████╗██╗    ██╗ █████╗ ██████╗ \n"
	@printf "  ██╔══██╗██║   ██║██╔════╝██║  ██║    ██╔════╝██║    ██║██╔══██╗██╔══██╗\n"
	@printf "  ██████╔╝██║   ██║███████╗███████║    ███████╗██║ █╗ ██║███████║██████╔╝\n"
	@printf "  ██╔═══╝ ██║   ██║╚════██║██╔══██║    ╚════██║██║███╗██║██╔══██║██╔═══╝ \n"
	@printf "  ██║     ╚██████╔╝███████║██║  ██║    ███████║╚███╔███╔╝██║  ██║██║     \n"
	@printf "  ╚═╝      ╚═════╝ ╚══════╝╚═╝  ╚═╝    ╚══════╝ ╚══╝╚══╝ ╚═╝  ╚═╝╚═╝     \n"
	@printf "\n"
endef 

all:
	$(MAKE) -C libft/
	@gcc $(CFLAGS) $(SRCS) libft/libft.a -o $(NAME)
	$(call logo)
	@printf "$(GREEN)  [$(YELLOW)+$(GREEN)] $(LGREEN)program create !$(RESET)\n"
	@printf "\n"

clean:
	@$(MAKE) -C libft/ clean
	$(call logo)
	@printf "$(RED)  [$(YELLOW)-$(RED)] $(LRED)objects removes !$(RESET)\n"
	@printf "\n"

fclean:
	@rm -rf push_swap
	@$(MAKE) -C libft/ fclean
	$(call logo)
	@printf "$(RED)  [$(YELLOW)-$(RED)] $(LRED)all removes !$(RESET)\n"
	@printf "\n"

re: fclean all

.PHONY: re all clean fclean