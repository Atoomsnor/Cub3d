/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gun.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roversch <roversch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 11:24:51 by nhendrik          #+#    #+#             */
/*   Updated: 2025/11/11 11:55:42 by roversch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	enable_and_disable_gun(mlx_image_t *prev_anime,
		mlx_image_t *next_anime)
{
	prev_anime->enabled = false;
	next_anime->enabled = true;
}

static void	reset_gun(t_game *game)
{
	game->img.gun[1]->enabled = false;
	game->img.gun[2]->enabled = false;
	game->img.gun[3]->enabled = false;
	enable_and_disable_gun(game->img.gun[4], game->img.gun[0]);
	game->anime.in_anime = false;
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
	if (game->anime.in_anime && time - game->anime.anime_start_time < 100)
		enable_and_disable_gun(game->img.gun[0], game->img.gun[1]);
	else if (game->anime.in_anime && time - game->anime.anime_start_time < 200)
		enable_and_disable_gun(game->img.gun[1], game->img.gun[2]);
	else if (game->anime.in_anime && time - game->anime.anime_start_time < 300)
		enable_and_disable_gun(game->img.gun[2], game->img.gun[3]);
	else if (game->anime.in_anime && time - game->anime.anime_start_time < 400)
		enable_and_disable_gun(game->img.gun[3], game->img.gun[4]);
	else if (game->anime.in_anime)
		reset_gun(game);
}
