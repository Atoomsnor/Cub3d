/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roversch <roversch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 13:29:00 by nhendrik          #+#    #+#             */
/*   Updated: 2025/10/09 16:08:44 by roversch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>
#include <stdio.h>

// int get_color(mlx_image_t* image, uint32_t x, uint32_t y)
// {
// 	uint8_t		*pixelstart = &image->pixels[(y * image->width + x) * 4];
// 	return (((pixelstart[0] << 24) | (pixelstart[1] << 16) | (pixelstart[2] << 8) | pixelstart[3]));
// }

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
		if (game->world_map[(int)ray.map.y][(int)ray.map.x].content > 0)
			ray.hit = true;
	}
	// if (!side)
	// 	ray.hit_dist = (ray.map.x - player->pos.x + (1 - dir.x) / 2) / ray.dir.x;
	// else
	// 	ray.hit_dist = (ray.map.y - player->pos.y + (1 - dir.y) / 2) / ray.dir.y;
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
	// printf("%f\n", ray.tex.x);
	if (ray.hit_dist > 0)
	{
		//printf("diff: %f\n", ray.hit_dist);
		int height = (int)(SCREEN_HEIGHT / ray.hit_dist);
		int y_start = SCREEN_HEIGHT / 2 + -height / 2;
		if (y_start < 0)
			y_start = 0;
		int y_end = SCREEN_HEIGHT / 2 + height / 2;
		if (y_end >= SCREEN_HEIGHT)
			y_end = SCREEN_HEIGHT - 1;
		double step = 1.0 * SCALE / height;
		double texPos = (y_start - SCREEN_HEIGHT / 2 + height / 2) * step;
		for (int y = y_start; y < y_end; y++)
		{
			int tex_y = (int)texPos & (SCALE - 1);
			texPos += step;
			uint32_t color = get_color(game->img_wall, ray.tex.x, tex_y);
			// if (side == 1) color = (color >> 1) & 8355711;
			put_pixel(game->screen_buffer, x, y, color);
		}
		// printf("x: %i, start: %i end: %i\n", x, y_start, y_end);
		// int color = 6969;
		// if (side == 1)
		// 	color = 696969;
		// static int delta_y = 0;
		// if (!delta_y)
		// 	delta_y = y_end - y_start;
		// else
		// 	delta_y--;
		// printf("delta y: %i\n", delta_y);
		// for (int i = y_end; i > y_start; i--)
		// 	put_pixel(game->screen_buffer, x, i, get_color(game->img_wall, delta_y, i));	
		mlx_image_to_window(game->mlx, game->screen_buffer, 0, 0);
	}
}

void move_map(t_game *game, t_map *map)
{
	if (map->ray.hit_dist > 0)
	{
		printf("diff: %f\n", map->ray.hit_dist);
		int width = (int)(SCALE / map->ray.hit_dist);
		int height = (int)(SCALE / map->ray.hit_dist);
		int x = map->ray.wall.x;
		printf("%i\n", x);
		int y = SCREEN_HEIGHT / 2 - height / 2;
		double step = 1.0 * SCALE / y;
		double texPos = (y - SCREEN_HEIGHT / 2 + height / 2) * step;
		printf("%f %f\n", step, texPos);
		// if (y + height > SCREEN_HEIGHT)
		// 	y *= 2;
		map->img = mlx_texture_to_image(game->mlx, game->textures->wall_texture);
		mlx_resize_image(map->img, width, height);
		mlx_image_to_window(game->mlx, map->img, texPos, y);
	}
}


// struct map;
// map -> int var;
// map -> int x  int y
// map -> bool hit
// map -> double hit_dist
// map->hist_dist > ray.hist_dist: map->hist_dist = ray.hit_dist;

// void reset_map(t_map **map, int len)
// {
// 	int	i;
// 	int	j;

// 	i = 0;
// 	while (map[i])
// 	{
// 		j = 0;
// 		while (j < len)
// 		{
// 			map[i][j].hit = false;
// 			j++;
// 		}
// 		i++;
// 	}
// }

//void move_map(t_game *game, t_map *map)
//{
//	if (map->ray.hit_dist > 0)
//	{
//		printf("diff: %f\n", map->ray.hit_dist);
//		int width = (int)(SCALE / map->ray.hit_dist);
//		int height = (int)(SCALE / map->ray.hit_dist);
//		int x = map->ray.wall.x;
//		printf("%i\n", x);
//		int y = SCREEN_HEIGHT / 2 - height / 2;
//		double step = 1.0 * SCALE / y;
//		double texPos = (y - SCREEN_HEIGHT / 2 + height / 2) * step;
//		printf("%f %f\n", step, texPos);
//		// if (y + height > SCREEN_HEIGHT)
//		// 	y *= 2;
//		map->img = mlx_texture_to_image(game->mlx, game->textures->wall_texture);
//		mlx_resize_image(map->img, width, height);
//		mlx_image_to_window(game->mlx, 28 daysmap->img, texPos, y);
//	}
//}

//void locate_hits(t_map **map, int len, t_game *game)
//{
//	int	i;
//	int	j;

//	i = 0;
//	while (map[i])
//	{
//		j = 0;
//		while (j < len)
//		{
//			if (map[i][j].img)
//				mlx_delete_image(game->mlx, map[i][j].img);
//			if (map[i][j].hit == true)
//				move_map(game, &(map[i][j]));
//			j++;
//		}
//		i++;
//	}
//}

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
	game->screen_buffer = mlx_new_image(game->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
    ft_memset(game->screen_buffer->pixels, 0, game->screen_buffer->width * game->screen_buffer->height * sizeof(int32_t));
	while (x < SCREEN_WIDTH)
	{
		camera.x = 2 * x / (double)SCREEN_WIDTH - 1;
		ray.dir.x = player->dir.x + player->plane.x * camera.x;
		ray.dir.y = player->dir.y + player->plane.y * camera.x;
		ray.hit = false;
		ray.wall.x = x;
		cast_ray(ray, player, game, x);
		x++;
	}
	mlx_image_to_window(game->mlx, game->screen_buffer, 0, 0);
}