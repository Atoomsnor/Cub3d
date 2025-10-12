/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhendrik <nhendrik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 13:29:00 by nhendrik          #+#    #+#             */
/*   Updated: 2025/10/13 00:25:19 by nhendrik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>
#include <stdio.h>

int get_color(mlx_image_t* image, uint32_t x, uint32_t y)
{
	uint8_t		*pixelstart = &image->pixels[(y * SCALE + x) * 4];
	return ((pixelstart[0] | (pixelstart[1] << 8) | (pixelstart[2] << 16) | (pixelstart[3] << 24)));
}

void put_pixel(mlx_image_t* image, uint32_t x, uint32_t y, uint32_t color)
{
	uint8_t* pixelstart;

	if (!image || x >= image->width || y >= image->height)
		return ;
	pixelstart = &image->pixels[(y * image->width + x) * 4];
	*(pixelstart++) = (uint8_t)(color & 0xFF);
	*(pixelstart++) = (uint8_t)(color >> 8);
	*(pixelstart++) = (uint8_t)(color >> 16);
	*(pixelstart++) = (uint8_t)(color >> 24);
}

void cast_ray(t_ray ray, t_player *player, t_game *game, int x)
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
		if (game->world_map[(int)ray.map.y][(int)ray.map.x] > 0)
			ray.hit = true;
	}
	if (!side)
		ray.hit_dist = ray.side_dist.x - ray.delta_dist.x;
	else
		ray.hit_dist = ray.side_dist.y - ray.delta_dist.y;
	if (!side)
		ray.wall.x = player->pos.y + ray.hit_dist * ray.dir.y;
	else
		ray.wall.x = player->pos.x + ray.hit_dist * ray.dir.x;
	ray.wall.x -= floor((ray.wall.x));
	ray.tex.x = ray.wall.x * SCALE;
	if (side == 0 && ray.dir.x > 0)
		ray.tex.x = SCALE - ray.tex.x - 1;
	if (side == 1 && ray.dir.y < 0)
		ray.tex.x = SCALE - ray.tex.x - 1;
	if (ray.hit_dist > 0)
	{
		int height = (int)(game->height / ray.hit_dist);
		int y_start = game->height / 2 + -height / 2;
		if (y_start < 0)
			y_start = 0;
		int y_end = game->height / 2 + height / 2;
		if (y_end >= game->height)
			y_end = game->height - 1;
		double step = 1.0 * SCALE / height;
		double texPos = (y_start - game->height / 2 + height / 2) * step;
		for (int y = y_start; y < y_end; y++)
		{
			int tex_y = (int)texPos & (SCALE - 1);
			texPos += step;
			mlx_image_t *img;
			if (!side && ray.dir.x > 0)
				img = game->img->EA;
			else if (!side)
				img = game->img->WE;
			else if (ray.dir.y > 0)
				img = game->img->SO;
			else
				img = game->img->NO;
			put_pixel(game->screen_buffer, x, y, get_color(img, ray.tex.x, tex_y));
		}
		mlx_image_to_window(game->mlx, game->screen_buffer, 0, 0);
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
	if (game->screen_buffer)
		mlx_delete_image(game->mlx, game->screen_buffer);
	game->screen_buffer = mlx_new_image(game->mlx, game->width, game->height);
    ft_memset(game->screen_buffer->pixels, 0, game->screen_buffer->width * game->screen_buffer->height * sizeof(int32_t));
	while (x < game->width)
	{
		camera.x = 2 * x / (double)game->width - 1;
		ray.dir.x = player->dir.x + player->plane.x * camera.x;
		ray.dir.y = player->dir.y + player->plane.y * camera.x;
		ray.hit = false;
		cast_ray(ray, player, game, x);
		x++;
	}
	mlx_image_to_window(game->mlx, game->screen_buffer, 0, 0);
	game->screen_buffer->instances[0].z = 0;
}