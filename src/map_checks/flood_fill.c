/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roversch <roversch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 17:11:45 by roversch          #+#    #+#             */
/*   Updated: 2025/10/28 16:24:47 by roversch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h>

static int flood(char ***map, int count, int i, int j)
{
	if (count > 500)
		return (-1);
	(*map)[i][j] = 'F';
	if ((*map)[i + 1][j] == 'X' || (*map)[i - 1][j] == 'X' || (*map)[i][j + 1] == 'X' || (*map)[i][j - 1] == 'X')
		return (-1);
	if ((*map)[i + 1][j] == '0')
		if (!flood(map, count + 1, i + 1, j))
			return (-1);
	if ((*map)[i][j + 1] == '0')
		if (!flood(map, count + 1, i, j + 1))
			return (-1);
	if ((*map)[i - 1][j] == '0')
		if (!flood(map, count + 1, i - 1, j))
			return (-1);
	if ((*map)[i][j - 1] == '0')
		if (!flood(map, count + 1, i, j - 1))
			return (-1);
	return (0);
}

static int	flood_check(char **flood_map)
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
				return (-1);
			x++;
		}
		y++;
	}
	return (0);
}

static int	find_widest_point(char **map)
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

static char **fill_whitespace(char **flood_map, int width)
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

int flood_and_walls(char **map, t_parse *parse)
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
	print_map(flood_map, width + 1);
	flood_map = fill_whitespace(flood_map, width + 1);
	print_map(flood_map, width + 1);
	printf ("\n\nNL\n\n");
	if (flood(&flood_map, 0, (int)parse->pos.y, (int)parse->pos.x + 1) == -1)
		return (-1);
	print_map(flood_map, width + 1);
	if (flood_check(flood_map) == -1)
		return (-1);
	return (0);
}