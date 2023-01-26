# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rarahhal <rarahhal@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/02 22:03:03 by rarahhal          #+#    #+#              #
#    Updated: 2022/06/19 15:30:37 by rarahhal         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d
# NAME_BONUS = cub3d_bonus
FLAGS = -Wall -Werror -Wextra
CC = cc

SRCS = Mandatory/cub3d.c \
		Mandatory/ft_check_file.c \
		Mandatory/get_next_line.c \
		Mandatory/get_next_line_2.c \
		Mandatory/setting_map.c \
		Mandatory/ft_error.c \
		# Mandatory/map_error.c \

# BONUS_SRCS = 


LIBFT = Libft/ft_calloc.c \
		Libft/ft_strchr.c \
		Libft/ft_strjoin.c \
		Libft/ft_strlen.c \
		Libft/ft_strdup.c \
		Libft/ft_putnbr.c \
		Libft/ft_itoa.c \

OBJS = $(SRCS:.c=.o)
OBJS_L = $(LIBFT:.c=.o)
OBJS_B = $(BONUS_SRCS:.c=.o)


$(NAME): $(OBJS) $(OBJS_L)
	$(CC) $(FLAGS) $(OBJS) $(OBJS_L) -L/mlx_linux mlx_linux/libmlx.a -lXext -lX11 -lbsd -lm -o $(NAME)

# $(NAME_BONUS): $(OBJS_B) $(OBJS_L)
# 	$(CC) $(FLAGS) $(OBJS_B) $(OBJS_L) -L/mlx_linux mlx_linux/libmlx.a -lXext -lX11 -lbsd -lm -o $(NAME)
	# $(CC) $(FLAGS) -lmlx -framework OpenGL -framework AppKit $(OBJS_B) $(OBJS_L) -o $(NAME_BONUS)

all: $(NAME)

# bonus: $(NAME_BONUS)

clean:
	@rm -f bonus/*.o
	@rm -f Mandatory/*.o
	@rm -f Bonus/*.o
	@rm -f Libft/*.o

fclean: clean
	@rm -f $(NAME)
	@rm -f $(NAME_BONUS)

re: fclean
	@make all

.PHONY: all bonus clean fclean re

# $(NAME): $(OBJS) $(OBJS_L)
	# $(CC) $(FLAGS) -lmlx -framework OpenGL -framework AppKit $(OBJS) $(OBJS_L) -o $(NAME)