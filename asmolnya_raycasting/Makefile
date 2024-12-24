NAME = ganr
CC = cc
OBJ = (SRC:.c = .o)

# FLAGS = -L./includes/mlx -lmlx -lXent -lX11 -lm -lz
INCLUDES = includes/minilibx-linux/libmlx.a
SRC = src/main.c
 
$(NAME): $(OBJ)
	$(CC) $(OBJ) -Lmlx -lmlx -framework OpenGL -framework AppKit -o $(NAME)

%.o: %.c
	$(CC) -Wall -Wextra -Werror -Imlx -c $< -o $@

fclean:
	rm -rf $(OBJ)
	rm -rf $(NAME)
