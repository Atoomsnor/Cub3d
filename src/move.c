/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhendrik <nhendrik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 15:13:12 by roversch          #+#    #+#             */
/*   Updated: 2025/10/06 13:40:47 by nhendrik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h>
#include <math.h>

void testfunc(void *ptr)
{
	mlx_image_t *img;
	static int x = 5;
	static int y = 5;
	static int bounce = 0;

	img = (mlx_image_t *)ptr;
	img->instances[0].x += x;
	img->instances[0].y += y;
	if (img->instances[0].x >= 700 || img->instances[0].x <= 0)
	{
		x = -x;
		bounce++;
	}
	if (img->instances[0].y >= 400 || img->instances[0].y <= 0)
	{
		y = -y;
		bounce++;
	}
	if (bounce == 5)
		bounce = 0, img->instances[0].z++;
}

void calculate_pos_w(t_game *game, double wall_y, double speed)
{
	double diff = wall_y - game->player->pos.y;

	printf("%f\n", diff);
	if (diff >= 1)
	{
		game->player->pos.y += speed;
		int width = 900 / diff;
		int height = 600 / diff;
		game->img_wall->instances->x = 900 / 2 - width / 2;
		game->img_wall->instances->y = 600 / 2 - height / 2;
		mlx_resize_image(game->img_wall, width, height);
	}
}

void calculate_pos_s(t_game *game, double wall_y, double speed)
{
	double diff = wall_y - game->player->pos.y;

	printf("%f\n", diff);
	if (diff > 0)
	{
		game->player->pos.y -= speed;
		int width = 900 / diff;
		int height = 600 / diff;
		game->img_wall->instances->x = 900 / 2 - width / 2;
		game->img_wall->instances->y = 600 / 2 - height / 2;
		mlx_resize_image(game->img_wall, width, height);
	}
}

void move_up(t_game *game, double speed)
{
	if (game->world_map[(int)game->player->pos.x][(int)(game->player->pos.y + speed)] == 0)
	{
		game->player->pos.y += speed;
		raycast(game);
	}
	printf("here %f\n", game->player->pos.y);
}

void move_down(t_game *game, double speed)
{
	if (game->world_map[(int)game->player->pos.x][(int)(game->player->pos.y - speed)] == 0)
	{
		game->player->pos.y -= speed;
		raycast(game);
	}
	printf("here %f\n", game->player->pos.y);
}

void test_keyhook(mlx_key_data_t keydata, void *param)
{
	t_game	*game;

	if (!param)
		return ;
	game = param;
	if (keydata.action == MLX_PRESS)
	{
		double speed = 1.0f;
		if (keydata.key == MLX_KEY_ESCAPE)
			mlx_close_window(game->mlx);
		else if (keydata.key == MLX_KEY_W)
			move_up(game, speed);
		else if (keydata.key == MLX_KEY_S)
			move_down(game, speed);
	}
}