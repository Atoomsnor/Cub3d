/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhendrik <nhendrik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 12:36:29 by roversch          #+#    #+#             */
/*   Updated: 2025/09/22 14:43:56 by nhendrik         ###   ########.fr       */
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

	game->player->y += 1;
	printf("%i\n", (wall_y - game->player->y));
	if (wall_y - game->player->y > 0)
	{
		mlx_resize_image(game->img, 900 / (wall_y - game->player->y), 600 / (wall_y - game->player->y));
		game->img->instances->x = 900 / 2 - (900 / (wall_y - game->player->y) / 2);
		game->img->instances->y = 600 / 2 - (600 / (wall_y - game->player->y) / 2);
	}
}

void calculate_pos_s(t_game *game)
{
	int wall_y = 15;

	game->player->y -= 1;
	printf("%i\n", (wall_y - game->player->y));
	if (wall_y - game->player->y > 0)
	{
		mlx_resize_image(game->img, 900 / (wall_y - game->player->y), 600 / (wall_y - game->player->y));
		game->img->instances->x = 900 / 2 - (900 / (wall_y - game->player->y) / 2);
		game->img->instances->y = 600 / 2 - (600 / (wall_y - game->player->y) / 2);
	}
}

void test_keyhook(mlx_key_data_t keydata, void *param)
{
	if (!param)
		return ;
	if (keydata.key == MLX_KEY_W && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
		calculate_pos_w((t_game *)param);
	else if (keydata.key == MLX_KEY_S && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
		calculate_pos_s((t_game *)param);
}

int	main(void)
{
	mlx_image_t *img;
	mlx_image_t *img2;
	mlx_t		*mlx;
	t_game		game[1];

	game->player->x = 5;
	printf("%i\n", game->player->x);
	game->player->y = 0;
	mlx = mlx_init(900, 600, "CUB3D", false);
	img = mlx_new_image(mlx, 200, 200);
	ft_memset(img->pixels, 255, img->width * img->height * sizeof(int32_t));
	mlx_image_to_window(mlx, img, 0, 0);
	img2 = mlx_new_image(mlx, 10, 10);
	ft_memset(img2->pixels, 200, img2->width * img2->height * sizeof(int32_t));
	mlx_image_to_window(mlx, img2, 440, 290);
	game->img = img2;
	game->mlx = mlx;
	mlx_key_hook(mlx, &test_keyhook, game);
	mlx_loop_hook(mlx, testfunc, img);
	mlx_loop(mlx);
}	