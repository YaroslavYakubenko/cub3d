NAME = game
CC = cc
OBJ = $(SRC:.c=.o)

# FLAGS = -Lmlx -lmlx -framework OpenGL -framework AppKit -g
FLAGS = -L$(MLX) -lmlx -lGL -lX11 -lXext -g
MLX = ../minilibx_linux/
SRC = src/main.c
 
all: $(NAME)

$(NAME): $(OBJ)
	@$(MAKE) -sC $(MLX)
	$(CC) $(OBJ) -o $(NAME) $(FLAGS) -L$(MLX) -lmlx
# $(CC) -Wall -Wextra -Werror -Imlx -c $< -o $@

%.o: %.c
	$(CC) -Wall -Wextra -Werror -Imlx -c $< -o $@

fclean:
	rm -rf $(OBJ)
	rm -rf $(NAME)
