/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roversch <roversch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 12:36:29 by roversch          #+#    #+#             */
/*   Updated: 2025/11/13 14:41:37 by roversch         ###   ########.fr       */
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
		return (print_error("Error\nWrong amount of arguments\n"), 1);
	if (check_input(argv[1], &parse) == -1)
		return (1);
	if (init_game(&game, parse) == -1)
		return (empty_parse(&parse, true));
	empty_parse(&parse, false);
	if (raycast(&game) == -1)
		return (mlx_terminate(game.mlx), free_matrix(game.world_map), 1);
	if (set_base_visuals(&game) == -1)
		return (mlx_terminate(game.mlx), free_matrix(game.world_map), 1);
	if (mlx_loop_hook(game.mlx, &key_hook, &game) == false)
		return (mlx_terminate(game.mlx), free_matrix(game.world_map), 1);
	mlx_resize_hook(game.mlx, resize_hook, &game);
	mlx_loop(game.mlx);
	mlx_terminate(game.mlx);
	free_matrix(game.world_map);
}
