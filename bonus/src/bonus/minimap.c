/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roversch <roversch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 20:19:35 by nhendrik          #+#    #+#             */
/*   Updated: 2025/11/11 11:55:42 by roversch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>

void	init_minimap(t_game *game)
{
	int	pixels_per_map_x;
	int	pixels_per_map_y;

	fill_buffer_color(game->minimap.img, 0xFF404000);
	game->minimap.map = game->world_map;
	game->minimap.pos = game->player.pos;
	game->minimap.min.x = game->minimap.pos.x - 5;
	game->minimap.min.y = game->minimap.pos.y - 5;
	pixels_per_map_x = game->minimap.img->width / 10;
	pixels_per_map_y = game->minimap.img->height / 10;
	game->minimap.step.x = 1.0 / pixels_per_map_x;
	game->minimap.step.y = 1.0 / pixels_per_map_y;
	game->minimap.map_pos = game->minimap.min;
}

void put_player(mlx_image_t *img)
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
			put_pixel(img, x, y, 0xFF000000);
			x++;
		}
		y++;
	}
}

int	resize_minimap(t_game *game)
{
	int	z;

	z = game->minimap.img->instances[0].z;
	mlx_delete_image(game->mlx, game->minimap.img);
	game->minimap.img = mlx_new_image(game->mlx, game->width / 6, game->height / 4);
	if (!game->minimap.img)
		return (-1);
	if (mlx_image_to_window(game->mlx, game->minimap.img, game->width / 40, ceil((double)game->height / 26.666667f)) == -1)
		return (-1);
	game->minimap.img->instances[0].z = z;
	return (0);
}

void	minimap(t_game *game)
{
	unsigned int	y;
	unsigned int	x;

	init_minimap(game);
	y = 0;
	while (y < game->minimap.img->height)
	{
		x = 0;
		game->minimap.map_pos.x = game->minimap.min.x;
		while (x < game->minimap.img->width)
		{
			if (game->minimap.map_pos.x > 0 && game->minimap.map_pos.x < game->map_width && game->minimap.map_pos.y >= 0 && game->minimap.map_pos.y < game->map_height)
			{
				if (game->minimap.map[(int)floor(game->minimap.map_pos.y)][(int)floor(game->minimap.map_pos.x)] && game->minimap.map[(int)floor(game->minimap.map_pos.y)][(int)floor(game->minimap.map_pos.x)] == 1)
					put_pixel(game->minimap.img, x, y, game->img.ceiling_color);
				else if (game->minimap.map[(int)floor(game->minimap.map_pos.y)][(int)floor(game->minimap.map_pos.x)] != 2)
					put_pixel(game->minimap.img, x, y, game->img.floor_color);
			}
			game->minimap.map_pos.x += game->minimap.step.x;
			x++;
		}
		game->minimap.map_pos.y += game->minimap.step.y;
		y++;
	}
	put_player(game->minimap.img);
}
