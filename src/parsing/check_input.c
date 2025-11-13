/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhendrik <nhendrik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 18:14:42 by nhendrik          #+#    #+#             */
/*   Updated: 2025/11/13 17:03:45 by nhendrik         ###   ########.fr       */
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

int check_textures(t_parse *parse)
{
	mlx_texture_t *text;

	text = mlx_load_png(parse->no_texture);
	if (!text)
		return (print_error("Error\nFailed to load image\n"));
	mlx_delete_texture(text);
	text = mlx_load_png(parse->so_texture);
	if (!text)
		return (print_error("Error\nFailed to load image\n"));
	mlx_delete_texture(text);
	text = mlx_load_png(parse->we_texture);
	if (!text)
		return (print_error("Error\nFailed to load image\n"));
	mlx_delete_texture(text);
	text = mlx_load_png(parse->ea_texture);
	if (!text)
		return (print_error("Error\nFailed to load image\n"));
	mlx_delete_texture(text);
	if (str_to_color(parse->ceiling_color) == -1)
		return (-1);
	if (str_to_color(parse->floor_color) == -1)
		return (-1);
	return (0);
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
	if (check_textures(parse) == -1)
		return (empty_parse(parse, false), -1);
	parse->int_map = ctoi_map(&parse->map[map_pos]);
	if (!parse->int_map)
		return (empty_parse(parse, false), -1);
	return (1);
}
