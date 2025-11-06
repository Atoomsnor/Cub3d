# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: roversch <roversch@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/09/18 15:46:40 by roversch          #+#    #+#              #
#    Updated: 2025/11/06 16:26:51 by roversch         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	cub3D

CC			=	cc
CFLAGS		=	-Wall -Wextra -Werror
DEPFLAGS	=	-MMD
INCLUDES	=	-I ./inc -I libft/ -I MLX42/include/MLX42

#cub3D
VPATH		=	$(SRC_DIRS)
SRC_DIRS	=	src/ \
				src/cleanup/ \
				src/initialize/ \
				src/map_checks/ \
				src/parsing/ \
				src/raycasting/ \
				src/user_input/ \
				src/utils/ \
				src/visual/

SRC			=	main.c \
				cleanup_utils.c parser_cleanup.c \
				init.c set_images.c \
				file_checks.c flood_fill.c map_checks.c \
				map_reading.c map_to_int.c parser.c \
				ray_to_image.c raycasting.c \
				cursor.c gun.c move.c turn.c \
				get_color.c time.c \
				pixels.c resize.c

OBJ_DIR		=	obj/
OBJ			=	$(SRC:%.c=$(OBJ_DIR)%.o)

#Libft
LIBFT_DIR	=	libft
LIBFT_LIB	=	$(LIBFT_DIR)/libft.a

#MLX42
MLX42_DIR	=	MLX42
MLX42_LIB	=	$(MLX42_DIR)/build/libmlx42.a
MLX_LIBS	=	$(MLX42_LIB) -ldl -lglfw -lm

#Targets
all: $(NAME)

$(NAME): $(OBJ) libft libmlx Makefile
	$(CC) $(OBJ) -L. $(LIBFT_LIB) $(MLX_LIBS) $(CFLAGS) -o $(NAME)

#Directories
%/:
	mkdir -p $@

#cub3D objects
$(OBJ_DIR)%.o: %.c Makefile | $(OBJ_DIR)
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
.PRECIOUS : $(OBJ_DIR)

-include $(OBJ:.o=.d)