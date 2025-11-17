/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_images.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhendrik <nhendrik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 15:54:25 by roversch          #+#    #+#             */
/*   Updated: 2025/11/17 11:17:25 by nhendrik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"
#include <stdio.h>

static int	resize_walls(t_img *img)
{
	if (!mlx_resize_image(img->no, SCALE, SCALE))
		return (print_error("Error\nFailed resizing image\n"));
	if (!mlx_resize_image(img->ea, SCALE, SCALE))
		return (print_error("Error\nFailed resizing image\n"));
	if (!mlx_resize_image(img->so, SCALE, SCALE))
		return (print_error("Error\nFailed resizing image\n"));
	if (!mlx_resize_image(img->we, SCALE, SCALE))
		return (print_error("Error\nFailed resizing image\n"));
	return (0);
}

static int	png_to_environment(t_img *img, mlx_t *mlx, t_parse parse)
{
	img->hud = png_to_image("./img/hud_bonus.png", mlx);
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
	if (resize_walls(img) == -1)
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
	game->minimap.img = mlx_new_image(game->mlx,
			SCREEN_WIDTH / 6, SCREEN_HEIGHT / 4);
	if (!game->minimap.img)
		return (-1);
	if (mlx_image_to_window(game->mlx, game->minimap.img,
			SCREEN_WIDTH / 40, (double)SCREEN_HEIGHT / 26.666667f) == -1)
		return (-1);
	game->minimap.img->instances[0].z = 10;
	if (png_to_environment(&game->img, game->mlx, parse) == -1)
		return (-1);
	if (png_to_elements(&game->img, game->mlx) == -1)
		return (-1);
	disable_instances(&game->img);
	return (0);
}

int	set_base_visuals(t_game *game)
{
	int	i;

	if (mlx_image_to_window(game->mlx, game->img.hud, 0, 0) == -1)
		return (print_error("Error\nImage to window failure\n"));
	game->img.hud->instances[0].z = 5;
	if (mlx_image_to_window(game->mlx, game->img.faces[0], 0, 0) == -1)
		return (print_error("Error\nImage to window failure\n"));
	if (mlx_image_to_window(game->mlx, game->img.faces[1], 0, 0) == -1)
		return (print_error("Error\nImage to window failure\n"));
	game->img.faces[0]->instances[0].z = 7;
	game->img.faces[1]->instances[0].z = 7;
	i = 0;
	while (i < 5)
	{
		if (mlx_image_to_window(game->mlx, game->img.gun[i], 0, 0) == -1)
			return (print_error("Error\nImage to window failure\n"));
		game->img.gun[i]->instances[0].z = 1;
		i++;
	}
	return (0);
}
