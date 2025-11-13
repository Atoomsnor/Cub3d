/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roversch <roversch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 15:04:45 by nhendrik          #+#    #+#             */
/*   Updated: 2025/11/13 13:29:56 by roversch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	doors(t_game *game)
{
	t_ray		ray;
	t_vector	camera;

	ray.x = game->width / 2;
	camera.x = 2 * ray.x / (double)game->width - 1;
	ray.dir.x = game->player.dir.x + game->player.plane.x * camera.x;
	ray.dir.y = game->player.dir.y + game->player.plane.y * camera.x;
	ray = cast_ray(ray, game->player, game, false);
	if (ray.hit_dist <= 0 || ray.hit_dist > 2
		|| game->world_map[(int)ray.map.y][(int)ray.map.x] != 3)
		return ;
	game->world_map[(int)ray.map.y][(int)ray.map.x] = 0;
}
