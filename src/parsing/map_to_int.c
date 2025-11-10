/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_to_int.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhendrik <nhendrik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 15:24:22 by roversch          #+#    #+#             */
/*   Updated: 2025/11/10 17:54:35 by nhendrik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h>

static int	ctoi_pos(char c)
{
	if (c == '0' || c == '1')
		return (c - '0');
	else if (c == 'N' || c == 'E'
		|| c == 'S' || c == 'W')
		return (0);
	return (2);
}

int	**ctoi_map(char **map)
{
	const int	width = find_widest_point(map);
	int			**out;
	int			i;
	int			j;

	i = 0;
	while (map[i])
		i++;
	out = ft_calloc(i + 1, sizeof(int *));
	if (!out)
		return (NULL);
	i = 0;
	while (map[i])
	{
		j = -1;
		out[i] = ft_calloc(width + 1, sizeof(int));
		if (!out[i])
			return (free_matrix(out), NULL);
		while (map[i][++j])
			out[i][j] = ctoi_pos(map[i][j]);
		while (j < width)
			out[i][j++] = 2;
		i++;
	}
	return (out);
}
