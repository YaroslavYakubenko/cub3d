GREEN = \033[0;32m
RESET = \033[0m

NAME        = cub3D

CC          = cc
CC_FLAGS    = -Wall -Wextra -Werror -g -Iinc #-fsanitize=address

MLX 		= minilibx_linux/
MLX_FLAGS 	= -I -g3 -L /usr/X11/lib -Lincludes -L./mlx -lmlx -Imlx -lXext -lX11 -lz

LIBFT_DIR	= inc/libft
PRINTF_DIR	= inc/ft_printf
GNL_DIR		= inc/get_next_line

LIBFT 		= $(LIBFT_DIR)/libft.a
PRINTF 		= $(PRINTF_DIR)/libftprintf.a
GNL 		= $(GNL_DIR)/libgnl.a

LIBFLAGS	= -L$(LIBFT_DIR) -lft -L$(PRINTF_DIR) -lftprintf -L$(GNL_DIR) -lgnl \
				-I$(LIBFT_DIR) -I$(PRINTF_DIR) -I$(GNL_DIR)

SRCS_F      = src/
OBJS_F      = obj/

SRCS        = $(SRCS_F)main.c \
			  $(SRCS_F)free.c \
              $(SRCS_F)parsing/check_and_reading.c \
			  $(SRCS_F)parsing/parse_map.c \
			  $(SRCS_F)parsing/parse_player.c \
              $(SRCS_F)game/init_move.c \
			  $(SRCS_F)game/movement.c \
			  $(SRCS_F)game/init_game.c \
            #   $(SRCS_F)raycast/raycast.c \

OBJS        = $(SRCS:.c=.o)

OBJS_P      = $(addprefix $(OBJS_F), $(OBJS))

VPATH = $(SRCS_F) $(SRCS_F)parsing/ $(SRCS_F)raycast/ $(SRCS_F)game/

all: $(NAME)

$(OBJS_F)%.o: %.c Makefile inc/cub3d.h
	@mkdir -p $(dir $@)
	@$(CC) $(CC_FLAGS) -O3 -c $< -o $@ # 2> /dev/null

$(LIBFT):
	@$(MAKE) -sC $(LIBFT_DIR)

$(PRINTF):
	@$(MAKE) -sC $(PRINTF_DIR)

$(GNL):
	@$(MAKE) -sC $(GNL_DIR)

$(NAME): $(OBJS_P) $(LIBFT) $(PRINTF) $(GNL)
	@$(MAKE) -sC $(MLX)
	@$(CC) -O3 -o $(NAME) $(OBJS_P) $(CC_FLAGS) $(LIBFLAGS) -L$(MLX) $(MLX_FLAGS) -lm
	@echo "\n$(GREEN)\n               CUB3D COMPILED SUCCESSFULLY\n\n$(RESET)"

clean:
	@rm -rf $(OBJS_F)
	@$(MAKE) -sC $(MLX) clean
	@$(MAKE) -sC $(LIBFT_DIR) clean
	@$(MAKE) -sC $(PRINTF_DIR) clean
	@$(MAKE) -sC $(GNL_DIR) clean

fclean: clean
	@rm -rf $(NAME)
	@$(MAKE) -sC $(LIBFT_DIR) fclean
	@$(MAKE) -sC $(PRINTF_DIR) fclean
	@$(MAKE) -sC $(GNL_DIR) fclean

re: fclean all

.PHONY: all clean fclean re