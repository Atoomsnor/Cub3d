/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roversch <roversch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 12:37:30 by roversch          #+#    #+#             */
/*   Updated: 2025/11/13 15:13:17 by roversch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_BONUS_H
# define CUB3D_BONUS_H

# include "libft.h"
# include "MLX42.h"
# include "stdbool.h"

# define SCREEN_HEIGHT 640
# define SCREEN_WIDTH 960
# define SCALE 64
// colors
# define BLACK 0xFF000000
# define CYPRUS 0xFF404000
# define LIGHT_SEA_GREEN 0xFFB4B420

typedef struct s_vector
{
	double	x;
	double	y;
}	t_vector;

typedef struct s_player
{
	t_vector	pos;
	t_vector	dir;
	t_vector	plane;
}	t_player;

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
	int			side;
	int			x;
	int			y;
}	t_ray;

typedef struct s_img
{
	mlx_image_t		*no;
	mlx_image_t		*so;
	mlx_image_t		*we;
	mlx_image_t		*ea;
	mlx_image_t		*screen;
	mlx_image_t		*hud;
	mlx_image_t		*faces[2];
	mlx_image_t		*gun[5];
	mlx_image_t		*door;
	mlx_image_t		*doors[20];
	int32_t			floor_color;
	int32_t			ceiling_color;
}	t_img;

typedef struct s_sprite_anime
{
	bool	in_anime;
	size_t	anime_start_time;
}	t_sprite_anime;

typedef struct s_fps
{
	size_t	start_time;
	size_t	frames;
	size_t	last_time;
	size_t	time;
	double	delta_time;
}	t_fps;

typedef struct s_parse
{
	int				**int_map;
	char			**map;
	char			*no_texture;
	char			*so_texture;
	char			*we_texture;
	char			*ea_texture;
	char			*floor_color;
	char			*ceiling_color;
	t_vector		pos;
	t_vector		dir;
}	t_parse;

typedef struct s_minimap
{
	int				**map;
	t_vector		pos;
	t_vector		min;
	t_vector		step;
	t_vector		map_pos;
	mlx_image_t		*img;
}	t_minimap;

typedef struct s_game
{
	mlx_t			*mlx;
	t_player		player;
	t_img			img;
	mlx_image_t		*screen_buffer;
	t_sprite_anime	anime;
	t_sprite_anime	door_anime;
	t_fps			fps;
	t_vector		mouse;
	t_minimap		minimap;
	int				**world_map;
	int				map_width;
	int				map_height;
	int				width;
	int				height;
}	t_game;

void		minimap(t_game *game);
void		doors(t_game *game);

// *cleanup* //

int			free_and_null(void *ptr);
void		free_matrix(void *ptr);
void		free_flood(void *ptr);
int			empty_parse(t_parse *parse, bool out);
int			print_error(char *str);

// *initialize* //

int			init_game(t_game *game, t_parse parse);
int			init_images(t_game *game, t_parse parse);
int			set_base_visuals(t_game *game);
// *map_checks* //

int			look_for_lines(int map_pos, char **map);
int			check_name(char *name);
int			flood_and_walls(char **map, t_parse *parse);
int			find_widest_point(char **map);
int			check_map(t_parse *parse, char **map);

// *parsing* //

char		**get_map(char *input);
int			**ctoi_map(char **map);
int			check_input(char *map_name, t_parse *parse);
int			parsing(char *map_name, t_parse *parse);

// *raycasting* //

void		ray_to_image(t_ray ray, t_game *game);
t_ray		cast_ray(t_ray ray, t_player player, t_game *game, bool to_image);
int			raycast(t_game *game);

// *user_input* //

void		mouse_hook(t_game *game);
void		cursor_hook(double x, double y, void *ptr);
void		shoot(t_game *game);
void		key_hook(void *param);
void		turn_left(t_game *game, double speed);
void		turn_right(t_game *game, double speed);
void		turn_hook(t_game *game, double speed);

// *utils* //

int32_t		str_to_color(char *str);
size_t		get_time(void);
size_t		get_fps(t_game *game);

// *visual* //

int			get_color(mlx_image_t *image, uint32_t x, uint32_t y);
void		put_pixel(mlx_image_t *image, uint32_t x,
				uint32_t y, uint32_t color);
void		fill_buffer_color(mlx_image_t *image, uint32_t color);
void		resize_hook(int32_t width, int32_t height, void *ptr);
int			resize_minimap(t_game *game);
mlx_image_t	*png_to_image(const char *path, mlx_t *mlx);

#endif