/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhendrik <nhendrik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 12:36:29 by roversch          #+#    #+#             */
/*   Updated: 2025/11/07 00:10:19 by nhendrik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

// void	print_map(char **map, int width)
// {
// 	for (int i = 0; map[i]; i++)
// 	{
// 		for (int j = 0; j < width; j++)
// 		{
// 			if (!map[i][j])
// 				printf("J");
// 			else
// 				printf("%c", map[i][j]);
// 		}
// 		printf("\n");
// 	}
// }

mlx_image_t	*png_to_image(const char *path, mlx_t *mlx)
{
	mlx_texture_t	*texture;
	mlx_image_t		*ret;

	texture = mlx_load_png(path);
	if (!texture)
		return (NULL);
	ret = mlx_texture_to_image(mlx, texture);
	mlx_delete_texture(texture);
	if (!ret)
		return (NULL);
	return (ret);
}

int	main(int argc, char **argv)
{
	t_game		game;
	t_parse		parse;

	if (argc != 2)
		argv[1] = "./maps/42.cub";
	if (check_input(argv[1], &parse) == -1)
		return (1);
	if (init_game(&game, parse) == -1)
		return (empty_parse(&parse, true));
	empty_parse(&parse, false);
	raycast(&game);
	minimap(&game);
	set_base_visuals(&game);
	mlx_loop_hook(game.mlx, &key_hook, &game);
	mlx_resize_hook(game.mlx, resize_hook, &game);
	mlx_cursor_hook(game.mlx, cursor_hook, &game);
	mouse_hook(&game);
	mlx_loop(game.mlx);
	mlx_terminate(game.mlx);
	free_matrix(game.world_map);
}
