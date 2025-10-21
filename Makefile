# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ingonzal <ingonzal@student.42urduliz.com>  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/07/13 20:12:25 by ingonzal          #+#    #+#              #
#    Updated: 2021/09/28 13:03:10 by ingonzal         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf

CC = gcc
FLAGS = -Wall -Wextra -Werror -g

AR = ar rcs

RM = rm -f

S = -fsanitize=address -g3

FRAME = -framework Opengl -framework AppKit

LIBFT = -Llibft -lft
MLX = -Lmlx -lmlx

FILES = fdf \
		draw2 \
		drw_aux \

SRCS_DIR = ./
SRCS = $(addprefix $(SRC_DIR), $(addsuffix .c, $(FILES)))

OBJS_DIR = ./
OBJS = $(addprefix $(OBJS_DIR), $(addsuffix .o, $(FILES)))

$(NAME): $(OBJS)
		$(MAKE) -C ./libft
		$(MAKE) -C ./mlx
		$(CC) $(FLAGS) $(S) $^ $(LIBFT) $(MLX) $(FRAME) -o $@ 

all: $(NAME)

clean:
		$(MAKE) clean -C ./libft
		$(MAKE) clean -C ./mlx
		$(RM) $(OBJS)

fclean: clean
		$(RM) $(NAME)

re: clean all

.PHONY: clean fclean %.o
