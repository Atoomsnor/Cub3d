/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhendrik <nhendrik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 13:29:00 by nhendrik          #+#    #+#             */
/*   Updated: 2025/10/07 17:14:55 by nhendrik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>
#include <stdio.h>

void cast_ray(t_ray ray, t_player *player, t_game *game)
{
	t_vector	dir;
	int			side;

	ray.map.x = (int)player->pos.x;
	ray.map.y = (int)player->pos.y;
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
		if (game->world_map[(int)ray.map.y][(int)ray.map.x].content > 0)
			ray.hit = true;
	}
	// double abc;
	// if (!side)
	// 	abc = (ray.map.x - player->pos.x + (1 - dir.x) / 2) / ray.dir.x;
	// else
	// 	abc = (ray.map.y - player->pos.y + (1 - dir.y) / 2) / ray.dir.y;
	if (!side)
		ray.hit_dist = ray.side_dist.x - ray.delta_dist.x;
	else
		ray.hit_dist = ray.side_dist.y - ray.delta_dist.y;

	double wallX;
	if (!side)
		wallX = player->pos.y + ray.hit_dist * ray.dir.y;
	else
		wallX = player->pos.x + ray.hit_dist * ray.dir.x;

		
	wallX -= floor((wallX));
	int texX = (int)wallX * 600;
	if (side == 0 && ray.dir.x > 0)
		texX = 600 - texX - 1;
	if (side == 1 && ray.dir.y < 0)
		texX = 600 - texX - 1;
	// printf("ray hit distance: %f = (%f - %f + (1 - %f) / 2) / %f\n", ray.hit_dist, ray.map.x, player->pos.x, dir.x, ray.dir.x);
	if (!game->world_map[(int)ray.map.y][(int)ray.map.x].hit)
	{
		printf("X %f Y %f\n", ray.map.x, ray.map.y);
		game->world_map[(int)ray.map.y][(int)ray.map.x].ray = ray;
		game->world_map[(int)ray.map.y][(int)ray.map.x].hit = true;
	}
}

// struct map;
// map -> int var;
// map -> int x  int y
// map -> bool hit
// map -> double hit_dist
// map->hist_dist > ray.hist_dist: map->hist_dist = ray.hit_dist;

void reset_map(t_map **map, int len)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (j < len)
		{
			map[i][j].hit = false;
			j++;
		}
		i++;
	}
}

void move_map(t_game *game, t_map *map)
{
	double diff = map->ray.hit_dist;

	printf("diff: %f\n", diff);
	if (diff > 0)
	{
		double width = SCREEN_HEIGHT / diff;
		double height = SCREEN_HEIGHT / diff;
		double x = (map->ray.dir.x - 1) * 600 - (map->ray.dir.y - 1) * 600;
		printf("%f\n", x);
		double y = SCREEN_HEIGHT / 2 - height / 2;
		map->img = mlx_texture_to_image(game->mlx, game->textures->wall_texture);
		mlx_resize_image(map->img, width, height);
		mlx_image_to_window(game->mlx, map->img, x, y);
	}
}

void locate_hits(t_map **map, int len, t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (j < len)
		{
			if (map[i][j].img)
				mlx_delete_image(game->mlx, map[i][j].img);
			if (map[i][j].hit == true)
				move_map(game, &(map[i][j]));
			j++;
		}
		i++;
	}
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
		ray.dir.x = player->dir.x + player->plane.x * camera.x;
		ray.dir.y = player->dir.y + player->plane.y * camera.x;
		ray.hit = false;
		cast_ray(ray, player, game);
		x++;
	}
	locate_hits(game->world_map, 11, game);
	reset_map(game->world_map, 11);
}