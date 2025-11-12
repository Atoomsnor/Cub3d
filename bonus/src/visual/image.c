/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhendrik <nhendrik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 12:32:44 by roversch          #+#    #+#             */
/*   Updated: 2025/11/13 00:28:03 by nhendrik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"
#include <stdio.h>

mlx_image_t	*png_to_image(const char *path, mlx_t *mlx)
{
	mlx_texture_t	*texture;
	mlx_image_t		*ret;

	texture = mlx_load_png(path);
	if (!texture)
		return (print_error("Error\nFailed to load image\n"), NULL);
	ret = mlx_texture_to_image(mlx, texture);
	mlx_delete_texture(texture);
	if (!ret)
		return (print_error("Error\nFailed to create image\n"), NULL);
	return (ret);
}
