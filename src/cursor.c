/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhendrik <nhendrik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 17:26:03 by nhendrik          #+#    #+#             */
/*   Updated: 2025/10/13 19:05:35 by nhendrik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h>

void mouse(t_game *game)
{
	mlx_win_cursor_t *curs;
	int x;
	int y;

	x = 0;
	y = 0;
	mlx_get_mouse_pos(game->mlx, &x, &y);
	game->mouse.x = x;
	game->mouse.y = y;
	curs = mlx_create_cursor(mlx_load_png("./img/Gun.png"));
	mlx_set_cursor(game->mlx, curs);
}

void cursor_hook(double x, double y, void *ptr)
{
	t_game	*game;
	double	speed;

	
	(void)y;
	game = (t_game *)ptr;
	mlx_set_mouse_pos(game->mlx, game->width / 2, game->height / 2);
	speed = 0;
	if (game->mouse.x > x)
	{
		printf("%f %f\n", game->mouse.x, x);
		speed = (game->mouse.x - x) * (game->fps->delta_time / 10000.0f);
		turn_left(game, speed);
		mlx_set_mouse_pos(game->mlx, game->width / 2, game->height / 2);
		game->mouse.x = game->width / 2;
	}
	else if (game->mouse.x < x)
	{
		printf("%f %f\n", game->mouse.x, x);
		speed = (x - game->mouse.x) * (game->fps->delta_time / 10000.0f);
		turn_right(game, speed);
		mlx_set_mouse_pos(game->mlx, game->width / 2, game->height / 2);
		game->mouse.x = game->width / 2;
	}
}