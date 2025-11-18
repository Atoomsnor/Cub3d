/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_to_image.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhendrik <nhendrik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 02:12:07 by nhendrik          #+#    #+#             */
/*   Updated: 2025/11/18 14:01:54 by nhendrik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	draw_floor(t_game *game, int x, int y)
{
	while (y < game->height)
	{
		put_pixel(game->screen_buffer, x, y, game->img.floor_color);
		y++;
	}
}

static void	draw_ceiling(t_game *game, int x, int y)
{
	while (y > 0)
	{
		put_pixel(game->screen_buffer, x, y, game->img.ceiling_color);
		y--;
	}
}

static void	draw_wall(const int height, int y_end, t_game *game, t_ray ray)
{
	mlx_image_t	*img;
	int			tex_y;
	double		step;
	double		tex_pos;

	step = 1.0 * SCALE / height;
	tex_pos = (ray.y - game->height / 2 + height / 2) * step;
	while (ray.y < y_end)
	{
		tex_y = (int)tex_pos & (SCALE - 1);
		tex_pos += step;
		if (!ray.side && ray.dir.x > 0)
			img = game->img.ea;
		else if (!ray.side)
			img = game->img.we;
		else if (ray.dir.y > 0)
			img = game->img.so;
		else
			img = game->img.no;
		if (game->world_map[(int)ray.map.y][(int)ray.map.x] == 3)
			img = game->img.door;
		put_pixel(game->screen_buffer, ray.x, ray.y,
			get_color(img, ray.tex.x, tex_y));
		ray.y++;
	}
}

void	ray_to_image(t_ray ray, t_game *game)
{
	const int	height = (int)(game->height / ray.hit_dist);
	int			y_start;
	int			y_end;

	y_start = game->height / 2 + -height / 2;
	y_end = game->height / 2 + height / 2;
	if (y_start < 0)
		y_start = 0;
	if (y_end >= game->height)
		y_end = game->height - 1;
	ray.y = y_start;
	draw_wall(height, y_end, game, ray);
	draw_floor(game, ray.x, y_end);
	draw_ceiling(game, ray.x, y_start);
}
