/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roversch <roversch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 16:25:44 by roversch          #+#    #+#             */
/*   Updated: 2025/11/11 12:00:44 by roversch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h>

static bool	input_numeral(char **argv, int argc)
{
	int	i;
	int	j;

	i = 1;
	while (i < argc && argv[i])
	{
		j = 0;
		while (argv[i][j])
			if (!ft_isdigit(argv[i][j++]))
				return (false);
		i++;
	}
	return (true);
}

int32_t	str_to_color(char *str)
{
	char	**ptr;
	int		r;
	int		g;
	int		b;

	ptr = ft_split(str, ',');
	if (!ptr || !ptr[0] || !ptr[1] || !ptr[2]
		|| ptr[3] || !input_numeral(ptr, 3))
		return (perror("Error\nInvalid RGB input\n"), -1);
	r = ft_atoi(ptr[2]);
	g = ft_atoi(ptr[1]);
	b = ft_atoi(ptr[0]);
	free_matrix(ptr);
	if (r > 255 || g > 255 || b > 255 || r < 0 || g < 0 || b < 0)
		return (perror("Error\nInvalid RGB input\n"), -1);
	return ((255 << 24 | (r << 16) | (g << 8) | (b)));
}
