/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhendrik <nhendrik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 15:13:12 by roversch          #+#    #+#             */
/*   Updated: 2025/10/27 13:09:28 by nhendrik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h> //can be removed later

static void	move_forward(t_game *game, double speed, const float mod)
{
	t_vector	*pos;
	t_vector	dir;
	double		next_x;
	double		next_y;

	pos = &game->player->pos;
	dir = game->player->dir;
	next_x = pos->x + (speed + mod) * dir.x;
	next_y = pos->y + (speed + mod) * dir.y;
	if (next_x > 0
		&& game->world_map[(int)(pos->y)][(int)(next_x)] != 1)
		pos->x += dir.x * speed;
	if (next_y > 0
		&& game->world_map[(int)(next_y)][(int)(pos->x)] != 1)
		pos->y += dir.y * speed;
}

static void	move_backward(t_game *game, double speed, const float mod)
{
	t_vector	*pos;
	t_vector	dir;
	double		next_x;
	double		next_y;

	pos = &game->player->pos;
	dir = game->player->dir;
	next_x = pos->x - (speed + mod) * dir.x;
	next_y = pos->y - (speed + mod) * dir.y;
	if ((next_x > 0)
		&& game->world_map[(int)(pos->y)][(int)(next_x)] != 1)
		pos->x -= dir.x * speed;
	if ((pos->y - (speed + mod) * dir.y > 0)
		&& game->world_map[(int)(next_y)][(int)(pos->x)] != 1)
		pos->y -= dir.y * speed;
}

static void	move_left(t_game *game, double speed, const float sideways_mod)
{
	t_vector	*pos;
	t_vector	dir;
	double		next_x;
	double		next_y;

	pos = &game->player->pos;
	dir.y = -game->player->dir.x;
	dir.x = game->player->dir.y;
	next_x = pos->x + (speed + sideways_mod) * dir.x;
	next_y = pos->y + (speed + sideways_mod) * dir.y;
	if (next_x > 0
		&& game->world_map[(int)(pos->y)][(int)(next_x)] != 1)
		pos->x += dir.x * speed;
	if (next_y > 0
		&& game->world_map[(int)(next_y)][(int)(pos->x)] != 1)
		pos->y += dir.y * speed;
}

static void	move_right(t_game *game, double speed, const float sideways_mod)
{
	t_vector	*pos;
	t_vector	dir;
	double		next_x;
	double		next_y;

	pos = &game->player->pos;
	dir.y = game->player->dir.x;
	dir.x = -game->player->dir.y;
	next_x = pos->x + (speed + sideways_mod) * dir.x;
	next_y = pos->y + (speed + sideways_mod) * dir.y;
	if (next_x > 0
		&& game->world_map[(int)(pos->y)][(int)(next_x)] != 1)
		pos->x += dir.x * speed;
	if (next_y > 0
		&& game->world_map[(int)(next_y)][(int)(pos->x)] != 1)
		pos->y += dir.y * speed;
}

// add an open flag to all for bonus doors
void	test_keyhook(void *param)
{
	const float	mod = 0.5f;
	const float sideways_mod = 0.15f;
	t_game	*game;
	double	speed;

	if (!param)
		return ;
	game = param;
	get_fps(game);
	speed = 0.005f * game->fps->delta_time;
	if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(game->mlx);
	if (mlx_is_key_down(game->mlx, MLX_KEY_W))
		move_forward(game, speed, mod);
	if (mlx_is_key_down(game->mlx, MLX_KEY_S))
		move_backward(game, speed, mod);
	if (mlx_is_key_down(game->mlx, MLX_KEY_A))
		move_left(game, speed, sideways_mod);
	if (mlx_is_key_down(game->mlx, MLX_KEY_D))
		move_right(game, speed, sideways_mod);
	if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT))
		turn_left(game, speed / 2.0f);
	if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT))
		turn_right(game, speed / 2.0f);
	raycast(game);
}
