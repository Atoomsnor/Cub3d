/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhendrik <nhendrik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 12:37:30 by roversch          #+#    #+#             */
/*   Updated: 2025/09/23 15:05:02 by nhendrik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft.h"
# include "MLX42.h"
# include "stdbool.h"

typedef struct s_vector
{
	double	x;
	double	y;
} t_vector;

typedef struct s_player
{
	t_vector	pos;
	t_vector	dir;
} t_player;

typedef struct s_ray
{
	t_vector	dir;
	t_vector	map;
	t_vector	side_dist;
	t_vector	delta_dist;
	double		hit_dist;
	bool		hit;
} t_ray;

typedef struct s_game
{
	mlx_t		*mlx;
	t_player	*player;
	mlx_image_t	*img_bounce;
	mlx_image_t *img_wall;
	int			width;
	int			height;
	int			**world_map;
} t_game;

void	testfunc(void *ptr);
void	test_keyhook(mlx_key_data_t keydata, void *param);
void	raycast(t_game *game);

#endif