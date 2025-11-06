/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhendrik <nhendrik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 20:19:35 by nhendrik          #+#    #+#             */
/*   Updated: 2025/11/06 23:12:35 by nhendrik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>
#include <stdio.h>

void	minimap(t_game *game)
{
	int **map;
	t_vector pos;
	t_vector min, map_pos, step;
	int	pixels_per_map_x, pixels_per_map_y;
	uint32_t	i, j;

	ft_memset(game->img.minimap->pixels, 0, game->img.minimap->width * game->img.minimap->height * sizeof(int32_t));
	map = game->world_map;
	pos = game->player.pos;
	pixels_per_map_x = game->img.minimap->width / 10;
	pixels_per_map_y = game->img.minimap->height / 10;
	step.x = 1.0 / pixels_per_map_x;
	step.y = 1.0 / pixels_per_map_y;
	min.x = pos.x - 5;
	min.y = pos.y - 5;
	map_pos = min;
	i = 0;
	while (i < game->img.minimap->height)
	{
		j = 0;
		map_pos.x = min.x;
		while (j < game->img.minimap->width)
		{
			if (map_pos.x > 0 && map_pos.x < game->map_width && map_pos.y >= 0 && map_pos.y < game->map_height)
			{
				if (map[(int)floor(map_pos.y)][(int)floor(map_pos.x)] && map[(int)floor(map_pos.y)][(int)floor(map_pos.x)] == 1)
					put_pixel(game->img.minimap, j, i, game->img.ceiling_color);
				else if (map_pos.x == pos.x && map_pos.y == pos.y)
					put_pixel(game->img.minimap, j, i, 0xFF0000FF);
				else if (map[(int)floor(map_pos.y)][(int)floor(map_pos.x)] != 2)
					put_pixel(game->img.minimap, j, i, game->img.floor_color);
			}
			map_pos.x += step.x;
			j++;
		}
		map_pos.y += step.y;
		i++;
	}
}