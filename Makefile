# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nhendrik <nhendrik@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/09/18 15:46:40 by roversch          #+#    #+#              #
#    Updated: 2025/11/11 14:02:38 by nhendrik         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	cub3D
NAME_B		=	cub3D_bonus

CC			=	cc
CFLAGS		=	-Wall -Wextra -Werror
DEPFLAGS	=	-MMD
INCLUDES	=	-I ./inc -I libft/ -I MLX42/include/MLX42

#cub3D Regular
SRC_DIRS	=	src/ \
				src/cleanup/ \
				src/initialize/ \
				src/map_checks/ \
				src/parsing/ \
				src/raycasting/ \
				src/user_input/ \
				src/utils/ \
				src/visual/ \

SRC			=	main.c \
				cleanup_utils.c parser_cleanup.c \
				init.c set_images.c \
				file_checks.c flood_fill.c map_checks.c \
				check_input.c map_reading.c map_to_int.c parser.c \
				ray_to_image.c raycasting.c \
				cursor.c gun.c move.c turn.c \
				get_color.c time.c \
				image.c pixels.c resize.c \

#cub3D Bonus
B_SRC_DIRS	=	bonus/src/ \
				bonus/src/bonus/ \
				bonus/src/cleanup/ \
				bonus/src/initialize/ \
				bonus/src/map_checks/ \
				bonus/src/parsing/ \
				bonus/src/raycasting/ \
				bonus/src/user_input/ \
				bonus/src/utils/ \
				bonus/src/visual/ \

B_SRC		=	main.c \
				cleanup_utils.c parser_cleanup.c \
				init.c set_images.c \
				file_checks.c flood_fill.c map_checks.c \
				check_input.c map_reading.c map_to_int.c parser.c \
				ray_to_image.c raycasting.c \
				cursor.c gun.c move.c turn.c \
				get_color.c time.c \
				image.c pixels.c resize.c \
				minimap.c doors.c \

OBJ_DIR		=	obj/
OBJ			=	$(SRC:%.c=$(OBJ_DIR)%.o)
OBJ_B		=	$(B_SRC:%.c=$(OBJ_DIR)%_bonus.o)

#Libft
LIBFT_DIR	=	libft
LIBFT_LIB	=	$(LIBFT_DIR)/libft.a

#MLX42
MLX42_DIR	=	MLX42
MLX42_LIB	=	$(MLX42_DIR)/build/libmlx42.a
MLX_LIBS	=	$(MLX42_LIB) -ldl -lglfw -lm

#Targets
all: $(NAME)

VPATH = $(SRC_DIRS)
$(NAME): $(OBJ) libft libmlx Makefile
	$(CC) $(OBJ) -L. $(LIBFT_LIB) $(MLX_LIBS) $(CFLAGS) -o $(NAME)

#Directories
%/:
	mkdir -p $@

#cub3D objects (regular)
$(OBJ_DIR)%.o: %.c Makefile | $(OBJ_DIR)
	$(CC) -c $(CFLAGS) $(DEPFLAGS) $(INCLUDES) $< -o $@

#Bonus target
bonus: fclean libft libmlx
	$(MAKE) -B VPATH="$(B_SRC_DIRS)" $(NAME_B)

#Bonus objects (with _bonus suffix)
$(OBJ_DIR)%_bonus.o: %.c Makefile | $(OBJ_DIR)
	$(CC) -c $(CFLAGS) $(DEPFLAGS) $(INCLUDES) -I ./bonus/inc -I ./inc $< -o $@

#Libft objects

libft:
	$(MAKE) -C $(LIBFT_DIR)

#MLX42 objects
libmlx:
	@cd $(MLX42_DIR) && cmake -B build && cmake --build build -j4

$(NAME_B): $(OBJ_B) libft libmlx Makefile
	$(CC) $(OBJ_B) -L. $(LIBFT_LIB) $(MLX_LIBS) $(CFLAGS) -o $(NAME_B)

clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	rm -rf $(OBJ_DIR)

fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	rm -f $(NAME) $(NAME_B)

re: fclean all

.PHONY: all bonus clean fclean re libft libmlx
.PRECIOUS : $(OBJ_DIR)

-include $(OBJ:.o=.d)
-include $(OBJ_B:.o=.d)