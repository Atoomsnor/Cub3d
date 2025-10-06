/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhendrik <nhendrik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 13:29:00 by nhendrik          #+#    #+#             */
/*   Updated: 2025/10/06 14:17:44 by nhendrik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>
#include <stdio.h>

void move_map(t_ray ray, t_game *game)
{
	double diff = ray.hit_dist;

	printf("diff: %f\n", diff);
	if (diff > 0)
	{
		int width = 600 / diff;
		int height = 600 / diff;
		double x = 900 / 2 - width / 2;
		double y = 600 / 2 - height / 2;
		mlx_delete_image(game->mlx, game->img_wall);
		game->img_wall = mlx_texture_to_image(game->mlx, game->wall_texture);
		mlx_resize_image(game->img_wall, width, height);
		mlx_image_to_window(game->mlx, game->img_wall, x, y);
	}
}

void cast_ray(t_ray ray, t_player *player, t_game *game)
{
	t_vector	dir;
	int			side;

	ray.map.x = player->pos.x;
	ray.map.y = player->pos.y;
	// distance per step
	ray.delta_dist.x = fabs(1 / ray.dir.x);
	ray.delta_dist.y = fabs(1 / ray.dir.y);
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
		if (game->world_map[(int)ray.map.y][(int)ray.map.x] > 0)
			ray.hit = true;
	}
	if (!side)
		ray.hit_dist = (ray.map.x - player->pos.x + (1 - dir.x) / 2) / ray.dir.x;
	else
		ray.hit_dist = (ray.map.y - player->pos.y + (1 - dir.y) / 2) / ray.dir.y;
	printf("raydirx: %f\n", ray.dir.x);
	move_map(ray, game);
}

// struct map;
// map -> int x  int y
// map -> bool hit
// map -> double hit_dist
// map->hist_dist > ray.hist_dist: map->hist_dist = ray.hit_dist;

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
		cast_ray(ray, player, game);
		x++;
	}
}