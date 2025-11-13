/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhendrik <nhendrik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 13:29:00 by nhendrik          #+#    #+#             */
/*   Updated: 2025/11/13 15:34:53 by nhendrik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"
#include <math.h>

static void	dir_and_side_dist(t_ray *ray, t_vector *dir, t_player player)
{
	if (ray->dir.x < 0)
	{
		dir->x = -1;
		ray->side_dist.x = (player.pos.x - ray->map.x) * ray->delta_dist.x;
	}
	else
	{
		dir->x = 1;
		ray->side_dist.x = (ray->map.x + 1 - player.pos.x) * ray->delta_dist.x;
	}
	if (ray->dir.y < 0)
	{
		dir->y = -1;
		ray->side_dist.y = (player.pos.y - ray->map.y) * ray->delta_dist.y;
	}
	else
	{
		dir->y = 1;
		ray->side_dist.y = (ray->map.y + 1 - player.pos.y) * ray->delta_dist.y;
	}
}

static void	dda_loop(t_ray *ray, t_game *game, t_vector dir)
{
	while (1)
	{
		if (ray->side_dist.x < ray->side_dist.y)
		{
			ray->side_dist.x += ray->delta_dist.x;
			ray->map.x += dir.x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist.y += ray->delta_dist.y;
			ray->map.y += dir.y;
			ray->side = 1;
		}
		if (game->world_map[(int)ray->map.y][(int)ray->map.x] > 0)
			break ;
	}
}

static void	side_based_calculations(t_ray *ray, t_vector pos)
{
	if (!ray->side)
	{
		ray->hit_dist = ray->side_dist.x - ray->delta_dist.x;
		ray->wall.x = pos.y + ray->hit_dist * ray->dir.y;
	}
	else
	{
		ray->hit_dist = ray->side_dist.y - ray->delta_dist.y;
		ray->wall.x = pos.x + ray->hit_dist * ray->dir.x;
	}
	ray->wall.x -= floor((ray->wall.x));
	ray->tex.x = ray->wall.x * SCALE;
	if (ray->side == 0 && ray->dir.x > 0)
		ray->tex.x = SCALE - ray->tex.x - 1;
	if (ray->side == 1 && ray->dir.y < 0)
		ray->tex.x = SCALE - ray->tex.x - 1;
}

t_ray	cast_ray(t_ray ray, t_player player, t_game *game, bool to_image)
{
	t_vector	dir;

	ray.map.x = (int)player.pos.x;
	ray.map.y = (int)player.pos.y;
	ray.delta_dist.x = fabs(1 / ray.dir.x);
	ray.delta_dist.y = fabs(1 / ray.dir.y);
	dir_and_side_dist(&ray, &dir, player);
	dda_loop(&ray, game, dir);
	side_based_calculations(&ray, player.pos);
	if (ray.hit_dist > 0 && to_image)
		ray_to_image(ray, game);
	return (ray);
}

int	raycast(t_game *game)
{
	t_player	player;
	t_vector	camera;
	t_ray		ray;

	player = game->player;
	ray.x = -1;
	if (game->screen_buffer)
		mlx_delete_image(game->mlx, game->screen_buffer);
	game->screen_buffer = mlx_new_image(game->mlx, game->width, game->height);
	if (!game->screen_buffer)
		return (print_error("Error\nFailure creating image\n"));
	ft_memset(game->screen_buffer->pixels, 0,
		game->width * game->height * sizeof(int32_t));
	while (++ray.x < game->width)
	{
		camera.x = 2 * ray.x / (double)game->width - 1;
		ray.dir.x = player.dir.x + player.plane.x * camera.x;
		ray.dir.y = player.dir.y + player.plane.y * camera.x;
		ray.hit = false;
		cast_ray(ray, player, game, true);
	}
	if (mlx_image_to_window(game->mlx, game->screen_buffer, 0, 0) == -1)
		return (print_error("Error\nImage to window failure\n"));
	game->screen_buffer->instances[0].z = 0;
	return (0);
}
