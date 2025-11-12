/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhendrik <nhendrik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 15:04:45 by nhendrik          #+#    #+#             */
/*   Updated: 2025/11/13 00:18:02 by nhendrik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

//void door_anime(t_game *game, t_ray ray, bool start_anim)
//{
//	size_t	time;
	
//	time = get_time() - game->fps.start_time;
//	if (!game->door_anime.in_anime && start_anim && ray.hit_dist > 0 && ray.hit_dist < 2
//		&& game->world_map[(int)ray.map.y][(int)ray.map.x] == 3)
//	{
//		game->door_anime.in_anime = true;
//		game->door_anime.anime_start_time = time;
//	}
//	if (game->door_anime.in_anime && time - game->door_anime.anime_start_time < 50)
//		game->img.door = game->img.doors[0];
//	else if (game->door_anime.in_anime && time - game->door_anime.anime_start_time < 100)
//		game->img.door = game->img.doors[1];
//	else if (game->door_anime.in_anime && time - game->door_anime.anime_start_time < 150)
//		game->img.door = game->img.doors[2];
//	else if (game->door_anime.in_anime && time - game->door_anime.anime_start_time < 200)
//		game->img.door = game->img.doors[3];
//	else if (game->door_anime.in_anime && time - game->door_anime.anime_start_time < 250)
//		game->img.door = game->img.doors[4];
//	else if (game->door_anime.in_anime && time - game->door_anime.anime_start_time < 300)
//		game->img.door = game->img.doors[5];
//	else if (game->door_anime.in_anime && time - game->door_anime.anime_start_time < 350)
//		game->img.door = game->img.doors[6];
//	else if (game->door_anime.in_anime && time - game->door_anime.anime_start_time < 400)
//		game->img.door = game->img.doors[7];
//	else if (game->door_anime.in_anime && time - game->door_anime.anime_start_time < 450)
//		game->img.door = game->img.doors[8];
//	else if (game->door_anime.in_anime && time - game->door_anime.anime_start_time < 500)
//		game->img.door = game->img.doors[9];
//	else if (game->door_anime.in_anime && time - game->door_anime.anime_start_time < 550)
//		game->img.door = game->img.doors[10];
//	else if (game->door_anime.in_anime && time - game->door_anime.anime_start_time < 600)
//		game->img.door = game->img.doors[11];
//	else if (game->door_anime.in_anime && time - game->door_anime.anime_start_time < 650)
//		game->img.door = game->img.doors[12];
//	else if (game->door_anime.in_anime && time - game->door_anime.anime_start_time < 700)
//		game->img.door = game->img.doors[13];
//	else if (game->door_anime.in_anime && time - game->door_anime.anime_start_time < 750)
//		game->img.door = game->img.doors[14];
//	else if (game->door_anime.in_anime && time - game->door_anime.anime_start_time < 800)
//		game->img.door = game->img.doors[15];
//	else if (game->door_anime.in_anime && time - game->door_anime.anime_start_time < 850)
//		game->img.door = game->img.doors[16];
//	else if (game->door_anime.in_anime && time - game->door_anime.anime_start_time < 900)
//		game->img.door = game->img.doors[17];
//	else if (game->door_anime.in_anime && time - game->door_anime.anime_start_time < 950)
//		game->img.door = game->img.doors[18];
//	else if (game->door_anime.in_anime && time - game->door_anime.anime_start_time < 1000)
//		game->img.door = game->img.doors[19];
//	else if (game->door_anime.in_anime)
//	{
//		game->img.door = game->img.doors[0];
//		game->world_map[(int)ray.map.y][(int)ray.map.x] = 0;	
//		game->door_anime.in_anime = false;
//	}
//}

void	doors(t_game *game, bool start_anim)
{
	t_ray		ray;
	t_vector	camera;

	ray.x = game->width / 2;
	camera.x = 2 * ray.x / (double)game->width - 1;
	ray.dir.x = game->player.dir.x + game->player.plane.x * camera.x;
	ray.dir.y = game->player.dir.y + game->player.plane.y * camera.x;
	ray = cast_ray(ray, game->player, game, false);
	if (!start_anim || ray.hit_dist <= 0 || ray.hit_dist > 2
		|| game->world_map[(int)ray.map.y][(int)ray.map.x] != 3)
		return ;
	
	//door_anime(game, ray, start_anim);
	game->world_map[(int)ray.map.y][(int)ray.map.x] = 0;
}