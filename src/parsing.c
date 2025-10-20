/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhendrik <nhendrik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 17:20:47 by roversch          #+#    #+#             */
/*   Updated: 2025/10/20 14:01:21 by nhendrik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

char *fill_info(char *input)
{
	char	*out;
	int		i;
	int		len;

	i = 0;
	while (input[i] == ' ')
		i++;
	if (input[i] != '"')
		return (NULL);
	len = i + 1;
	while (input[len] && input[len] != '"' && input[len] != '\n')
		len++;
	if (input[len] != '"')
		return (NULL);
	out = ft_substr(input, i + 1, len - (i + 1));
	return (out);
}

int	parsing(char *map_name, t_parse *parse)
{
	int		i;
	int		j;

	parse->map = get_map(map_name);
	if (!parse->map)
		return (-1);
	i = 0;
	while (parse->map[i])
	{
		j = 0;
		while(parse->map[i][j])
		{
			if (!ft_strncmp(&parse->map[i][j], "NO ", 3))
				parse->NO_texture = fill_info(&parse->map[i][j + 3]);
			else if (!ft_strncmp(&parse->map[i][j], "SO ", 3))
				parse->SO_texture = fill_info(&parse->map[i][j + 3]);
			else if (!ft_strncmp(&parse->map[i][j], "EA ", 3))
				parse->EA_texture = fill_info(&parse->map[i][j + 3]);
			else if (!ft_strncmp(&parse->map[i][j], "WE ", 3))
				parse->WE_texture = fill_info(&parse->map[i][j + 3]);
			else if (!ft_strncmp(&parse->map[i][j], "F ", 2))
				parse->floor_color = "100,0,0";
			else if (!ft_strncmp(&parse->map[i][j], "C ", 2))
				parse->ceiling_color = "0,0,50";
			j++;
			if (parse->NO_texture && parse->SO_texture && parse->EA_texture && parse->WE_texture && parse->floor_color && parse->ceiling_color)
				return (i);
		}
		i++;
	}
	return (-1);
}

int	check_name(char *name)
{
	int	i;

	i = 0;
	while (name[i] && ft_strncmp(&name[i], ".cub\0", 5))
		i++;
	if (!name[i])
		return (-1);
	return (0);
}

void set_pos_and_dir(t_parse *parse, int y, int x, char dir)
{
	parse->pos.x = x;
	parse->pos.y = y;
	// if (dir == 'N')
	// 	parse->dir.y = 1;
	// else if (dir == 'E')
	// 	parse->dir.x = 1;
	// else if (dir == 'S')
	// 	parse->dir.y = -1;
	// else if (dir == 'W')
	// 	parse->dir.x = -1;
	(void)dir;
}

int **ctoi_map(char **map, t_parse *parse)
{
	int **out;
	int	i;
	int	j;

	i = 0;
	while (map[i])
		i++;
	out = ft_calloc(i, sizeof(int *));
	i = 0;
	while (map[i])
	{
		j = 0;
		out[i] = ft_calloc(ft_strlen(map[i]) + 1, sizeof(int));
		while (map[i][j])
		{
			if (map[i][j] == '0' || map[i][j] == '1')
				out[i][j] = map[i][j] - '0';
			else if (map[i][j] == 'N' || map[i][j] == 'E' || map[i][j] == 'S' || map[i][j] == 'W')
			{
				set_pos_and_dir(parse, i, j, map[i][j]);
				printf("x %i, y %i\n", j, i);
				out[i][j] = 0;
			}
			j++;
		}
		i++;
	}
	return (out);
}

int look_for_empty_lines(int map_pos, char **map)
{
	int i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] != ' ' || map[i][j] != '\n')
				return (map_pos + i);
			j++;
		}
		i++;
	}
	return (-1);
}

int check_input(char *map_name, t_parse *parse)
{
	int		map_pos;

	if (check_name(map_name) == -1)
		return (printf("Error\nInvalid map name\n"), -1);
	parse->EA_texture = NULL;
	parse->NO_texture = NULL;
	parse->WE_texture = NULL;
	parse->SO_texture = NULL;
	parse->floor_color = NULL;
	parse->ceiling_color = NULL;
	parse->dir.x = 1;
	parse->dir.y = 0;
	map_pos = parsing(map_name, parse);
	if (map_pos == -1)
		return (printf("Error\n"), -1);
	map_pos = look_for_empty_lines(map_pos, &parse->map[map_pos]);
	if (map_pos == -1)
		return (printf("Error\n"), -1);
	// check_map();
	parse->int_map = ctoi_map(&parse->map[map_pos], parse);
	return (1);
}
