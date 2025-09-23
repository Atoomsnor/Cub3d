/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhendrik <nhendrik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 13:29:00 by nhendrik          #+#    #+#             */
/*   Updated: 2025/09/23 18:35:58 by nhendrik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>
#include <stdio.h>

void move_map(t_ray ray, mlx_image_t *img)
{
	double diff = ray.hit_dist;

	printf("%f\n", diff);
	if (diff > 0)
	{
		int width = 900 / diff;
		int height = 600 / diff;
		img->instances->x = 900 / 2 - width / 2;
		img->instances->y = 600 / 2 - height / 2;
		mlx_resize_image(img, width, height);
	}
}

void cast_ray(t_ray ray, t_player *player, mlx_image_t *img)
{
	t_vector	dir;
	int			side;
	int			worldMap[10][10] =
	{
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 1, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
	};
	ray.map.x = player->pos.x;
	ray.map.y = player->pos.y;
	// distance per step
	ray.delta_dist.x = fabs(1 / ray.dir.x);
	ray.delta_dist.y = fabs(1 / ray.dir.y);
	//
	if (ray.dir.x < 0)
	{
		dir.x = -1;
		ray.side_dist.x = (player->pos.x - ray.map.x) * ray.delta_dist.x;
	}
	else
	{
		dir.x = 1;
		ray.side_dist.x = (ray.map.x + 1 - player->pos.x) * ray.delta_dist.x;
	}
	if (ray.dir.y < 0)
	{
		dir.y = -1;
		ray.side_dist.y = (player->pos.y - ray.map.y) * ray.delta_dist.y;
	}
	else
	{
		dir.y = 1;
		ray.side_dist.y = (ray.map.y + 1 - player->pos.y) * ray.delta_dist.y;
	}
	while (!ray.hit)
	{
		if (ray.side_dist.x < ray.side_dist.y)
		{
			ray.side_dist.x += ray.delta_dist.x;
			ray.map.x += dir.x;
			side = 0;
		}
		else
		{
			ray.side_dist.y += ray.delta_dist.y;
			ray.map.y += dir.y;
			side = 1;
		}
		if (worldMap[(int)ray.map.y][(int)ray.map.x] > 0)
			ray.hit = true;
	}
	if (!side)
		ray.hit_dist = (ray.map.x - player->pos.x + (1 - dir.x) / 2) / ray.dir.x;
	else
		ray.hit_dist = (ray.map.y - player->pos.y + (1 - dir.y) / 2) / ray.dir.y;
	move_map(ray, img);
}

void raycast(t_game *game)
{
	t_player	*player;
	int			x;
	t_vector	camera;
	t_ray		ray;

	player = game->player;
	x = 0;
	while (x < game->width)
	{
		camera.x = 2 * x / (double)game->width - 1;
		ray.dir.x = player->dir.x * camera.x;
		ray.dir.y = player->dir.y + 0.66 * camera.x;
		ray.hit = false;
		cast_ray(ray, player, game->img_wall);
		x++;
	}
}