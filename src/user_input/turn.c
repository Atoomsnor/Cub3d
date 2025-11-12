/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   turn.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhendrik <nhendrik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 02:15:13 by nhendrik          #+#    #+#             */
/*   Updated: 2025/11/12 22:40:09 by nhendrik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>

void	turn_left(t_game *game, double speed)
{
	t_player	*player;
	double		old_dir_x;
	double		old_plane_x;

	player = &game->player;
	old_dir_x = player->dir.x;
	old_plane_x = player->plane.x;
	player->dir.x = player->dir.x * cos(-speed) - player->dir.y * sin(-speed);
	player->dir.y = old_dir_x * sin(-speed) + player->dir.y * cos(-speed);
	player->plane.x = player->plane.x * cos(-speed)
		- player->plane.y * sin(-speed);
	player->plane.y = old_plane_x * sin(-speed) + player->plane.y * cos(-speed);
}

void	turn_right(t_game *game, double speed)
{
	t_player	*player;
	double		old_dir_x;
	double		old_plane_x;

	player = &game->player;
	old_dir_x = player->dir.x;
	old_plane_x = player->plane.x;
	player->dir.x = player->dir.x * cos(speed) - player->dir.y * sin(speed);
	player->dir.y = old_dir_x * sin(speed) + player->dir.y * cos(speed);
	player->plane.x = player->plane.x * cos(speed)
		- player->plane.y * sin(speed);
	player->plane.y = old_plane_x * sin(speed) + player->plane.y * cos(speed);
}

void	turn_hook(t_game *game, double speed)
{
	if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT))
		turn_left(game, speed);
	if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT))
		turn_right(game, speed);
}
