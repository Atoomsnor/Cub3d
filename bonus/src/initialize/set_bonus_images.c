/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_bonus_images.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhendrik <nhendrik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 11:13:23 by nhendrik          #+#    #+#             */
/*   Updated: 2025/11/17 11:16:02 by nhendrik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	png_to_elements(t_img *img, mlx_t *mlx)
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
	img->door = png_to_image("./img/door.png", mlx);
	if (!img->door)
		return (-1);
	return (0);
}

void	disable_instances(t_img *img)
{
	img->faces[0]->enabled = false;
	img->faces[1]->enabled = false;
	img->gun[1]->enabled = false;
	img->gun[2]->enabled = false;
	img->gun[3]->enabled = false;
	img->gun[4]->enabled = false;
}
