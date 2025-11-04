/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roversch <roversch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 11:24:51 by nhendrik          #+#    #+#             */
/*   Updated: 2025/11/04 19:53:39 by roversch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h>

void enable_and_disable_gun(mlx_image_t *prev_anime, mlx_image_t *next_anime)
{
	prev_anime->enabled = false;
	next_anime->enabled = true;
}

void	shoot(t_game *game)
{
	bool	shoot_down;
	size_t	time;

	shoot_down = (mlx_is_mouse_down(game->mlx, MLX_MOUSE_BUTTON_LEFT)
			|| mlx_is_key_down(game->mlx, MLX_KEY_SPACE));
	time = get_time() - game->fps.start_time;
	if (shoot_down && !game->anime.in_anime)
	{
		game->anime.in_anime = true;
		game->anime.anime_start_time = time;
	}
	printf("%zu\n", time - game->anime.anime_start_time);
	if (game->anime.in_anime && time - game->anime.anime_start_time < 100)
		enable_and_disable_gun(game->img.gun[0], game->img.gun[1]);
	else if (game->anime.in_anime && time - game->anime.anime_start_time < 200)
		enable_and_disable_gun(game->img.gun[1], game->img.gun[2]);
	else if (game->anime.in_anime && time - game->anime.anime_start_time < 300)
		enable_and_disable_gun(game->img.gun[2], game->img.gun[3]);
	else if (game->anime.in_anime && time - game->anime.anime_start_time < 400)
		enable_and_disable_gun(game->img.gun[3], game->img.gun[4]);
	else if (game->anime.in_anime && time - game->anime.anime_start_time < 500)
	{
		// game->img.gun[1]->instances[0].enabled = false;
		// game->img.gun[2]->instances[0].enabled = false;
		// game->img.gun[3]->instances[0].enabled = false;
		enable_and_disable_gun(game->img.gun[4], game->img.gun[0]);
		game->anime.in_anime = false;
	}
}