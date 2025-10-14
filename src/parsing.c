/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhendrik <nhendrik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 17:20:47 by roversch          #+#    #+#             */
/*   Updated: 2025/10/14 18:56:09 by nhendrik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

mlx_texture_t *fill_info(char *str, char *input)
{
	char	*out;
	int		i;

	i = 0;
	while (input[i] == ' ')
		i++;
	if (input[i] != '"')
		return (NULL);
	out = ft_substr(input, i + 1, ft_str)
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
				parse->NO_texture = fill_info("NO", &parse->map[i][j + 3]);
			else if (!ft_strncmp(&parse->map[i][j], "SO ", 3))
				parse->SO_texture = fill_info("SO", &parse->map[i][j + 3]);
			else if (!ft_strncmp(&parse->map[i][j], "EA ", 3))
				parse->EA_texture = fill_info("EA", &parse->map[i][j + 3]);
			else if (!ft_strncmp(&parse->map[i][j], "WE ", 3))
				parse->WE_texture = fill_info("WE", &parse->map[i][j + 3]);
			j++;
		}
		i++;
	}
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

int check_input(char *map_name)
{
	// int **map;
	t_parse parse;

	if (check_name(map_name) == -1)
		return (printf("Error\nInvalid map name\n"), -1);
	if (parsing(map_name, &parse) == -1)
		return (-1);
	// check_map();
	// ctoi_map();
	return (1);
}
