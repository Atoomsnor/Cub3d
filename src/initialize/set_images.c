/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_images.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roversch <roversch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 15:54:25 by roversch          #+#    #+#             */
/*   Updated: 2025/11/13 14:39:43 by roversch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h>

static int	png_to_environment(t_img *img, mlx_t *mlx, t_parse parse)
{
	img->hud = png_to_image("./img/hud.png", mlx);
	if (!img->hud)
		return (-1);
	img->no = png_to_image(parse.no_texture, mlx);
	if (!img->no)
		return (-1);
	img->ea = png_to_image(parse.ea_texture, mlx);
	if (!img->ea)
		return (-1);
	img->so = png_to_image(parse.so_texture, mlx);
	if (!img->so)
		return (-1);
	img->we = png_to_image(parse.we_texture, mlx);
	if (!img->we)
		return (-1);
	img->floor_color = str_to_color(parse.floor_color);
	if (img->floor_color == -1)
		return (-1);
	img->ceiling_color = str_to_color(parse.ceiling_color);
	if (img->ceiling_color == -1)
		return (-1);
	return (0);
}

int	init_images(t_game *game, t_parse parse)
{
	if (png_to_environment(&game->img, game->mlx, parse) == -1)
		return (-1);
	game->img.gun = png_to_image("./img/gun1.png", game->mlx);
	if (!game->img.gun)
		return (-1);
	return (0);
}

int	set_base_visuals(t_game *game)
{
	if (mlx_image_to_window(game->mlx, game->img.hud, 0, 0) == -1)
		return (print_error("Error\nImage to window failure\n"));
	game->img.hud->instances[0].z = 5;
	if (mlx_image_to_window(game->mlx, game->img.gun, 0, 0) == -1)
		return (print_error("Error\nImage to window failure\n"));
	game->img.gun->instances[0].z = 1;
	return (0);
}
