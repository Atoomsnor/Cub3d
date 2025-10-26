/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resize.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhendrik <nhendrik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 02:19:41 by nhendrik          #+#    #+#             */
/*   Updated: 2025/10/26 02:19:51 by nhendrik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	resize_image(t_game *game, mlx_image_t **img, char *path, t_vector pos)
{
	mlx_delete_image(game->mlx, *img);
	*img = png_to_image(path, game->mlx);
	mlx_resize_image(*img, game->width, game->height);
	mlx_image_to_window(game->mlx, *img, pos.x, pos.y);
}

void	resize_hook(int32_t width, int32_t height, void *ptr)
{
	t_game		*game;
	t_vector	pos;

	game = ptr;
	game->width = width;
	game->height = height;
	pos.x = 0;
	pos.y = 0;
	resize_image(game, &game->img->hud, "./img/Hud.png", pos);
	pos.x = game->width;
	raycast(game);
}