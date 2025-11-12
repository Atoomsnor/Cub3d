/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhendrik <nhendrik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 18:03:36 by nhendrik          #+#    #+#             */
/*   Updated: 2025/11/13 00:27:25 by nhendrik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdlib.h>

int	free_and_null(void *ptr)
{
	free(ptr);
	ptr = NULL;
	return (-1);
}

void	free_matrix(void *ptr)
{
	int		i;
	char	**str;

	if (!ptr)
		return ;
	str = (char **)ptr;
	i = 0;
	while (str[i])
	{
		free_and_null(str[i]);
		i++;
	}
	free_and_null(str);
}

void	free_flood(void *ptr)
{
	int		i;
	char	**str;

	if (!ptr)
		return ;
	str = (char **)ptr;
	i = 0;
	while (str[i])
	{
		free_and_null(str[i]);
		i++;
	}
	free_and_null(str[i]);
	free_and_null(str);
}

int	print_error(char *str)
{
	ft_putstr_fd(str, 2);
	return (-1);
}
