/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_images.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roversch <roversch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 15:54:25 by roversch          #+#    #+#             */
/*   Updated: 2025/11/13 14:49:55 by roversch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"
#include <stdio.h>

static int	png_to_environment(t_img *img, mlx_t *mlx, t_parse parse)
{
	img->hud = png_to_image("./img/hud_bonus.png", mlx);
	if (!img->hud)
		return (-1);
	img->door = png_to_image("./img/door.png", mlx);
	if (!img->door)
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

static int	png_to_elements(t_img *img, mlx_t *mlx)
{
	img->faces[0] = png_to_image("./img/face_left.png", mlx);
	if (!img->faces[0])
		return (-1);
	img->faces[1] = png_to_image("./img/face_right.png", mlx);
	if (!img->faces[1])
		return (-1);
	img->gun[0] = png_to_image("./img/gun1.png", mlx);
	if (!img->gun[0])
		return (-1);
	img->gun[1] = png_to_image("./img/gun2.png", mlx);
	if (!img->gun[1])
		return (-1);
	img->gun[2] = png_to_image("./img/gun3.png", mlx);
	if (!img->gun[2])
		return (-1);
	img->gun[3] = png_to_image("./img/gun4.png", mlx);
	if (!img->gun[3])
		return (-1);
	img->gun[4] = png_to_image("./img/gun5.png", mlx);
	if (!img->gun[4])
		return (-1);
	return (0);
}

static void	disable_instances(t_img *img)
{
	img->faces[0]->enabled = false;
	img->faces[1]->enabled = false;
	img->gun[1]->enabled = false;
	img->gun[2]->enabled = false;
	img->gun[3]->enabled = false;
	img->gun[4]->enabled = false;
}

int	init_images(t_game *game, t_parse parse)
{
	game->minimap.img = mlx_new_image(game->mlx,
			SCREEN_WIDTH / 6, SCREEN_HEIGHT / 4);
	mlx_image_to_window(game->mlx, game->minimap.img,
		SCREEN_WIDTH / 40, (double)SCREEN_HEIGHT / 26.666667f);
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
