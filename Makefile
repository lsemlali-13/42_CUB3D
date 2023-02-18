SRC = main.c libft/ft_split.c dda_algo.c
CFLAGS = -Wall -Wextra -Werror -fsanitize=address -g3

NAME = CUB3D

OBJ = $(SRC:.c=.o)
$(NAME) : $(OBJ)
	cc -lmlx -framework OpenGL -framework Appkit $(CFLAGS) $(OBJ) -o $(NAME)

all : $(NAME)

clean :
	rm -f $(OBJ)

fclean : clean
	rm -f $(NAME)

re : fclean all
