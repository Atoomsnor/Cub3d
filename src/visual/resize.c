/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resize.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhendrik <nhendrik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 02:19:41 by nhendrik          #+#    #+#             */
/*   Updated: 2025/11/06 16:48:14 by nhendrik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//static int	resize_enabled(t_game *game, mlx_image_t **img,
//		char *path, int z)
//{
//	mlx_delete_image(game->mlx, *img);
//	*img = png_to_image(path, game->mlx);
//	if (!img)
//		return (-1);
//	if(mlx_resize_image(*img, game->width, game->height) == false)
//		return (-1);
//	if (mlx_image_to_window(game->mlx, *img, 0, 0) == -1)
//		return (-1);
//	(*img)->instances[0].z = z;
//	return (0);
//}

static int	resize_image(t_game *game, mlx_image_t **img,
		char *path, bool enabled)
{
	int	z;

	z = (*img)->instances[0].z;
	mlx_delete_image(game->mlx, *img);
	*img = png_to_image(path, game->mlx);
	if (!img)
		return (-1);
	if(mlx_resize_image(*img, game->width, game->height) == false)
		return (-1);
	if(mlx_image_to_window(game->mlx, *img, 0, 0) == -1)
		return (-1);
	(*img)->enabled = enabled;
	(*img)->instances[0].z = z;
	return (0);
}

static int	resize_guns(t_game *game)
{ 
	if (resize_image(game, &game->img.gun[0], "./img/gun1.png", true) == -1)
		return (-1);
	if (resize_image(game, &game->img.gun[1], "./img/gun2.png", false) == -1)
		return (-1);
	if (resize_image(game, &game->img.gun[2], "./img/gun3.png", false) == -1)
		return (-1);
	if (resize_image(game, &game->img.gun[3], "./img/gun4.png", false) == -1)
		return (-1);
	if (resize_image(game, &game->img.gun[4], "./img/gun5.png", false) == -1)
		return (-1);
	return (0);
}

void	resize_hook(int32_t width, int32_t height, void *ptr)
{
	t_game		*game;

	game = ptr;
	game->width = width;
	game->height = height;
	if (resize_image(game, &game->img.hud, "./img/Hud.png", true) == -1)
		return ;
	if (resize_guns(game) == -1)
		return ;
	if (resize_image(game, &game->img.faces[0], "./img/face_left.png", false) == -1)
		return ;
	if (resize_image(game, &game->img.faces[1], "./img/face_right.png", false) == -1)
		return ;
	raycast(game);
}
