/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roversch <roversch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 00:29:41 by nhendrik          #+#    #+#             */
/*   Updated: 2025/11/06 16:28:13 by roversch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h>

static void	init_player(t_player *player, t_vector pos, t_vector dir)
{
	const double	fov_scale = 0.66;

	player->pos = pos;
	player->pos.x += 0.5;
	player->pos.y += 0.5;
	// dir_x -1 == looking left dir_x 1 == looking right
	player->dir = dir;
	// dir_y -1 == looking down dir_y 1 == looking up
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

static void	init_anime(t_sprite_anime *anime)
{
	anime->anime_start_time = 0;
	anime->in_anime = false;
}

int	init_game(t_game *game, t_parse parse)
{
	init_player(&game->player, parse.pos, parse.dir);
	game->width = SCREEN_WIDTH;
	game->height = SCREEN_HEIGHT;
	game->world_map = parse.int_map;
	game->mlx = mlx_init(game->width, game->height, "CUB3D", true);
	if (!game->mlx)
		return (-1);
	if (init_images(game, parse) == -1)
		return (mlx_terminate(game->mlx), -1);
	init_fps(&game->fps);
	init_anime(&game->anime);
	game->screen_buffer = NULL;
	return (0);
}
