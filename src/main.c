/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roversch <roversch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 12:36:29 by roversch          #+#    #+#             */
/*   Updated: 2025/09/22 15:25:30 by roversch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h>
#include <math.h>

int	main(void)
{
	// mlx_image_t *img;
	// mlx_image_t *img2;
	// mlx_t		*mlx;
	t_game		game[1];

	game->player->x = 5;
	printf("%i\n", game->player->x);
	game->player->y = 0;
	game->mlx = mlx_init(900, 600, "CUB3D", false);
	game->img_bounce = mlx_new_image(game->mlx, 200, 200);
	ft_memset(game->img_bounce->pixels, 255, game->img_bounce->width * game->img_bounce->height * sizeof(int32_t));
	mlx_image_to_window(game->mlx, game->img_bounce, 0, 0);
	game->img_wall = mlx_new_image(game->mlx, 10, 10);
	ft_memset(game->img_wall->pixels, 200, game->img_wall->width * game->img_wall->height * sizeof(int32_t));
	mlx_image_to_window(game->mlx, game->img_wall, 440, 290);
	// game->img = img2;
	// game->mlx = mlx;
	mlx_key_hook(game->mlx, &test_keyhook, game);
	mlx_loop_hook(game->mlx, testfunc, game->img_bounce);
	mlx_loop(game->mlx);
}	