SRC = main.c libft/ft_split.c
CFLAGS = -Wall -Wextra -Werror

NAME = CUB3D

OBJ = $(SRC:.c=.o)
$(NAME) : $(OBJ)
	cc -Lmlx -lmlx -framework OpenGL -framework Appkit $(CFLAGS) $(OBJ) -o $(NAME)

all : $(NAME)

clean :
	rm -f $(OBJ)

fclean : clean
	rm -f $(NAME)

re : fclean all
