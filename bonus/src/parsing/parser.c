/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhendrik <nhendrik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 17:20:47 by roversch          #+#    #+#             */
/*   Updated: 2025/11/13 17:13:43 by nhendrik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

static char	*fill_info(char *input)
{
	char	*out;
	int		i;
	int		len;

	i = 0;
	while (input[i] == ' ')
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

static int	check_dupes(t_parse *parse, int i, int j)
{
	if (!ft_strncmp(&parse->map[i][j], "NO ", 3) && parse->no_texture)
		return (-1);
	else if (!ft_strncmp(&parse->map[i][j], "SO ", 3) && parse->so_texture)
		return (-1);
	else if (!ft_strncmp(&parse->map[i][j], "EA ", 3) && parse->ea_texture)
		return (-1);
	else if (!ft_strncmp(&parse->map[i][j], "WE ", 3) && parse->we_texture)
		return (-1);
	else if (!ft_strncmp(&parse->map[i][j], "F ", 2) && parse->floor_color)
		return (-1);
	else if (!ft_strncmp(&parse->map[i][j], "C ", 2) && parse->ceiling_color)
		return (-1);
	return (0);
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
		while (parse->map[i][j])
		{
			if (check_dupes(parse, i, j) == -1)
				return (print_error("Error\nDuplicate elements\n"));
			compare_info(parse, i, j);
			j++;
			if (parse->no_texture && parse->so_texture
				&& parse->ea_texture && parse->we_texture
				&& parse->floor_color && parse->ceiling_color)
				return (i + 1);
		}
		i++;
	}
	return (print_error("Error\nNot enough elements\n"));
}
