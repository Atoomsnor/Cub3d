/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roversch <roversch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 12:36:29 by roversch          #+#    #+#             */
/*   Updated: 2025/10/28 12:59:13 by roversch         ###   ########.fr       */
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
	mlx_image_to_window(game->mlx, game->img->gun1, 0, 0);
	game->img->hud->instances[0].z = 5;
	mlx_loop_hook(game->mlx, &test_keyhook, game);
	mlx_resize_hook(game->mlx, resize_hook, game);
	mlx_cursor_hook(game->mlx, cursor_hook, game);
	mouse(game);
	mlx_loop(game->mlx);
}
