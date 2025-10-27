/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhendrik <nhendrik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 12:46:52 by roversch          #+#    #+#             */
/*   Updated: 2025/10/27 15:10:26 by nhendrik         ###   ########.fr       */
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

void set_pos_and_dir(t_parse *parse, int y, int x, char dir)
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

bool	check_characters(char **map, t_parse *parse)
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
			// printf("%c", map[y][x]);
			if (map[y][x] == '1')
				in_map = true;
			if (!in_map && is_map_character(map[y][x]))
					return (false);
			if (map[y][x] == 'N' || map[y][x] == 'E' || map[y][x] == 'W' || map[y][x] == 'S')
			{
				set_pos_and_dir(parse, y, x, map[y][x]);
				player_count++;
			}
			x++;
		}
		y++;
	}
	// printf("\n");
	if (player_count != 1)
		return (false);
	return (true);
}

int	find_widest_point(char **map)
{
	int	i;
	int	width;
	int	len;

	i = 0;
	width = 0;
	len = 0;
	while (map[i])
	{
		len = ft_strlen(map[i]);
		if (len > width)
			width = len;
		i++;
	}
	return (width);
}

char **fill_whitespace(char **flood_map, int width)
{
	int	i;
	int	j;

	i = 0;
	while (flood_map[i])
	{
		j = 0;
		while (j < width)
		{
			if (ft_iswhitespace(flood_map[i][j]) || !flood_map[i][j])
				flood_map[i][j] = 'X';
			j++;
		}
		i++;
	}
	return (flood_map);
}

void print_map(char **map, int width)
{
	for (int i = 0; map[i]; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (!map[i][j])
				printf("J");
			else
				printf("%c", map[i][j]);
		}
		printf("\n");
	}
}

bool flood(char ***map, int count, int i, int j)
{
	bool ret;

	ret = true;
	if (count > 500)
		return (true);
	if (count == 0)
		printf("starting pos %c %i %i\n", (*map)[i][j], i, j);
	(*map)[i][j] = 'F';
	if ((*map)[i + 1][j] == 'X' || (*map)[i - 1][j] == 'X' || (*map)[i][j + 1] == 'X' || (*map)[i][j - 1] == 'X')
		return (false);
	if ((*map)[i + 1][j] == '0')
		if (!flood(map, count + 1, i + 1, j))
			return (false);
	if ((*map)[i][j + 1] == '0')
		if (!flood(map, count + 1, i, j + 1))
			return (false);
	if ((*map)[i - 1][j] == '0')
		if (!flood(map, count + 1, i - 1, j))
			return (false);
	if ((*map)[i][j - 1] == '0')
		if (!flood(map, count + 1, i, j - 1))
			return (false);
	return (ret);
}

bool	flood_check(char **flood_map)
{
	int	y;
	int	x;

	y = 0;
	while (flood_map[y])
	{
		x = 0;
		while (flood_map[y][x])
		{
			if (!(flood_map[y][x] == '1' || flood_map[y][x] == 'F' ||flood_map[y][x] == 'X' || flood_map[y][x] == '\n'))
				return (false);
			x++;
		}
		y++;
	}
	return (true);
}

bool check_walls(char **map, t_parse *parse)
{
	char	**flood_map;
	int		height;
	int		width;
	int		i;

	height = 0;
	while (map[height])
		height++;
	flood_map = ft_calloc(height + 2, sizeof(char *));
	width = find_widest_point(map);
	i = 0;
	flood_map[0] = ft_calloc(width + 1, sizeof(char));
	while(i < height)
	{
		flood_map[i + 1] = ft_calloc(width + 1, sizeof(char));
		ft_strlcpy(&flood_map[i][1], map[i], width);
		i++;
	}
	flood_map[height] = ft_calloc(width + 1, sizeof(char));
	// print_map(flood_map, height, width);
	flood_map = fill_whitespace(flood_map, width + 1);
	print_map(flood_map, width + 1);
	printf ("\n\nNL\n\n");
	if (!flood(&flood_map, 0, (int)parse->pos.y, (int)parse->pos.x + 1))
		return (false);
	print_map(flood_map, width + 1);
	if (!flood_check(flood_map))
		return (false);
	return (true);
}

bool	check_map(t_parse *parse, char **map)
{
	if (!check_empty(map))
		return (printf("Error\nMap is empty\n"), true);
	if (!check_characters(map, parse))
		return (printf("Error\nMap has invalid characters\n"), true);
	if (!check_walls(map, parse))
		return (printf("Error\nMap is not surrounded by walls\n"), true);
	return (false);
}
