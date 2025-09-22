/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roversch <roversch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 12:36:29 by roversch          #+#    #+#             */
/*   Updated: 2025/09/22 12:02:26 by roversch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h>
#include <math.h>

void testfunc(void *ptr)
{
	mlx_image_t *img;
	static int x = 5;
	static int y = 5;
	static int bounce = 0;

	img = (mlx_image_t *)ptr;
	img->instances[0].x += x;
	img->instances[0].y += y;
	if (img->instances[0].x >= 700 || img->instances[0].x <= 0)
	{
		x = -x;
		bounce++;
	}
	if (img->instances[0].y >= 400 || img->instances[0].y <= 0)
	{
		y = -y;
		bounce++;
	}
	if (bounce == 5)
		bounce = 0, img->instances[0].z++;
}

int	main(void)
{
	mlx_image_t *img;
	mlx_image_t *img2;
	mlx_t *mlx;

	mlx = mlx_init(900, 600, "CUB3D", false);
	img = mlx_new_image(mlx, 200, 200);
	ft_memset(img->pixels, 255, img->width * img->height * sizeof(int32_t));
	mlx_image_to_window(mlx, img, 0, 0);
	img2 = mlx_new_image(mlx, 200, 200);
	ft_memset(img2->pixels, 200, img2->width * img2->height * sizeof(int32_t));
	mlx_image_to_window(mlx, img2, 350, 200);
	mlx_loop_hook(mlx, testfunc, img);
	mlx_loop(mlx);
}	