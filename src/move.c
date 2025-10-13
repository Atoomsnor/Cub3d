/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhendrik <nhendrik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 15:13:12 by roversch          #+#    #+#             */
/*   Updated: 2025/10/13 17:39:33 by nhendrik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h> //can be removed later
#include <math.h>

static void	move_forward(t_game *game, double speed, float mod)
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

static void	move_backward(t_game *game, double speed, float mod)
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

void	turn_left(t_game *game, double speed)
{
	t_player	*player;
	double		old_dir_x;
	double		old_plane_x;

	player = game->player;
	old_dir_x = player->dir.x;
	old_plane_x = player->plane.x;
	player->dir.x = player->dir.x * cos(-speed) - player->dir.y * sin(-speed);
	player->dir.y = old_dir_x * sin(-speed) + player->dir.y * cos(-speed);
	player->plane.x = player->plane.x * cos(-speed) - player->plane.y * sin(-speed);
	player->plane.y = old_plane_x * sin(-speed) + player->plane.y * cos(-speed);
}

void	turn_right(t_game *game, double speed)
{
	t_player	*player;
	double		old_dir_x;
	double		old_plane_x;

	player = game->player;
	old_dir_x = player->dir.x;
	old_plane_x = player->plane.x;
	player->dir.x = player->dir.x * cos(speed) - player->dir.y * sin(speed);
	player->dir.y = old_dir_x * sin(speed) + player->dir.y * cos(speed);
	player->plane.x = player->plane.x * cos(speed) - player->plane.y * sin(speed);
	player->plane.y = old_plane_x * sin(speed) + player->plane.y * cos(speed);
}

// add an open flag to all for bonus doors
void	test_keyhook(void *param)
{
	t_game	*game;
	double	speed;
	float	mod;

	if (!param)
		return ;
	game = param;
	get_fps(game);
	speed = 0.005f * game->fps->delta_time;
	mod = 0.2f;
	if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(game->mlx);
	if (mlx_is_key_down(game->mlx, MLX_KEY_W))
		move_forward(game, speed, mod);
	if (mlx_is_key_down(game->mlx, MLX_KEY_S))
		move_backward(game, speed, mod);
	if (mlx_is_key_down(game->mlx, MLX_KEY_A))
		turn_left(game, speed / 2.0f);
	if (mlx_is_key_down(game->mlx, MLX_KEY_D))
		turn_right(game, speed / 2.0f);
	raycast(game);
}
