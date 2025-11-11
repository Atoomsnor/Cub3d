/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roversch <roversch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 12:36:29 by roversch          #+#    #+#             */
/*   Updated: 2025/11/11 12:32:54 by roversch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdlib.h>
#include <stdio.h>

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
