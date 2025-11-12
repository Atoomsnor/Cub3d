/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhendrik <nhendrik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 18:14:42 by nhendrik          #+#    #+#             */
/*   Updated: 2025/11/13 00:32:48 by nhendrik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h>

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
		return (print_error("Error\nInvalid map name\n"));
	set_parse_vars_null(parse);
	map_pos = parsing(map_name, parse);
	if (map_pos == -1)
		return (empty_parse(parse, false), -1);
	map_pos = look_for_lines(map_pos, &parse->map[map_pos]);
	if (map_pos == -1)
		return (empty_parse(parse, false),
			print_error("Error\nInvalid map position\n"));
	if (check_map(parse, &parse->map[map_pos]) == -1)
		return (empty_parse(parse, false), -1);
	parse->int_map = ctoi_map(&parse->map[map_pos]);
	return (1);
}
