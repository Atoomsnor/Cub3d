/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_reading.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhendrik <nhendrik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 12:53:25 by nhendrik          #+#    #+#             */
/*   Updated: 2025/11/17 17:35:00 by nhendrik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>

static void	*free_null(void *ptr)
{
	free(ptr);
	ptr = NULL;
	return (NULL);
}

static int	count_lines(char *file_name)
{
	char	*line;
	int		i;
	int		fd;

	fd = open(file_name, O_RDONLY);
	if (fd < 0)
		return (print_error("Error\nInvalid file\n"));
	line = get_next_line(fd);
	if (!line)
	{
		close(fd);
		return (print_error("Error\nFile is empty\n"));
	}
	i = 0;
	while (line)
	{
		free_null(line);
		line = get_next_line(fd);
		i++;
	}
	close(fd);
	return (i);
}

static void	*free_error_ret(char **str, char *err)
{
	if (str)
		free_matrix(str);
	if (err)
		print_error(err);
	return (NULL);
}

char	**get_map(char *input)
{
	int		fd;
	int		i;
	int		line_count;
	char	**ret;

	line_count = count_lines(input);
	if (line_count == -1)
		return (NULL);
	fd = open(input, O_RDONLY);
	if (fd < 0)
		return (free_error_ret(NULL, "Error\nInvalid file\n"));
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
	if (ret[i - 1][ft_strlen(ret[i - 1]) - 1] == '\n')
		return (free_error_ret(ret, "Error\nEmpty line(s) in map\n"));
	return (ret);
}
