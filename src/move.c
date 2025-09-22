/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roversch <roversch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 15:13:12 by roversch          #+#    #+#             */
/*   Updated: 2025/09/22 15:30:29 by roversch         ###   ########.fr       */
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

void calculate_pos_w(t_game *game)
{
	int wall_y = 15;
	int diff = wall_y - game->player->y;

	game->player->y += 1;
	printf("%i\n", diff);
	if (diff > 0)
	{
		int width = 900 / diff;
		int height = 600 / diff;
		game->img_wall->instances->x = 900 / 2 - width / 2;
		game->img_wall->instances->y = 600 / 2 - height / 2;
		mlx_resize_image(game->img_wall, width, height);
	}
}

void calculate_pos_s(t_game *game)
{
	int wall_y = 15;
	int diff = wall_y - game->player->y;

	game->player->y -= 1;
	printf("%i\n", diff);
	if (diff > 0)
	{
		int width = 900 / diff;
		int height = 600 / diff;
		game->img_wall->instances->x = 900 / 2 - width / 2;
		game->img_wall->instances->y = 600 / 2 - height / 2;
		mlx_resize_image(game->img_wall, width, height);
	}
}

void test_keyhook(mlx_key_data_t keydata, void *param)
{
	t_game	*game;

	if (!param)
		return ;
	game = param;
	if (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT)
	{
		if (keydata.key == MLX_KEY_ESCAPE)
			mlx_close_window(game->mlx);
		else if (keydata.key == MLX_KEY_W)
			calculate_pos_w(game);
		else if (keydata.key == MLX_KEY_S)
			calculate_pos_s(game);
	}
}