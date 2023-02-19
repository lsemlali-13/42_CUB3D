# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lsemlali <lsemlali@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/02 22:03:03 by rarahhal          #+#    #+#              #
#    Updated: 2023/02/19 18:41:49 by lsemlali         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D
CFLAGS = -Wall -Werror -Wextra
CC = cc #-fsanitize=address -g3

SRCS = Mandatory/cub3d.c \
		Mandatory/parser/ft_check_file.c \
		Mandatory/parser/ft_error.c \
		Mandatory/parser/map_setting.c \
		Mandatory/parser/collect_element.c \
		Mandatory/parser/collores.c \
		Mandatory/parser/texture.c \
		Mandatory/parser/collect_map.c \
		Mandatory/parser/check_map.c \
		cast_rend/cast_rend.c \
		cast_rend/rendering3d.c \
		cast_rend/rend_tools.c \
		cast_rend/player_movement.c \
		cast_rend/dda_algo.c \

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
OBJS_B = $(BONUS_SRCS:.c=.o)


$(NAME): $(OBJS) $(OBJS_L)
	$(CC) $(CFLAGS) -lmlx -framework OpenGL -framework AppKit $(OBJS) $(OBJS_L) -o $(NAME)

all: $(NAME)

clean:
	@rm -f Mandatory/*.o
	@rm -f Mandatory/parser/*.o
	@rm -f Libft/*.o

fclean: clean
	@rm -f $(NAME)
	@rm -f $(NAME_BONUS)

re: fclean
	@make all

.PHONY: all bonus clean fclean re