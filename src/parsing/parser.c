/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roversch <roversch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 17:20:47 by roversch          #+#    #+#             */
/*   Updated: 2025/11/06 15:38:51 by roversch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

static char	*fill_info(char *input)
{
	char	*out;
	int		i;
	int		len;

	i = 0;
	while (ft_iswhitespace(input[i]))
		i++;
	len = i + 1;
	while (input[len] && input[len] != '\n')
		len++;
	out = ft_substr(input, i, len - (i));
	return (out);
}

static void	compare_info(t_parse *parse, int i, int j)
{
	if (!ft_strncmp(&parse->map[i][j], "NO ", 3))
		parse->no_texture = fill_info(&parse->map[i][j + 3]);
	else if (!ft_strncmp(&parse->map[i][j], "SO ", 3))
		parse->so_texture = fill_info(&parse->map[i][j + 3]);
	else if (!ft_strncmp(&parse->map[i][j], "EA ", 3))
		parse->ea_texture = fill_info(&parse->map[i][j + 3]);
	else if (!ft_strncmp(&parse->map[i][j], "WE ", 3))
		parse->we_texture = fill_info(&parse->map[i][j + 3]);
	else if (!ft_strncmp(&parse->map[i][j], "F ", 2))
		parse->floor_color = fill_info(&parse->map[i][j + 2]);
	else if (!ft_strncmp(&parse->map[i][j], "C ", 2))
		parse->ceiling_color = fill_info(&parse->map[i][j + 2]);
}

static int	parsing(char *map_name, t_parse *parse)
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
		while (parse->map[i][j])
		{
			compare_info(parse, i, j);
			j++;
			if (parse->no_texture && parse->so_texture
				&& parse->ea_texture && parse->we_texture
				&& parse->floor_color && parse->ceiling_color)
				return (i);
		}
		i++;
	}
	return (-1);
}

static void	set_parse_vars_null(t_parse *parse)
{
	parse->ea_texture = NULL;
	parse->no_texture = NULL;
	parse->we_texture = NULL;
	parse->so_texture = NULL;
	parse->floor_color = NULL;
	parse->ceiling_color = NULL;
	parse->dir.x = 0;
	parse->dir.y = 0;
}

int	check_input(char *map_name, t_parse *parse)
{
	int		map_pos;

	if (check_name(map_name) == -1)
		return (printf("Error\nInvalid map name\n"), -1);
	set_parse_vars_null(parse);
	map_pos = parsing(map_name, parse);
	if (map_pos == -1)
		return (printf("Error\nNot enough elements\n"), -1);
	printf("%i\n", map_pos);
	map_pos = look_for_empty_lines(map_pos, &parse->map[map_pos]) + 1;//???
	printf("%i\n", map_pos);
	if (map_pos == -1)
		return (printf("Error\n"), -1);
	if (check_map(parse, &parse->map[map_pos]) == -1)
		return (-1);
	parse->int_map = ctoi_map(&parse->map[map_pos]);
	return (1);
}
