# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lsemlali <lsemlali@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/02 22:03:03 by rarahhal          #+#    #+#              #
#    Updated: 2023/02/22 13:39:28 by lsemlali         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D
CFLAGS = -Wall -Wextra -Werror
CC = cc

SRCS =  cub3d.c \
		parser/ft_check_file.c \
		parser/ft_error.c \
		parser/map_setting.c \
		parser/collect_element.c \
		parser/collores.c \
		parser/texture.c \
		parser/collect_map.c \
		parser/check_map.c \
		cast_rend/cast_rend.c \
		cast_rend/rendering3d.c \
		cast_rend/rend_tools.c \
		cast_rend/player_movement.c \
		cast_rend/dda_algo.c \
		cast_rend/dda_horisontal.c \
		cast_rend/dda_vertical.c \
		cast_rend/player_info.c \

LIBFT = Libft/ft_calloc.c \
		Libft/ft_strchr.c \
		Libft/ft_strjoin.c \
		Libft/ft_strlen.c \
		Libft/ft_strdup.c \
		Libft/ft_putnbr.c \
		Libft/ft_itoa.c \
		Libft/ft_split.c \
		Libft/ft_strncmp.c \
		Libft/ft_atoi.c \
		Libft/get_next_line.c \
		Libft/get_next_line_2.c \

OBJS = $(SRCS:.c=.o)
OBJS_L = $(LIBFT:.c=.o)


$(NAME): $(OBJS) $(OBJS_L)
	$(CC) $(CFLAGS) -lmlx -framework OpenGL -framework AppKit $(OBJS) $(OBJS_L) -o $(NAME)

all: $(NAME)

clean:
	@rm -f $(OBJS) $(OBJS_L)

fclean: clean
	@rm -f $(NAME)

re: fclean
	@make all

.PHONY: all clean fclean re