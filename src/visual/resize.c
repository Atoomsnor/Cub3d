/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resize.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roversch <roversch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 02:19:41 by nhendrik          #+#    #+#             */
/*   Updated: 2025/11/13 14:48:19 by roversch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	resize_image(t_game *game, mlx_image_t **img,
		char *path, bool enabled)
{
	int	z;

	z = 0;
	if (*img)
	{
		z = (*img)->instances[0].z;
		mlx_delete_image(game->mlx, *img);
	}
	*img = png_to_image(path, game->mlx);
	if (!*img)
		return (-1);
	if (mlx_resize_image(*img, game->width, game->height) == false)
		return (-1);
	if (mlx_image_to_window(game->mlx, *img, 0, 0) == -1)
		return (-1);
	(*img)->enabled = enabled;
	(*img)->instances[0].z = z;
	return (0);
}

void	resize_hook(int32_t width, int32_t height, void *ptr)
{
	t_game	*game;

	game = ptr;
	game->width = width;
	game->height = height;
	if (resize_image(game, &game->img.hud, "./img/hud.png", true) == -1)
		return ((void)print_error("Error\nResize Image failure\n"));
	if (resize_image(game, &game->img.gun, "./img/gun1.png", true) == -1)
		return ((void)print_error("Error\nResize Image failure\n"));
	if (raycast(game) == -1)
		return ;
}
