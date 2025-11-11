/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_checks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roversch <roversch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 17:21:56 by roversch          #+#    #+#             */
/*   Updated: 2025/11/11 11:57:49 by roversch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	look_for_lines(int map_pos, char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (!ft_iswhitespace(map[i][j]) && map[i][j] != '\n')
				return (map_pos + i);
			j++;
		}
		i++;
	}
	return (-1);
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
