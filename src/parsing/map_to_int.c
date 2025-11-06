/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_to_int.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roversch <roversch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 15:24:22 by roversch          #+#    #+#             */
/*   Updated: 2025/11/06 15:34:13 by roversch         ###   ########.fr       */
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
	return (-1);
}

int	**ctoi_map(char **map)
{
	int	**out;
	int	i;
	int	j;

	i = 0;
	while (map[i])
		i++;
	out = ft_calloc(i + 1, sizeof(int *));
	if (!out)
		return (NULL);
	i = 0;
	while (map[i])
	{
		j = 0;
		out[i] = ft_calloc(ft_strlen(map[i]) + 1, sizeof(int));
		while (map[i][j])
		{
			out[i][j] = ctoi_pos(map[i][j]);
			j++;
		}
		i++;
	}
	return (out);
}
