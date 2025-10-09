/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhendrik <nhendrik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 12:37:30 by roversch          #+#    #+#             */
/*   Updated: 2025/10/10 00:21:28 by nhendrik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft.h"
# include "MLX42.h"
# include "stdbool.h"

# define SCREEN_HEIGHT 640
# define SCREEN_WIDTH 960
# define SCALE 64

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
	t_vector	wall;
	t_vector	tex;
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
	mlx_image_t		*NO;
	mlx_image_t		*SO;
	mlx_image_t		*WE;
	mlx_image_t		*EA;
	mlx_image_t		*img_wall;
	mlx_image_t		*screen;
	mlx_image_t		*gun;
} t_img;

typedef struct s_texture
{
	mlx_texture_t *wall_texture;
	mlx_texture_t *gun;
} t_texture;

typedef struct s_game
{
	mlx_t			*mlx;
	t_player		*player;
	mlx_image_t		*img_wall;
	t_texture		*textures;
	t_map			**world_map;
	t_img			*img;
	mlx_image_t		*screen_buffer;
	mlx_image_t		*gun;
	int				width;
	int				height;
	int				game_width;
	
} t_game;

void	test_keyhook(void *param);
void	raycast(t_game *game);
t_map	**read_map(char *file_name, t_game *game);

#endif