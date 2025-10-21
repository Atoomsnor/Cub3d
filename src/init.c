/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhendrik <nhendrik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 00:29:41 by nhendrik          #+#    #+#             */
/*   Updated: 2025/10/21 13:26:58 by nhendrik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_player *init_player(t_vector pos, t_vector dir)
{
	t_player *player;
	const double FOV_SCALE = 0.66;

	player = ft_calloc(1, sizeof(struct s_player));
	if (!player)
		return (NULL);
	player->pos = pos;
	player->pos.x += 0.5;
	player->pos.y += 0.5;
	// dir_x -1 == looking left dir_x 1 == looking right
	player->dir = dir;
	// dir_y -1 == looking down dir_y 1 == looking up
	player->plane.x = -player->dir.y * FOV_SCALE;
	player->plane.y = player->dir.x * FOV_SCALE;
	return (player);
}

int32_t str_to_color(char *str)
{
	char **ptr;
	int	r;
	int	g;
	int	b;

	ptr = ft_split(str, ',');
	r = ft_atoi(ptr[2]);
	g = ft_atoi(ptr[1]);
	b = ft_atoi(ptr[0]);
	if (r > 255 || g > 255 || b > 255)
		return (ft_printf("error\n"), 0);
	return ((255 << 24 | (r << 16) | (g << 8) | (b)));
}

t_img *init_images(mlx_t *mlx, t_parse parse)
{
	t_img *img;
	
	img = ft_calloc(1, sizeof(struct s_img));
	ft_printf("%s %s %s %s\n", parse.NO_texture, parse.EA_texture, parse.SO_texture, parse.WE_texture);
	img->NO = png_to_image(parse.NO_texture, mlx);
	img->EA = png_to_image(parse.EA_texture, mlx);
	img->SO = png_to_image(parse.SO_texture, mlx);
	img->WE = png_to_image(parse.WE_texture, mlx);
	img->hud = png_to_image("./img/Hud.png", mlx);
	img->floor_color = str_to_color(parse.floor_color);
	ft_printf("%s\n", parse.floor_color);
	img->ceiling_color = str_to_color(parse.ceiling_color);
	return (img);
}

t_fps *init_fps(void)
{
	t_fps *fps;

	fps = ft_calloc(1, sizeof(struct s_fps));
	fps->start_time = get_time();
	fps->last_time = fps->start_time;
	fps->frames = 0;
	return (fps);
}

t_game *init_game(t_parse parse)
{
	t_game *game;

	game = ft_calloc(1, sizeof(struct s_game));
	game->player = init_player(parse.pos, parse.dir);
	game->width = SCREEN_WIDTH;
	game->height = SCREEN_HEIGHT;
	// parsing(argv[1], game);
	game->world_map = parse.int_map;
	game->mlx = mlx_init(game->width, game->height, "CUB3D", true);
	game->img = init_images(game->mlx, parse);
	game->fps = init_fps();
	game->screen_buffer = NULL;
	return (game);
}
