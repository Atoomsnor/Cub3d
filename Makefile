# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: roversch <roversch@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/09/18 15:46:40 by roversch          #+#    #+#              #
#    Updated: 2025/09/18 15:57:20 by roversch         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= cub3D

CC			= cc
CFLAGS		= -Wall -Wextra -Werror
DEPFLAGS	= -MMD
INCLUDES	= -I ./include -I libft/ -I MLX42/include

#cub3D
SRC_DIR		= src
SRC			= main.c

OBJ_DIR		= obj
OBJ			= $(SRC:%.c=$(OBJ_DIR)/%.o)

#Libft
LIBFT_DIR	= libft
LIBFT_LIB	= $(LIBFT_DIR)/libft.a

#MLX42
MLX42_LIB	= MLX42/build/libmlx42.a
MLX_LIBS	= $(MLX42_LIB) -ldl -lglfw -lm

#Targets
all: $(NAME)

$(NAME): $(LIBFT_LIB) $(OBJ) $(MLX42_LIB) Makefile
	$(CC) $(OBJ) -L. $(LIBFT_LIB) $(MLX_LIBS) $(CFLAGS) -o $(NAME)

#Object directory
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

#cub3D objects
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c Makefile | $(OBJ_DIR)
	$(CC) -c $(CFLAGS) $(DEPFLAGS) $(INCLUDES) $< -o $@

#Libft objects
$(LIBFT_LIB):
	$(MAKE) -C $(LIBFT_DIR)

#MLX42 objects
$(MLX42_LIB):
	@cd MLX42 && cmake -B build && cmake --build build -j4

clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	rm -rf $(OBJ_DIR)

fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

-include $(OBJ:.o=.d)