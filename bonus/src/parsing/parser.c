/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhendrik <nhendrik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 17:20:47 by roversch          #+#    #+#             */
/*   Updated: 2025/11/18 11:21:09 by nhendrik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

static int	fill_info_check(char *input, char **str, int *pos, int strlen)
{
	int		i;
	int		len;

	i = 0;
	while (i < *pos && input[i])
	{
		if (input[i] != ' ')
			return (print_error("Error\nInvalid input\n"));
		i++;
	}
	i += strlen;
	while (input[i] == ' ')
		i++;
	len = i + 1;
	while (input[len] && input[len] != '\n')
		len++;
	*str = ft_substr(input, i, len - (i));
	*pos = len;
	if (!*str)
		return (-1);
	if (*str[0] == '\n')
		return (print_error("Error\nInvalid input\n"));
	return (0);
}

static int	compare_info(t_parse *parse, int i, int *j)
{
	if (!ft_strncmp(&parse->map[i][*j], "NO ", 3))
		return (fill_info_check(parse->map[i], &parse->no_texture, j, 3));
	if (!ft_strncmp(&parse->map[i][*j], "SO ", 3))
		return (fill_info_check(parse->map[i], &parse->so_texture, j, 3));
	if (!ft_strncmp(&parse->map[i][*j], "EA ", 3))
		return (fill_info_check(parse->map[i], &parse->ea_texture, j, 3));
	if (!ft_strncmp(&parse->map[i][*j], "WE ", 3))
		return (fill_info_check(parse->map[i], &parse->we_texture, j, 3));
	if (!ft_strncmp(&parse->map[i][*j], "F ", 2))
		return (fill_info_check(parse->map[i], &parse->floor_color, j, 2));
	if (!ft_strncmp(&parse->map[i][*j], "C ", 2))
		return (fill_info_check(parse->map[i], &parse->ceiling_color, j, 2));
	if (parse->map[i][*j] != ' ' && parse->map[i][*j] != '\n')
		return (print_error("Error\nInvalid input\n"));
	return (0);
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
			if (compare_info(parse, i, &j) == -1)
				return (-1);
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
