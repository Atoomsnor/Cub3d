/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhendrik <nhendrik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 00:29:41 by nhendrik          #+#    #+#             */
/*   Updated: 2025/11/11 14:06:05 by nhendrik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_player(t_player *player, t_vector pos, t_vector dir)
{
	const double	fov_scale = 0.66;

	player->pos = pos;
	player->pos.x += 0.5;
	player->pos.y += 0.5;
	player->dir = dir;
	player->plane.x = -player->dir.y * fov_scale;
	player->plane.y = player->dir.x * fov_scale;
}

static void	init_fps(t_fps *fps)
{
	fps->start_time = get_time();
	fps->last_time = 0;
	fps->time = 0;
	fps->delta_time = 0;
	fps->frames = 0;
}

static void	get_map_height_width(t_game *game, int **map)
{
	int	width;
	int	i;
	int	j;

	i = 0;
	width = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
			j++;
		if (j > width)
			width = j;
		i++;
	}
	game->map_width = width;
	game->map_height = i;
}

int	init_game(t_game *game, t_parse parse)
{
	init_player(&game->player, parse.pos, parse.dir);
	game->width = SCREEN_WIDTH;
	game->height = SCREEN_HEIGHT;
	game->world_map = parse.int_map;
	get_map_height_width(game, game->world_map);
	game->mlx = mlx_init(game->width, game->height, "CUB3D", true);
	if (!game->mlx)
		return (-1);
	if (init_images(game, parse) == -1)
		return (mlx_terminate(game->mlx), -1);
	init_fps(&game->fps);
	game->screen_buffer = NULL;
	return (0);
}
