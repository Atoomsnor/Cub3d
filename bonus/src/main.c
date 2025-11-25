/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhendrik <nhendrik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 12:36:29 by roversch          #+#    #+#             */
/*   Updated: 2025/11/26 00:30:14 by nhendrik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"
#include <stdlib.h>
#include <stdio.h>

void	main_hook(void *param)
{
	t_game		*game;
	double		speed;

	if (!param)
		return ;
	game = param;
	get_fps(game);
	minimap(game);
	speed = 0.005f * game->fps.delta_time;
	if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(game->mlx);
	move(game, speed);
	turn(game, speed / 2.0f);
	shoot(game);
	if (raycast(game) == -1)
		return ;
}

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
	minimap(&game);
	if (set_base_visuals(&game) == -1)
		return (mlx_terminate(game.mlx), free_matrix(game.world_map), 1);
	if (mlx_loop_hook(game.mlx, &main_hook, &game) == false)
		return (mlx_terminate(game.mlx), free_matrix(game.world_map), 1);
	mlx_resize_hook(game.mlx, resize_hook, &game);
	mlx_cursor_hook(game.mlx, cursor_hook, &game);
	init_mouse(&game);
	mlx_loop(game.mlx);
	mlx_terminate(game.mlx);
	free_matrix(game.world_map);
}
