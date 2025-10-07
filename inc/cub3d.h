/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhendrik <nhendrik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 12:37:30 by roversch          #+#    #+#             */
/*   Updated: 2025/10/07 16:53:10 by nhendrik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft.h"
# include "MLX42.h"
# include "stdbool.h"

# define SCREEN_HEIGHT 600
# define SCREEN_WIDTH 900

typedef struct s_vector
{
	double	x;
	double	y;
} t_vector;

typedef struct s_player
{
	t_vector	pos;
	t_vector	dir;
	t_vector	plane;
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

// struct map;
// map -> int var;
// map -> int x  int y
// map -> bool hit
// map -> double hit_dist
// map->hist_dist > ray.hist_dist: map->hist_dist = ray.hit_dist;

typedef struct s_map
{
	bool			hit;
	int				content;
	t_ray			ray;
	mlx_image_t		*img;
} t_map;

typedef struct s_img
{
	mlx_image_t		*img_wall;
} t_img;

typedef struct s_texture
{
	mlx_texture_t *wall_texture;
} t_texture;

typedef struct s_game
{
	mlx_t			*mlx;
	t_player		*player;
	t_texture		*textures;
	t_map			**world_map;
	int				width;
	int				height;
	int				game_width;
} t_game;

void	testfunc(void *ptr);
void	test_keyhook(mlx_key_data_t keydata, void *param);
void	raycast(t_game *game);
t_map	**read_map(char *file_name, t_game *game);

#endif