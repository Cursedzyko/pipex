# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zyunusov <zyunusov@student.42wolfsburg.de> +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/12 18:26:49 by zyunusov          #+#    #+#              #
#    Updated: 2022/10/23 15:18:58 by zyunusov         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ./pipex
NAME_BONUS = ./pipex_bonus
LIBFT_PATH = ./libft
LIBFT = $(LIBFT_PATH)/libft.a
MAKE = make
CC = cc
CFLAGS = -Wall -Wextra -Werror
PATH_SRC = srcs
PATH_SRC_BONUS = srcs_bonus
FILES_BONUS = cmd_utils_bonus.c exec_utils_bonus.c here_doc_bonus.c parse_utils_bonus.c pipes_utils_bonus.c pipex_bonus.c
FILES = pipex.c child_utils.c cmd_utils.c parse_args_utils.c
SRC = $(addprefix $(PATH_SRC)/,$(FILES))
SRC_BONUS = $(addprefix $(PATH_SRC_BONUS)/,$(FILES_BONUS))
RM = rm -rf

all: $(NAME)

bonus: $(NAME_BONUS)

$(NAME): $(LIBFT)
	$(CC) $(CFLAGS) -o $@ $(SRC) $(LIBFT)

$(NAME_BONUS): $(LIBFT)
	$(CC) $(CFLAGS) -o $@ $(SRC_BONUS) $(LIBFT)
	cp ./pipex_bonus ./pipex
	
$(LIBFT):
	$(MAKE) all -sC $(LIBFT_PATH)

clean:
	make clean -C $(LIBFT_PATH)

fclean: clean
	make fclean -C $(LIBFT_PATH) 
	$(RM) $(NAME) $(NAME_BONUS)

re: fclean all

.PHONY: all clean fclean re
