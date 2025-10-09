/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhendrik <nhendrik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 12:36:29 by roversch          #+#    #+#             */
/*   Updated: 2025/10/10 00:31:38 by nhendrik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h>
#include <math.h>

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

mlx_image_t	*png_to_image(const char *path, t_game *game)
{
	mlx_texture_t	*texture;
	mlx_image_t		*ret;

	texture = mlx_load_png(path);
	ret = mlx_texture_to_image(game->mlx, texture);
	mlx_delete_texture(texture);
	if (ret)
		mlx_resize_image(ret, SCALE, SCALE);
	return (ret);
}

int	main(int argc, char **argv)
{
	t_game		game[1];

	if (argc != 2)
		argv[1] = "map.txt";
	game->player = init_player(2, 5, 1, 0);
	printf("%f\n", game->player->pos.x);
	game->textures = ft_calloc(1, sizeof(struct s_texture));
	game->textures->wall_texture = mlx_load_png("./img/Wallgrey1.png");
	game->textures->gun = mlx_load_png("./img/Gun.png");
	game->img = ft_calloc(1, sizeof(struct s_img));
	// parsing(argv[1], game);
	game->world_map = read_map(argv[1], game);
	game->mlx = mlx_init(SCREEN_WIDTH, SCREEN_HEIGHT, "CUB3D", false);
	game->img->NO = png_to_image("./img/Wallgrey1.png", game);
	game->img->EA = png_to_image("./img/Walldark1.png", game);
	game->img->SO = png_to_image("./img/Wallgrey2.png", game);
	game->img->WE = png_to_image("./img/Walldark2.png", game);
	game->gun = mlx_texture_to_image(game->mlx, game->textures->gun);
	game->img_wall = mlx_texture_to_image(game->mlx, game->textures->wall_texture);
	game->screen_buffer = NULL;
	mlx_resize_image(game->img_wall, SCALE, SCALE);
	mlx_resize_image(game->gun, SCREEN_HEIGHT / 2, SCREEN_HEIGHT/ 2);
	raycast(game);
	mlx_image_to_window(game->mlx, game->gun, SCREEN_WIDTH / 2 - game->gun->width / 2, SCREEN_HEIGHT / 2);
	game->gun->instances[0].z = 1;
	// game->img_wall = mlx_texture_to_image(game->mlx, game->textures->wall_texture);
	// mlx_image_to_window(game->mlx, game->img_wall, 418, 268);
	// mlx_key_hook(game->mlx, &test_keyhook, game);
	mlx_loop_hook(game->mlx, &test_keyhook, game);
	mlx_loop(game->mlx);
}
