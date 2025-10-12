/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhendrik <nhendrik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 00:25:32 by nhendrik          #+#    #+#             */
/*   Updated: 2025/10/13 01:05:35 by nhendrik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <sys/time.h>
#include <stdio.h>

size_t	get_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		printf("gettimeofday Error\n");
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

size_t	get_fps(t_game *game)
{
	size_t time;
	double frame_time;

	time = get_time() - game->fps->start_time;
	frame_time = (time - game->fps->last_time) / 1000.0;
	game->fps->last_time= time;
	printf("%f\n", 1.0 / frame_time);
	//if (time - game->fps->last_time > 1000)
	//{
	//	game->fps->last_time = time;
	//	printf("%zu: %zu\n", time / 1000, game->fps->frames);
	//	game->fps->frames = 0;
	//}
	//else
	//	game->fps->frames++;
	
	return (1.0 / frame_time);
}