/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeneghe <lmeneghe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 20:13:27 by lmeneghe          #+#    #+#             */
/*   Updated: 2024/07/25 12:47:27 by lmeneghe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

static void	start_graphics(t_game *game)
{
	if (!game)
		end_game("Error\nError on start_graphics call", NULL, CLOSE_OTHER);
	game->mlx_ptr = mlx_init();
	if (!game->mlx_ptr)
		end_game("Error\nError starting MLX connection", game, CLOSE_FAIL);
	game->map.total_pixel_width = (TILE_WIDTH * game->map.horiz_tiles);
	game->map.total_pixel_height = (TILE_HEIGHT * game->map.vertical_tiles);
}

static int	check_extension(char *filename)
{
	char	*extension;

	if (!filename)
		return (0);
	extension = ft_strrchr(filename, '.');
	if (!extension || ft_strlen(extension) != 4)
		return (0);
	if (ft_strncmp(extension, ".ber", 4))
		return (0);
	return (1);
}

static void	structs_initialization(t_game *game)
{
	if (!game)
		exit_program("Error\nInvalid structs_initialization call", CLOSE_OTHER);
	game->mlx_ptr = NULL;
	game->window = NULL;
	game->player.tile = NULL;
	game->player.movements = 0;
	game->images.player = NULL;
	game->images.background = NULL;
	game->images.wall = NULL;
	game->images.exit = NULL;
	game->images.collectible = NULL;
	game->images.exit_player = NULL;
	game->map.types = "01PEC";
	game->map.grid = NULL;
	game->map.list = NULL;
	game->map.collectibles = 0;
	game->var.filename = NULL;
	game->var.buffer = NULL;
	game->var.fd = -1;
	game->var.line_count = 0;
	game->var.exit_found = 0;
	game->var.collects_found = 0;
}

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2 || !argv || !argv[0] || !argv[1])
		exit_program("Error\nInvalid game arguments", CLOSE_OTHER);
	if (!check_extension(argv[1]))
		exit_program("Error\nMap file must be .ber type", CLOSE_OTHER);
	structs_initialization(&game);
	build_map(&game, argv[1]);
	start_graphics(&game);
	start_images(&game);
	grid_creation(&game);
	fill_screen(&game);
	mlx_key_hook(game.window, key_press_handler, &game);
	mlx_hook(game.window, 17, 0, mouse_close_handler, &game);
	mlx_loop(game.mlx_ptr);
	end_game(NULL, &game, CLOSE_SUCCESS);
}
