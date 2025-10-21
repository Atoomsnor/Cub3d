/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhendrik <nhendrik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 12:37:30 by roversch          #+#    #+#             */
/*   Updated: 2025/10/21 17:44:33 by nhendrik         ###   ########.fr       */
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

typedef struct s_img
{
	mlx_image_t		*NO;
	mlx_image_t		*SO;
	mlx_image_t		*WE;
	mlx_image_t		*EA;
	mlx_image_t		*screen;
	mlx_image_t		*hud;
	int32_t			floor_color;
	int32_t			ceiling_color;
} t_img;

typedef struct s_fps
{
	size_t	start_time;
	size_t	frames;
	size_t	last_time;
	size_t	time;
	double	delta_time;
} t_fps;

typedef struct s_parse
{
	int				**int_map;
	char			**map;
	char			*NO_texture;
	char			*SO_texture;
	char			*WE_texture;
	char			*EA_texture;
	char			*floor_color;
	char			*ceiling_color;
	t_vector		pos;
	t_vector		dir;

} t_parse;

typedef struct s_game
{
	mlx_t			*mlx;
	t_player		*player;
	t_img			*img;
	mlx_image_t		*screen_buffer;
	t_fps			*fps;
	t_vector		mouse;
	int				**world_map;
	int				width;
	int				height;
	int				game_width;
	
} t_game;

void		test_keyhook(void *param);
void		raycast(t_game *game);
int			**read_map(char *file_name, t_game *game);
size_t		get_time(void);
mlx_image_t	*png_to_image(const char *path, mlx_t *mlx);
t_game		*init_game(t_parse parse);
size_t		get_fps(t_game *game);
void		mouse(t_game *game);
void		cursor_hook(double x, double y, void *ptr);
void		turn_right(t_game *game, double speed);
void		turn_left(t_game *game, double speed);
void		curse(t_game *game);
int			check_input(char *map_name, t_parse *parse);
char		**get_map(char *input);
bool		check_map(t_parse *parse,  char **map);

#endif