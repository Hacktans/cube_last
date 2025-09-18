CC = cc
CFLAGS = -Wall -Wextra -Werror -I. 
DEBUG_FLAGS = -g

NAME = cub3d

SRC = main.c engine.c parse/parse.c gnl/get_next_line_utils.c gnl/get_next_line.c parse/parse_utils.c parse/map_parse.c parse/read_file.c
OBJ = $(SRC:.c=.o)

# Libft ayarları
LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a

# MinilibX ayarları
MLX_DIR = ./minilibx-linux
MLX = $(MLX_DIR)/libmlx.a
MLX_FLAGS = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm

all: $(NAME) 

$(NAME): $(OBJ) $(LIBFT) $(MLX)
	$(CC) $(CFLAGS) $(DEBUG_FLAGS) $(OBJ) $(LIBFT) $(MLX_FLAGS) -o $(NAME) 

$(LIBFT):
	make -C $(LIBFT_DIR)

$(MLX):
	make -C $(MLX_DIR)

%.o: %.c
	$(CC) $(CFLAGS) $(DEBUG_FLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)
	make -C $(LIBFT_DIR) clean
	make -C $(MLX_DIR) clean

fclean: clean
	rm -f $(NAME)
	make -C $(LIBFT_DIR) fclean
	make -C $(MLX_DIR) clean

re: fclean all

.PHONY: all clean fclean re
