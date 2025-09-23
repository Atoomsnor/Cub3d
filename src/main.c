/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhendrik <nhendrik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 12:36:29 by roversch          #+#    #+#             */
/*   Updated: 2025/09/23 18:26:25 by nhendrik         ###   ########.fr       */
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
	return (player);
}

int	main(void)
{
	t_game		game[1];
	game->player = init_player(2, 5, 1, 0);
	printf("%f\n", game->player->pos.x);
	game->mlx = mlx_init(900, 600, "CUB3D", false);
	game->img_wall = mlx_new_image(game->mlx, 10, 10);
	ft_memset(game->img_wall->pixels, 200, game->img_wall->width * game->img_wall->height * sizeof(int32_t));
	mlx_image_to_window(game->mlx, game->img_wall, 440, 290);
	mlx_key_hook(game->mlx, &test_keyhook, game);
	mlx_loop(game->mlx);
}	