/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roversch <roversch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 12:37:30 by roversch          #+#    #+#             */
/*   Updated: 2025/09/22 15:23:46 by roversch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft.h"
# include "MLX42.h"

typedef struct s_player
{
	int	x;
	int	y;
} t_player;

typedef struct s_game
{
	mlx_t		*mlx;
	t_player	player[1];
	mlx_image_t	*img_bounce;
	mlx_image_t *img_wall;
} t_game;

void testfunc(void *ptr);
void test_keyhook(mlx_key_data_t keydata, void *param);

#endif