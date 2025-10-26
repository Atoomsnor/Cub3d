/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhendrik <nhendrik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 12:46:52 by roversch          #+#    #+#             */
/*   Updated: 2025/10/26 02:02:30 by nhendrik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h>

bool	check_empty(char **map)
{
	if (map[0])
		return (true);
	return (false);
}

bool	is_map_character(char c)
{
	if (c == 'N' || c == 'E' || c == 'W' || c == 'S' || c == '0')
		return (true);
	return (false);
}
bool	check_characters(char **map)
{
	bool in_map;
	int	player_count;
	int	y;
	int	x;

	y = 0;
	player_count = 0;
	while (map[y])
	{
		in_map = false;
		x = 0;
		while (map[y][x])
		{
			printf("%c", map[y][x]);
			if (map[y][x] == '1')
				in_map = true;
			if (!in_map && is_map_character(map[y][x]))
					return (false);
			if (map[y][x] == 'N' || map[y][x] == 'E' || map[y][x] == 'W' || map[y][x] == 'S')
				player_count++;
			x++;
		}
		y++;
	}
	printf("\n");
	if (player_count != 1)
		return (false);
	return (true);
}

bool	check_map(t_parse *parse, char **map)
{
	if (!check_empty(map))
		return (printf("Error\nMap is empty\n"), true);
	if (!check_characters(map))
		return (printf("Error\nMap has invalid characters\n"), true);
	(void)parse;
	// if (!check_walls(parse->map))
		// return (printf("Error\nMap is not surrounded by walls\n"), 1);
	return (0);
}
