/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhendrik <nhendrik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 12:46:52 by roversch          #+#    #+#             */
/*   Updated: 2025/11/13 00:31:33 by nhendrik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"
#include <stdio.h>

static int	is_map_character(char c)
{
	if (c == 'N' || c == 'E' || c == 'W'
		|| c == 'S' || c == '0' || c == 'D')
		return (1);
	return (0);
}

static void	set_pos_and_dir(t_parse *parse, int y, int x, char dir)
{
	parse->pos.x = x;
	parse->pos.y = y;
	if (dir == 'N')
		parse->dir.y = -1;
	else if (dir == 'E')
		parse->dir.x = 1;
	else if (dir == 'S')
		parse->dir.y = 1;
	else if (dir == 'W')
		parse->dir.x = -1;
}

static int	check_characters(char **map, t_parse *parse)
{
	int		player_count;
	int		y;
	int		x;

	y = -1;
	player_count = 0;
	while (map[++y])
	{
		x = -1;
		while (map[y][++x])
		{
			if (!is_map_character(map[y][x])
				&& !ft_iswhitespace(map[y][x]) && map[y][x] != '1')
				return (-1);
			if (map[y][x] == 'N' || map[y][x] == 'E'
					|| map[y][x] == 'W' || map[y][x] == 'S')
			{
				set_pos_and_dir(parse, y, x, map[y][x]);
				player_count++;
			}
		}
	}
	if (player_count != 1)
		return (-1);
	return (0);
}

int	check_map(t_parse *parse, char **map)
{
	if (check_characters(map, parse) == -1)
		return (print_error("Error\nMap has invalid characters\n"));
	if (flood_and_walls(map, parse) == -1)
		return (print_error("Error\nMap is not surrounded by walls\n"));
	return (0);
}
