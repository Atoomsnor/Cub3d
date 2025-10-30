/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cleanup.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhendrik <nhendrik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 18:02:59 by nhendrik          #+#    #+#             */
/*   Updated: 2025/10/30 18:28:50 by nhendrik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "cub3d.h"

void	free_texture_paths(t_parse *parse)
{
	if (parse->ceiling_color)
		free_and_null(parse->ceiling_color);
	if (parse->ea_texture)
		free_and_null(parse->ea_texture);
	if (parse->we_texture)
		free_and_null(parse->we_texture);
	if (parse->so_texture)
		free_and_null(parse->so_texture);
	if (parse->no_texture)
		free_and_null(parse->no_texture);
	if (parse->floor_color)
		free_and_null(parse->floor_color);
}

int	empty_parse(t_parse *parse, bool map)
{
	if (map && parse->int_map)
		free_matrix(parse->int_map);
	free_texture_paths(parse);
	//if (parse->map)
		//free_matrix(parse->map);
	return (1);
}
