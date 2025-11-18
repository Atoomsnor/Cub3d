/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhendrik <nhendrik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 15:04:45 by nhendrik          #+#    #+#             */
/*   Updated: 2025/11/18 15:54:54 by nhendrik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	doors(t_game *game)
{
	t_ray			ray;
	t_vector		camera;
	static size_t	timer = 0;

	ray.x = game->width / 2;
	camera.x = 2 * ray.x / (double)game->width - 1;
	ray.dir.x = game->player.dir.x + game->player.plane.x * camera.x;
	ray.dir.y = game->player.dir.y + game->player.plane.y * camera.x;
	ray = cast_ray(ray, game->player, game, false);
	if (ray.hit_dist <= 0 || ray.hit_dist > 2)
		return ;
	if (get_time() - timer < 1000)
		return ;
	if (game->world_map[(int)ray.map.y][(int)ray.map.x] == 3)
	{
		game->world_map[(int)ray.map.y][(int)ray.map.x] = -1;
		timer = get_time();
	}
	else if (game->world_map[(int)ray.map.y][(int)ray.map.x] == -1)
	{
		game->world_map[(int)ray.map.y][(int)ray.map.x] = 3;
		timer = get_time();
	}
}

void	dda_door(t_ray *ray, t_game *game, t_vector dir)
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
		if (game->world_map[(int)ray->map.y][(int)ray->map.x])
			break ;
	}
}
