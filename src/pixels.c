/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixels.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhendrik <nhendrik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 02:13:11 by nhendrik          #+#    #+#             */
/*   Updated: 2025/10/26 02:16:09 by nhendrik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_color(mlx_image_t *image, uint32_t x, uint32_t y)
{
	uint8_t	*pixelstart;

	pixelstart = &image->pixels[(y * SCALE + x) * 4];
	return ((pixelstart[0] | (pixelstart[1] << 8)
			| (pixelstart[2] << 16) | (pixelstart[3] << 24)));
}

void	put_pixel(mlx_image_t *image, uint32_t x, uint32_t y, uint32_t color)
{
	uint8_t	*pixelstart;

	if (!image || x >= image->width || y >= image->height)
		return ;
	pixelstart = &image->pixels[(y * image->width + x) * 4];
	*(pixelstart++) = (uint8_t)(color & 0xFF);
	*(pixelstart++) = (uint8_t)(color >> 8);
	*(pixelstart++) = (uint8_t)(color >> 16);
	*(pixelstart++) = (uint8_t)(color >> 24);
}
