/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhendrik <nhendrik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 15:13:12 by roversch          #+#    #+#             */
/*   Updated: 2025/10/09 14:50:15 by nhendrik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h>
#include <math.h>

void move_up(t_game *game, double speed)
{
	if (game->world_map[(int)(game->player->pos.y)][(int)(game->player->pos.x + speed)].content == 0)
	{
		game->player->pos.x += speed;
		raycast(game);
	}
	printf("here %f\n", game->player->pos.x);
}

void move_down(t_game *game, double speed)
{
	if (game->world_map[(int)(game->player->pos.y)][(int)(game->player->pos.x - speed)].content == 0)
	{
		game->player->pos.x -= speed;
		raycast(game);
	}
	printf("here %f\n", game->player->pos.x);
}

void move_forward(t_game *game, double speed)
{
	if (game->player->pos.x + (speed + 0.1f) * game->player->dir.x > 0
			&& game->world_map[(int)(game->player->pos.y)][(int)(game->player->pos.x + (speed + 0.1f) * game->player->dir.x)].content == 0)
		game->player->pos.x += game->player->dir.x * speed;
	if (game->player->pos.y + (speed + 0.1f) * game->player->dir.y > 0
			&& game->world_map[(int)(game->player->pos.y + (speed + 0.1f) * game->player->dir.y)][(int)(game->player->pos.x)].content == 0)
		game->player->pos.y += game->player->dir.y * speed;
}

void move_backward(t_game *game, double speed)
{
	float mod;

	mod = 0.1f;
	// if (game->player->pos.x - (speed - mod) * game->player->dir.x  < 0)
	// 	mod = 0;
	if ((game->player->pos.x - (speed + mod) * game->player->dir.x  > 0) &&game->world_map[(int)(game->player->pos.y)][(int)(game->player->pos.x - (speed + mod) * game->player->dir.x - mod)].content == 0)
		game->player->pos.x -= game->player->dir.x * speed;
	// mod = 0.5f;
	// if (game->player->pos.y - (speed - mod) * game->player->dir.y < 0)
	// 	mod = 0;
	if ((game->player->pos.y - (speed + mod) * game->player->dir.y > 0) && game->world_map[(int)(game->player->pos.y - (speed + mod) * game->player->dir.y)][(int)(game->player->pos.x)].content == 0)
		game->player->pos.y -= game->player->dir.y * speed;
}

void turn_left(t_game *game, double rot_speed)
{
	t_player *player;
	double old_dir_x;
	double old_plane_x;

	player = game->player;
	old_dir_x = player->dir.x;
	old_plane_x = player->plane.x;
	player->dir.x = player->dir.x * cos(-rot_speed) - player->dir.y * sin(-rot_speed);
	player->dir.y = old_dir_x * sin(-rot_speed) + player->dir.y * cos(-rot_speed);
	player->plane.x = player->plane.x * cos(-rot_speed) - player->plane.y * sin(-rot_speed);
	player->plane.y = old_plane_x * sin(-rot_speed) + player->plane.y * cos(-rot_speed);
}

void turn_right(t_game *game, double rot_speed)
{
	t_player *player;
	double old_dir_x;
	double old_plane_x;

	player = game->player;
	old_dir_x = player->dir.x;
	old_plane_x = player->plane.x;
	player->dir.x = player->dir.x * cos(rot_speed) - player->dir.y * sin(rot_speed);
	player->dir.y = old_dir_x * sin(rot_speed) + player->dir.y * cos(rot_speed);
	player->plane.x = player->plane.x * cos(rot_speed) - player->plane.y * sin(rot_speed);
	player->plane.y = old_plane_x * sin(rot_speed) + player->plane.y * cos(rot_speed);
}

void test_keyhook(void *param)
{
	t_game	*game;

	if (!param)
		return ;
	game = param;
	double speed = 0.05f;
	if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(game->mlx);
	if (mlx_is_key_down(game->mlx, MLX_KEY_W))
		move_forward(game, speed);
	if (mlx_is_key_down(game->mlx, MLX_KEY_S))
		move_backward(game, speed);
	// if (mlx_is_key_down(game->mlx, MLX_KEY_W))
		// move_up(game, speed);
	// if (mlx_is_key_down(game->mlx, MLX_KEY_S))
		// move_down(game, speed);
	if (mlx_is_key_down(game->mlx, MLX_KEY_A))
		turn_left(game, 0.05f);
	if (mlx_is_key_down(game->mlx, MLX_KEY_D))
		turn_right(game, 0.05f);
	raycast(game);
}