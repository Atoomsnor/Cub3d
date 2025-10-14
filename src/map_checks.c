/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhendrik <nhendrik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 12:46:52 by roversch          #+#    #+#             */
/*   Updated: 2025/10/14 17:56:51 by nhendrik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h>

// int	check_empty(char **map)
// {
// 	if (map[0])
// 		return (1);
// 	return (0);
// }

// int	check_characters(char **map)
// {
// 	int	y;
// 	int	x;

// 	y = 0;
// 	while (map[y])
// 	{
// 		x = 0;
// 		while (map[y][x] != '\0')
// 		{
			
// 			x++;
// 		}
// 		y++;
// 	}
// }

// int	check_map(t_game *game)
// {
// 	if (!check_empty(game->world_map))
// 		return (printf("Error\nMap is empty\n"), 1);
// 	if (!check_characters(game->world_map))
// 		return (printf("Error\nMap has invalid characters\n"), 1);
// 	if (!check_walls(game->world_map))
// 		return (printf("Error\nMap is not surrounded by walls\n"), 1);
// 	return (0);
// }
