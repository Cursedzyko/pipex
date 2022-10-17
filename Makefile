# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zyunusov <zyunusov@student.42wolfsburg.de> +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/12 18:26:49 by zyunusov          #+#    #+#              #
#    Updated: 2022/10/16 16:51:22 by zyunusov         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ./pipex
LIBFT_PATH = ./libft
LIBFT = $(LIBFT_PATH)/libft.a
MAKE = make
CC = cc
CFLAGS = -Wall -Wextra -Werror
PATH_SRC = srcs
FILES = pipex.c child_utils.c cmd_utils.c parse_args_utils.c
SRC = $(addprefix $(PATH_SRC)/,$(FILES))
RM = rm -rf

all: $(NAME)


$(NAME): $(LIBFT)
	$(CC) $(CFLAGS) -o $@ $(SRC) $(LIBFT)
	
$(LIBFT):
	$(MAKE) all -sC $(LIBFT_PATH)

clean:
	make clean -C $(LIBFT_PATH)

fclean: clean
	make fclean -C $(LIBFT_PATH) 
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
