# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dverbyts <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/29 17:36:20 by dverbyts          #+#    #+#              #
#    Updated: 2019/04/29 17:36:22 by dverbyts         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ssl

CFLAGS = -Wall -Wextra -Werror -I.

SRC = main.c md5.c sha256.c parsing_input.c

OBJ = $(SRC:.c=.o)

LIB = libft/libft.a

all: $(NAME)

$(NAME): $(OBJ)
	@make -C libft
	@echo "\033[32;1m<libft>			| done\033[0m"
	@gcc $(FLAGS) -o $(NAME) $(OBJ) $(LIB) -lncurses
	@echo "\033[32;1m<ft_ssl>		| done\033[0m"

%.o: %.c
	@gcc $(CFLAGS) -c -o $@ $<

clean:
	@rm -f $(OBJ)
	@make clean -C libft
	@echo "\033[1;33m<libft *.o>		| removed\033[0m"
	@echo "\033[1;33m<ft_ssl *.o>		| removed\033[0m"
	
fclean: clean
	@rm -f $(NAME)
	@make fclean -C libft
	@echo "\033[1;33m<ft_ssl>		| removed\033[0m"

re: fclean all
