/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhendrik <nhendrik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 12:36:29 by roversch          #+#    #+#             */
/*   Updated: 2025/10/09 14:15:06 by nhendrik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h>
#include <math.h>

t_player *init_player(double pos_x, double pos_y, double dir_x, double dir_y)
{
	t_player *player;

	player = ft_calloc(1, sizeof(struct s_player));
	if (!player)
		return (NULL);
	player->pos.x = pos_x;
	player->pos.y = pos_y;
	// dir_x -1 == looking left dir_x 1 == looking right
	player->dir.x = dir_x;
	// dir_y -1 == looking down dir_y 1 == looking up
	player->dir.y = dir_y;
	player->plane.x = 0;
	player->plane.y = 0.66;
	return (player);
}

int	main(int argc, char **argv)
{
	t_game		game[1];

	if (argc != 2)
		argv[1] = "map.txt";
	game->player = init_player(2, 5, 1, 0);
	printf("%f\n", game->player->pos.x);
	game->textures = ft_calloc(1, sizeof(struct s_texture));
	game->textures->wall_texture = mlx_load_png("./img/Wallgrey1.png");
	game->world_map = read_map(argv[1], game);
	game->mlx = mlx_init(SCREEN_WIDTH, SCREEN_HEIGHT, "CUB3D", false);
	game->img_wall = mlx_texture_to_image(game->mlx, game->textures->wall_texture);
	game->screen_buffer = NULL;
	mlx_resize_image(game->img_wall, SCALE, SCALE);
	raycast(game);
	//mlx_image_to_window(game->mlx, game->screen_buffer, 0, 0);
	// game->img_wall = mlx_texture_to_image(game->mlx, game->textures->wall_texture);
	// mlx_image_to_window(game->mlx, game->img_wall, 418, 268);
	// mlx_key_hook(game->mlx, &test_keyhook, game);
	mlx_loop_hook(game->mlx, &test_keyhook, game);
	mlx_loop(game->mlx);
}	