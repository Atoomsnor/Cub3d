/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhendrik <nhendrik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 20:19:35 by nhendrik          #+#    #+#             */
/*   Updated: 2025/11/18 14:10:36 by nhendrik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"
#include <math.h>

int	resize_minimap(t_game *game)
{
	int	z;

	z = game->minimap.img->instances[0].z;
	mlx_delete_image(game->mlx, game->minimap.img);
	game->minimap.img = mlx_new_image(game->mlx,
			game->width / 6, game->height / 4);
	if (!game->minimap.img)
		return (-1);
	if (mlx_image_to_window(game->mlx, game->minimap.img,
			game->width / 40, ceil((double)game->height / 26.666667f))
		== -1)
		return (-1);
	game->minimap.img->instances[0].z = z;
	return (0);
}

static void	init_minimap(t_game *game, t_minimap *minimap)
{
	int	pixels_per_map_x;
	int	pixels_per_map_y;

	fill_buffer_color(minimap->img, CYPRUS);
	minimap->map = game->world_map;
	minimap->pos = game->player.pos;
	minimap->min.x = minimap->pos.x - 5;
	minimap->min.y = minimap->pos.y - 5;
	pixels_per_map_x = minimap->img->width / 10;
	pixels_per_map_y = minimap->img->height / 10;
	minimap->step.x = 1.0 / pixels_per_map_x;
	minimap->step.y = 1.0 / pixels_per_map_y;
	minimap->map_pos = minimap->min;
}

static void	put_player(mlx_image_t *img)
{
	unsigned int	y;
	unsigned int	x;
	int				point_width;
	int				point_height;

	point_width = img->width / 20 + 2;
	point_height = img->height / 20 + 2;
	y = img->height / 2 - point_height / 2;
	while (y < img->height / 2 + point_height / 2 + 1)
	{
		x = img->width / 2 - point_width / 2;
		while (x < img->width / 2 + point_width / 2 + 1)
		{
			put_pixel(img, x, y, BLACK);
			x++;
		}
		y++;
	}
}

static void	put_minimap(t_minimap *minimap, t_game *game,
		unsigned int x, unsigned int y)
{
	if (minimap->map_pos.x > 0 && minimap->map_pos.x < game->map_width
		&& minimap->map_pos.y >= 0
		&& minimap->map_pos.y < game->map_height)
	{
		if (minimap->map[(int)floor(minimap->map_pos.y)]
			[(int)floor(minimap->map_pos.x)] == 1)
			put_pixel(minimap->img, x, y, game->img.ceiling_color);
		else if (minimap->map[(int)floor(minimap->map_pos.y)]
			[(int)floor(minimap->map_pos.x)] == 3
			|| minimap->map[(int)floor(minimap->map_pos.y)]
			[(int)floor(minimap->map_pos.x)] == -1)
			put_pixel(minimap->img, x, y, LIGHT_SEA_GREEN);
		else if (minimap->map[(int)floor(minimap->map_pos.y)]
			[(int)floor(minimap->map_pos.x)] != 2)
			put_pixel(minimap->img, x, y, game->img.floor_color);
	}
	minimap->map_pos.x += minimap->step.x;
}

void	minimap(t_game *game)
{
	t_minimap		*minimap;
	unsigned int	y;
	unsigned int	x;

	minimap = &game->minimap;
	init_minimap(game, minimap);
	y = 0;
	while (y < minimap->img->height)
	{
		x = 0;
		minimap->map_pos.x = minimap->min.x;
		while (x < minimap->img->width)
		{
			put_minimap(minimap, game, x, y);
			x++;
		}
		minimap->map_pos.y += minimap->step.y;
		y++;
	}
	put_player(minimap->img);
}
