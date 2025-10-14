/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhendrik <nhendrik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 12:36:29 by roversch          #+#    #+#             */
/*   Updated: 2025/10/14 18:01:12 by nhendrik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h>
#include <math.h>

mlx_image_t	*png_to_image(const char *path, mlx_t *mlx)
{
	mlx_texture_t	*texture;
	mlx_image_t		*ret;

	texture = mlx_load_png(path);
	ret = mlx_texture_to_image(mlx, texture);
	mlx_delete_texture(texture);
	return (ret);
}

void	resize_hook(int32_t width, int32_t height, void *ptr)
{
	t_game	*game;

	game = ptr;
	game->width = width;
	game->height = height;
	mlx_delete_image(game->mlx, game->img->hud);
	game->img->hud = png_to_image("./img/Hud.png", game->mlx);
	mlx_resize_image(game->img->hud, width, height);
	mlx_image_to_window(game->mlx, game->img->hud, 0, 0);
	raycast(game);
}

int	main(int argc, char **argv)
{
	t_game		*game;

	if (argc != 2)
		argv[1] = "map.txt";
	// if (check_input(argv[1]) == -1)
		// return (1);
	game = init_game(argv);
	mlx_resize_image(game->img->gun, game->height / 2, game->height / 2);
	raycast(game);
	mlx_image_to_window(game->mlx, game->img->hud, 0, 0);
	mlx_image_to_window(game->mlx, game->img->gun, game->width / 2 - game->img->gun->width / 2, game->height / 2);
	game->img->gun->instances[0].z = 6;
	game->img->hud->instances[0].z = 5;
	mlx_loop_hook(game->mlx, &test_keyhook, game);
	mlx_resize_hook(game->mlx, resize_hook, game);
	mlx_cursor_hook(game->mlx, cursor_hook, game);
	mouse(game);
	mlx_loop(game->mlx);
}
