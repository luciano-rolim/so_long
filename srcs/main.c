/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeneghe <lmeneghe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 20:13:27 by lmeneghe          #+#    #+#             */
/*   Updated: 2024/07/22 15:51:01 by lmeneghe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

static void	start_graphics(t_game *game)
{
	if (!game)
		close_game("Error\nError on start_graphics call", NULL, CLOSE_OTHERS);
	game->mlx_ptr = mlx_init();
	if (!game->mlx_ptr)
		close_game("Error\nError starting MLX connection", game, CLOSE_FAILURE);
	game->map.total_pixel_width = (TILE_WIDTH * game->map.horizontal_tiles);
	game->map.total_pixel_height = (TILE_HEIGHT * game->map.vertical_tiles);
	game->window = mlx_new_window(game->mlx_ptr, game->map.total_pixel_width, game->map.total_pixel_height, "Custom Pac-Man");
	if (!game->window)
		close_game("Error\nError initializing game window", game, CLOSE_FAILURE);
}

static int	check_extension(char *filename)
{
	char	*extension;

	if (!filename)
		return (0);
	extension = ft_strrchr(filename, '.');
	if (!extension || ft_strlen(extension) != 4)
		return (0);
	if(ft_strncmp(extension, ".ber", 4))
		return (0);
	return (1);
}

static void structs_initialization(t_game *game)
{
	if (!game)
		exit_program("Error\nInvalid structs_initialization call", CLOSE_OTHERS);
	game->mlx_ptr = NULL;
	game->window = NULL;
	game->player.tile = NULL;
	game->player.movements = 0;
	game->images.player = NULL;
	game->images.background = NULL;
	game->images.wall = NULL;
	game->images.exit = NULL;
	game->images.collectible = NULL;
	game->images.exit_and_player = NULL;
	game->map.types = "01PEC";
	game->map.grid = NULL;
	game->map.list = NULL;
	game->map.collectibles = 0;
	game->tmp_var.buffer = NULL;
	game->tmp_var.file_fd = -1;
	game->tmp_var.line_count = 0;
	game->tmp_var.exit_found = 0;
	game->tmp_var.collectables_found = 0;
}

void	search_valid_path(t_game *game, t_tile *current_tile)
{
	if (!game)
		close_game("Error\nInvalid search_valid_path call", NULL, CLOSE_OTHERS);
	if (!current_tile)
		return ;
	if (current_tile->checked == 1)
		return ;
	current_tile->checked = 1;
	if (current_tile->type == WALL)
		return ;
	else if (current_tile->type == COLLECTIBLE)
		game->tmp_var.collectables_found++;
	else if (current_tile->type == EXIT)
		game->tmp_var.exit_found++;
	search_valid_path(game, current_tile->up_tile);
	search_valid_path(game, current_tile->right_tile);
	search_valid_path(game, current_tile->down_tile);
	search_valid_path(game, current_tile->left_tile);
}

void	valid_path(t_game *game)
{
	search_valid_path(game, game->player.tile);
	if (game->tmp_var.exit_found != 1 || (game->tmp_var.collectables_found != game->map.collectibles))
		close_game("Error\nPath is blocked", game, CLOSE_OTHERS);
}

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2 || !argv || !argv[0] || !argv[1])
		exit_program("Error\nInvalid game arguments", CLOSE_OTHERS);
	if (!check_extension(argv[1]))
		exit_program("Error\nMap file must be .ber type", CLOSE_OTHERS);
	structs_initialization(&game);
	build_map(&game, argv[1]);
	start_graphics(&game);
	start_images(&game);
	grid_creation(&game);
	valid_path(&game);
	mlx_key_hook(game.window, key_press, &game);
	mlx_loop(game.mlx_ptr);
	close_game(NULL, &game, CLOSE_SUCCESS);
}
