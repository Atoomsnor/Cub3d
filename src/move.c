/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhendrik <nhendrik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 15:13:12 by roversch          #+#    #+#             */
/*   Updated: 2025/10/07 18:36:17 by nhendrik         ###   ########.fr       */
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

void test_keyhook(mlx_key_data_t keydata, void *param)
{
	t_game	*game;

	if (!param)
		return ;
	game = param;
	if (keydata.action == MLX_PRESS)
	{
		double speed = 0.25f;
		if (keydata.key == MLX_KEY_ESCAPE)
			mlx_close_window(game->mlx);
		else if (keydata.key == MLX_KEY_W)
			move_up(game, speed);
		else if (keydata.key == MLX_KEY_S)
			move_down(game, speed);
	}
}