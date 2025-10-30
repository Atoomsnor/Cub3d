/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhendrik <nhendrik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 12:36:29 by roversch          #+#    #+#             */
/*   Updated: 2025/10/29 21:42:41 by nhendrik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h>
#include <math.h>

void print_map(char **map, int width)
{
	for (int i = 0; map[i]; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (!map[i][j])
				printf("J");
			else
				printf("%c", map[i][j]);
		}
		printf("\n");
	}
}

mlx_image_t	*png_to_image(const char *path, mlx_t *mlx)
{
	mlx_texture_t	*texture;
	mlx_image_t		*ret;

	texture = mlx_load_png(path);
	ret = mlx_texture_to_image(mlx, texture);
	mlx_delete_texture(texture);
	return (ret);
}

int	free_and_null(void *ptr)
{
	free(ptr);
	ptr = NULL;
	return (-1);
}

int empty_parse(t_parse *parse, bool map)
{
	//free int map (maybe pointer saved in game struct so conditional?)
	//free char map
	//free texture paths (ptr in game struct, conditional?)
	return (1);	
}

int	main(int argc, char **argv)
{
	t_game		game;
	t_parse		parse;

	if (argc != 2)
		argv[1] = "map.txt";
	if (check_input(argv[1], &parse) == -1)
		return (1);
	if (init_game(&game, parse) == -1)
		return (empty_parse(&parse, true));
	raycast(&game);
	mlx_image_to_window(game.mlx, game.img.hud, 0, 0);
	game.img.hud->instances[0].z = 5;
	mlx_loop_hook(game.mlx, &test_keyhook, &game);
	mlx_resize_hook(game.mlx, resize_hook, &game);
	mlx_cursor_hook(game.mlx, cursor_hook, &game);
	mouse(&game);
	mlx_loop(game.mlx);
}
