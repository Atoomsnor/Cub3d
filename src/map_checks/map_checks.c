/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roversch <roversch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 12:46:52 by roversch          #+#    #+#             */
/*   Updated: 2025/11/06 14:14:51 by roversch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h>

static int	is_map_character(char c)
{
	if (c == 'N' || c == 'E' || c == 'W'
		|| c == 'S' || c == '0')
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
	bool	in_map;
	int		player_count;
	int		y;
	int		x;

	y = 0;
	player_count = 0;
	while (map[y])
	{
		in_map = false;
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == '1')
				in_map = true;
			if (!is_map_character(map[y][x])
				&& !ft_iswhitespace(map[y][x]) && map[y][x] != '1')
				return (-1);
			if (!in_map && is_map_character(map[y][x]))
				return (-1);
			if (map[y][x] == 'N' || map[y][x] == 'E'
					|| map[y][x] == 'W' || map[y][x] == 'S')
			{
				set_pos_and_dir(parse, y, x, map[y][x]);
				player_count++;
			}
			x++;
		}
		y++;
	}
	if (player_count != 1)
		return (-1);
	return (0);
}

// static int	set_pos_and_dir(t_parse *parse, int y, int x, char dir)
// {
// 	parse->pos.x = x;
// 	parse->pos.y = y;
// 	if (dir == 'N')
// 		parse->dir.y = -1;
// 	else if (dir == 'E')
// 		parse->dir.x = 1;
// 	else if (dir == 'S')
// 		parse->dir.y = 1;
// 	else if (dir == 'W')
// 		parse->dir.x = -1;
// 	return (1);
// }

// static int	is_valid_char(char c, bool in_map)
// {
// 	if (!is_map_character(c) && !ft_iswhitespace(c) && c != '1')
// 		return (-1);
// 	if (!in_map && is_map_character(c))
// 		return (-1);
// 	return (0);
// }

// static int	check_characters(char **map, t_parse *parse)
// {
// 	bool	in_map;
// 	int		player_count;
// 	int		y;
// 	int		x;

// 	player_count = 0;
// 	y = 0;
// 	while (map[y])
// 	{
// 		in_map = false;
// 		x = 0;
// 		while (map[y][x])
// 		{
// 			if (map[y][x] == '1')
// 				in_map = true;
// 			if (is_valid_char(map[y][x], in_map) == -1)
// 				return (-1);
// 			if (map[y][x] == 'N' || map[y][x] == 'E'
// 				|| map[y][x] == 'W' || map[y][x] == 'S')
// 				player_count += set_pos_and_dir(parse, y, x, map[y][x]);
// 			x++;
// 		}
// 		y++;
// 	}
// 	if (player_count != 1)
// 		return (-1);
// 	return (0);
// }

int	check_map(t_parse *parse, char **map)
{
	// if (!check_empty(map))
	// 	return (printf("Error\nMap is empty\n"), true);
	if (check_characters(map, parse) == -1)
		return (printf("Error\nMap has invalid characters\n"), -1);
	if (flood_and_walls(map, parse) == -1)
		return (printf("Error\nMap is not surrounded by walls\n"), -1);
	return (0);
}
