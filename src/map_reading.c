/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_reading.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhendrik <nhendrik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 12:53:25 by nhendrik          #+#    #+#             */
/*   Updated: 2025/10/06 13:32:32 by nhendrik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>

void *free_and_null(void *ptr)
{
	free(ptr);
	ptr = NULL;
	return (NULL);
}

int	count_lines(char *file_name)
{
	char	*line;
	int		i;
	int		fd;

	fd = open(file_name, O_RDONLY);
	line = get_next_line(fd);
	if (!line)
		return (close(fd), 0);
	i = 0;
	while (line)
	{
		free_and_null(line);
		line = get_next_line(fd);
		i++;
	}
	close(fd);
	return (i);
}

int		**read_map(char *file_name)
{
	int		**map;
	int		fd;
	int		line_count;
	int		i;

	line_count = count_lines(file_name);
	fd = open(file_name, O_RDONLY);
	i = 0;
	map = ft_calloc(line_count, sizeof(int *));
	while (i < line_count)
	{
		char *tmp = get_next_line(fd);
		map[i] = ft_calloc(ft_strlen(tmp), sizeof(int));
		int	j = 0;
		while (tmp[j] && tmp[j] >= '0' && tmp[j] <= '9')
		{
			map[i][j] = tmp[j] - '0';
			printf("%i", map[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
	close(fd);
	return (map);
}