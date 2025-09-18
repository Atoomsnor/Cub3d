NAME = cub3d

SRC = main.c

SRC_DIR = src

SRC_COPE	= $(SRC:%=$(SRC_DIR)/%)
OBJ			= $(SRC:%.c=$(OBJ_DIR)/%.o)
OBJ_DIR		= obj

CC = cc
CFLAGS = -Wall -Wextra -Werror
INCLUDE     = -I ./include -I libft/ -I MLX42/include

LIBFT_DIR = libft
LIBFT_LIB = $(LIBFT_DIR)/libft.a

MLX_LIB	= MLX42/build/libmlx42.a -ldl -lglfw -lm

all: MLX42_BUILD $(NAME)

$(NAME): $(LIBFT_LIB) $(OBJ) MLX42
	$(CC) $(OBJ) -L. $(LIBFT_LIB) $(MLX_LIB) $(CFLAGS) -o $(NAME)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

MLX42_BUILD:
	@cd MLX42 && cmake -B build && cmake --build build -j4

MLX42_CLEAN:
	@cd MLX42 && cmake --build build --target clean

$(LIBFT_LIB):
	$(MAKE) -C $(LIBFT_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) -c $(CFLAGS) $< -o $@

clean: MLX42_CLEAN
	rm -rf $(OBJ_DIR)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean
	
re: fclean all

.PHONY: all clean fclean re
