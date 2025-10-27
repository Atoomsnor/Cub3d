# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nhendrik <nhendrik@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/09/18 15:46:40 by roversch          #+#    #+#              #
#    Updated: 2025/10/27 14:39:40 by nhendrik         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	cub3D

CC			=	cc
CFLAGS		=	-Wall -Wextra -Werror
DEPFLAGS	= 	-MMD
INCLUDES	=	-I ./inc -I libft/ -I MLX42/include/MLX42

#cub3D
SRC_DIR		=	src
SRC			=	main.c move.c raycasting.c map_reading.c time.c init.c cursor.c \
				parsing.c map_checks.c turn.c ray_to_image.c pixels.c resize.c \

OBJ_DIR		=	obj
OBJ			=	$(SRC:%.c=$(OBJ_DIR)/%.o)

#Libft
LIBFT_DIR	=	libft
LIBFT_LIB	=	$(LIBFT_DIR)/libft.a

#MLX42
MLX42_DIR   =	MLX42
MLX42_LIB   =	$(MLX42_DIR)/build/libmlx42.a
MLX_LIBS	=	$(MLX42_LIB) -ldl -lglfw -lm

#Targets
all: $(NAME)

$(NAME): $(OBJ) libft libmlx Makefile
	$(CC) $(OBJ) -L. $(LIBFT_LIB) $(MLX_LIBS) $(CFLAGS) -o $(NAME)

#Object directory
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

#cub3D objects
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c Makefile | $(OBJ_DIR)
	$(CC) -c $(CFLAGS) $(DEPFLAGS) $(INCLUDES) $< -o $@

#Libft objects

libft:
	$(MAKE) -C $(LIBFT_DIR)

#MLX42 objects
libmlx:
	@cd $(MLX42_DIR) && cmake -B build && cmake --build build -j4

clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	rm -rf $(OBJ_DIR)

fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re libft libmlx

-include $(OBJ:.o=.d)