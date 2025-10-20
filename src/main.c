/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhendrik <nhendrik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 12:36:29 by roversch          #+#    #+#             */
/*   Updated: 2025/10/20 13:59:03 by nhendrik         ###   ########.fr       */
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

void resize_image(t_game *game, mlx_image_t **img, char *path, t_vector pos)
{
	mlx_delete_image(game->mlx, *img);
	*img = png_to_image(path, game->mlx);
	mlx_resize_image(*img, game->width, game->height);
	mlx_image_to_window(game->mlx, *img, pos.x, pos.y);
}

void	resize_hook(int32_t width, int32_t height, void *ptr)
{
	t_game		*game;
	t_vector	pos;

	game = ptr;
	game->width = width;
	game->height = height;
	pos.x = 0;
	pos.y = 0;
	resize_image(game, &game->img->hud, "./img/Hud.png", pos);
	pos.x = game->width;
	raycast(game);
}

int	main(int argc, char **argv)
{
	t_game		*game;
	t_parse		parse;

	if (argc != 2)
		argv[1] = "map.txt";
	if (check_input(argv[1], &parse) == -1)
		return (1);
	game = init_game(parse);
	raycast(game);
	mlx_image_to_window(game->mlx, game->img->hud, 0, 0);
	game->img->hud->instances[0].z = 5;
	mlx_loop_hook(game->mlx, &test_keyhook, game);
	mlx_resize_hook(game->mlx, resize_hook, game);
	mlx_cursor_hook(game->mlx, cursor_hook, game);
	mouse(game);
	mlx_loop(game->mlx);
}
