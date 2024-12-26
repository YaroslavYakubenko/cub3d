NAME = game
CC = cc
OBJ = $(SRC:.c=.o)

FLAGS = -Lmlx -lmlx -framework OpenGL -framework AppKit -g
INCLUDES = mlx/libmlx.a
SRC = src/main.c
 
all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) -o $(NAME) $(INCLUDES) $(FLAGS)

%.o: %.c
	$(CC) -Wall -Wextra -Werror -Imlx -c $< -o $@

fclean:
	rm -rf $(OBJ)
	rm -rf $(NAME)
