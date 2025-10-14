/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhendrik <nhendrik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 00:29:41 by nhendrik          #+#    #+#             */
/*   Updated: 2025/10/14 15:51:11 by nhendrik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_player *init_player(double pos_x, double pos_y, double dir_x, double dir_y)
{
	t_player *player;

	player = ft_calloc(1, sizeof(struct s_player));
	if (!player)
		return (NULL);
	player->pos.x = pos_x;
	player->pos.y = pos_y;
	// dir_x -1 == looking left dir_x 1 == looking right
	player->dir.x = dir_x;
	// dir_y -1 == looking down dir_y 1 == looking up
	player->dir.y = dir_y;
	player->plane.x = 0;
	player->plane.y = 0.66;
	return (player);
}

t_img *init_images(mlx_t *mlx)
{
	t_img *img;
	
	img = ft_calloc(1, sizeof(struct s_img));
	img->NO = png_to_image("./img/Wallgrey1.png", mlx);
	img->EA = png_to_image("./img/Walldark1.png", mlx);
	img->SO = png_to_image("./img/Wallgrey2.png", mlx);
	img->WE = png_to_image("./img/Walldark2.png", mlx);
	img->gun = png_to_image("./img/Gun.png", mlx);
	img->hud = png_to_image("./img/Hud.png", mlx);
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

t_game *init_game(char **argv)
{
	t_game *game;

	game = ft_calloc(1, sizeof(struct s_game));
	game->player = init_player(2, 5, 1, 0);
	game->width = SCREEN_WIDTH;
	game->height = SCREEN_HEIGHT;
	// parsing(argv[1], game);
	game->world_map = read_map(argv[1], game);
	game->mlx = mlx_init(game->width, game->height, "CUB3D", true);
	game->img = init_images(game->mlx);
	game->fps = init_fps();
	game->screen_buffer = NULL;
	return (game);
}
