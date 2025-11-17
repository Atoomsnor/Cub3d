/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_to_int.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhendrik <nhendrik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 15:24:22 by roversch          #+#    #+#             */
/*   Updated: 2025/11/17 11:22:48 by nhendrik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static int	ctoi_pos(char c)
{
	if (c == '0' || c == '1')
		return (c - '0');
	else if (c == 'N' || c == 'E'
		|| c == 'S' || c == 'W')
		return (0);
	else if (c == 'D')
		return (3);
	return (2);
}

static void	ctoi_str(char *map, const int width, int *out)
{
	int		i;

	i = 0;
	while (map[i])
	{
		out[i] = ctoi_pos(map[i]);
		i++;
	}
	while (i < width)
	{
		out[i] = 2;
		i++;
	}
}

int	**ctoi_map(char **map)
{
	const int	width = find_widest_point(map);
	int			**out;
	int			i;

	i = 0;
	while (map[i])
		i++;
	if (i > 100 || width > 100)
		return (print_error("Error\nMap is too big\n"), NULL);
	out = ft_calloc(i + 1, sizeof(int *));
	if (!out)
		return (NULL);
	i = -1;
	while (map[++i])
	{
		out[i] = ft_calloc(width + 1, sizeof(int));
		if (!out[i])
			return (free_matrix(out), NULL);
		ctoi_str(map[i], width, out[i]);
	}
	return (out);
}
