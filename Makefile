# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ahamza <ahamza@student.s19.be>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/12 10:47:57 by molamdao          #+#    #+#              #
#    Updated: 2025/08/19 17:58:37 by ahamza           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d


HEADER = cub3d.h
SRCS =	main.c file_content.c utils.c gnl/get_next_line.c gnl/get_next_line_utils.c \
		ft_split.c parsing.c parsing2.c mini_init.c init_minilibx.c ray_casting.c controls.c colors.c textures.c texture_utils.c \
		wall_rendering.c

OBJS = $(SRCS:.c=.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror -g

MLX_DIR = minilibx-linux
MLX_LIB = $(MLX_DIR)/libmlx.a
MLX_INC = -I$(MLX_DIR)
MLX_FLAGS = -L$(MLX_DIR) -lmlx -lX11 -lXext -lbsd

RM = rm -f

all: $(NAME)

$(NAME): $(MLX_LIB) $(OBJS)
	$(CC) $(CFLAGS) $(MLX_INC) $(OBJS) $(MLX_LIB) $(MLX_FLAGS) -lm -o $(NAME)

$(MLX_LIB):
	$(MAKE) -C $(MLX_DIR)

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) $(MLX_INC) -c $< -o $@

clean:
	$(RM) $(OBJS)
	$(MAKE) clean -C $(MLX_DIR)

fclean: clean
	$(RM) $(NAME)
	$(RM) $(MLX_LIB)

re: fclean all

.PHONY: all clean fclean re