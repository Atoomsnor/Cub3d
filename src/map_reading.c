/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_reading.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhendrik <nhendrik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 12:53:25 by nhendrik          #+#    #+#             */
/*   Updated: 2025/10/26 02:00:56 by nhendrik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>

void	*free_and_null(void *ptr)
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

int	**read_map(char *file_name, t_game *game)
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
		game->game_width = ft_strlen(tmp);
		int	j = 0;
		while (tmp[j] && tmp[j] >= '0' && tmp[j] <= '9')
		{
			map[i][j] = tmp[j] - '0';
			printf("%i", map[i][j]);
			j++;
		}
		printf("\n");
		free_and_null(tmp);
		i++;
	}
	close(fd);
	(void)game; //?
	return (map);
}

char	**get_map(char *input)
{
	int		fd;
	int		i;
	int		line_count;
	char	**ret;

	line_count = count_lines(input);
	if (!line_count)
		return (NULL);
	fd = open(input, O_RDONLY);
	if (fd < 0)
		return (ft_printf("Invalid file.\n"), NULL);
	i = 0;
	ret = (char **)ft_calloc(line_count + 1, sizeof(char *));
	if (!ret)
		return (NULL);
	ret[i] = get_next_line(fd);
	while (ret[i])
	{
		i++;
		ret[i] = get_next_line(fd);
	}
	close(fd);
	return (ret);
}