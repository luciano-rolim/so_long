/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeneghe <lmeneghe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 20:13:27 by lmeneghe          #+#    #+#             */
/*   Updated: 2024/07/22 08:00:36 by lmeneghe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

t_tile *tile_creation(t_game *game, int x, int y, t_tile ***grid)
{
	t_tile		*new_tile;

	if (!game || !grid)
		close_game("Error on tile_creation call", game, CLOSE_OTHERS);
	new_tile = NULL;
	new_tile = ft_calloc(1, sizeof(t_tile));
	if (!new_tile)
		close_game("ft_calloc failure on tile", game, CLOSE_FAILURE);
	new_tile->image = NULL;
	new_tile->right_tile = NULL;
	new_tile->left_tile = NULL;
	new_tile->up_tile = NULL;
	new_tile->down_tile = NULL;
	new_tile->x_grid = x;
	new_tile->y_grid = y;
	return (new_tile);
}

void	image_attribution(t_game *game, t_tile *tile)
{
	if (!game || !tile)
		close_game("Error on image_attribution call", game, CLOSE_OTHERS);
	if (tile->type == PLAYER)
	{
		tile->image = game->images.player;
		game->player.tile = tile;
		game->player.movements = 0;
	}
	else if (tile->type == EMPTY)
		tile->image = game->images.background;
	else if (tile->type == WALL)
		tile->image = game->images.wall;
	else
		close_game("Invalid tile->image type", game, CLOSE_OTHERS);
}

void	tiles_coordinates(t_game *game)
{
	t_tile	*tmp_tile;
	int		x;
	int		y;
	int		i;
	t_line	*tmp_line;

	if (!game)
		close_game("Error on tile_coordinates call", NULL, CLOSE_OTHERS);
	tmp_line = game->map.list; //Check if this is necessary
	tmp_tile = NULL; //Check if this is necessary
	y = 0;
	while (y < game->map.vertical_tiles)
	{
		i = 0;
		x = 0;
		while (x < game->map.horizontal_tiles)
		{
			tmp_tile = game->grid[y][x];
			tmp_tile->type = tmp_line->content[i];
			image_attribution(game, tmp_tile);
			if (x < (game->map.horizontal_tiles - 1))
				tmp_tile->right_tile = game->grid[y][x + 1];
			if (x > 0)
				tmp_tile->left_tile = game->grid[y][x - 1];
			if (y > 0)
				tmp_tile->up_tile = game->grid[y - 1][x];
			if (y < (game->map.vertical_tiles - 1))
				tmp_tile->down_tile = game->grid[y + 1][x];
			mlx_put_image_to_window(game->mlx_ptr, game->window, tmp_tile->image, \
			tmp_tile->x_grid * TILE_WIDTH, tmp_tile->y_grid * TILE_HEIGHT);
			x++;
			i++;
		}
		tmp_line = tmp_line->next_line;
		y++;
	}
}

void	grid_allocation(t_game *game)
{
	int		y;

	if (!game)
		close_game("Error on grid allocation call", NULL, CLOSE_OTHERS);
	game->grid = ft_calloc(game->map.vertical_tiles, sizeof(t_tile*));
	if (!game->grid)
		close_game("ft_calloc failure on grid", game, CLOSE_FAILURE);
	y = 0;
	while (y < game->map.vertical_tiles)
	{
		game->grid[y] = ft_calloc(game->map.horizontal_tiles, sizeof(t_tile*));
		if (!game->grid[y])
			close_game("ft_calloc failure on grid line", game, CLOSE_FAILURE);
		y++;
	}
}

void	grid_creation(t_game *game)
{
	int		x;
	int		y;

	if (!game)
		close_game("Error on grid_creation call", NULL, CLOSE_OTHERS);
	grid_allocation(game);
	x = 0;
	y = 0;
	while (y < game->map.vertical_tiles)
	{
		x = 0;
		while (x < game->map.horizontal_tiles)
		{
			game->grid[y][x] = tile_creation(game, x, y, game->grid);
			x++;
		}
		y++;
	}
	tiles_coordinates(game);
}

void	start_graphics(t_game *game)
{
	if (!game)
		close_game("Error on start_graphics call", NULL, CLOSE_OTHERS);
	game->mlx_ptr = mlx_init();
	if (!game->mlx_ptr)
		close_game("Error starting MLX connection", game, CLOSE_FAILURE);
	game->map.total_pixel_width = (TILE_WIDTH * game->map.horizontal_tiles);
	game->map.total_pixel_height = (TILE_HEIGHT * game->map.vertical_tiles);
	game->window = mlx_new_window(game->mlx_ptr, game->map.total_pixel_width, game->map.total_pixel_height, "Custom Pac-Man");
	if (!game->window)
		close_game("Error initializing game window", game, CLOSE_FAILURE);
}

int	xpm_conversion(void **image, char* address, t_game *game)
{
    int img_width = TILE_WIDTH;
    int img_height = TILE_HEIGHT;

	if (!image || !address || !game)
		close_game("Error on xpm_conversion call", game, CLOSE_FAILURE);
	*image = mlx_xpm_file_to_image(game->mlx_ptr, address, &img_width, &img_height);
	if (!image)
		return (0);
	return (1);
}

void	start_images(t_game *game)
{
	char* message;

	if (!game)
		close_game("Error on start_images call", NULL, CLOSE_OTHERS);
	message = "Error initializing image";
	if (!xpm_conversion(&game->images.player, "assets/left_1.xpm", game))
		close_game(message, game, CLOSE_FAILURE);
	if (!xpm_conversion(&game->images.background, "assets/background.xpm", game))
		close_game("Error initializing image", game, CLOSE_FAILURE);
	if (!xpm_conversion(&game->images.wall, "assets/wall.xpm", game))
		close_game("Error initializing image", game, CLOSE_FAILURE);
}

int	check_extension(char *filename)
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

void	map_allocation(t_game *game)
{
	int		y;

	if (!game)
		close_game("Invalid grid allocation call", NULL, CLOSE_OTHERS);
	game->map.map = ft_calloc(game->map.vertical_tiles, sizeof(char*));
	if (!game->map.map)
		close_game("ft_calloc failure on map", game, CLOSE_FAILURE);
	y = 0;
	while (y < game->map.vertical_tiles)
	{
		game->map.map[y] = ft_calloc(game->map.horizontal_tiles, sizeof(char));
		if (!game->map.map[y])
			close_game("ft_calloc failure on map line", game, CLOSE_FAILURE);
		y++;
	}
}

t_line *last_node(t_line *head_node)
{
	t_line *tmp_tile;

	if (!head_node)
		return (NULL);
	tmp_tile = head_node;
	while (tmp_tile->next_line)
		tmp_tile = tmp_tile->next_line;
	return (tmp_tile);
}

void add_new_node(t_game *game, char *content)
{
	//i need to build this function my way
	t_line	*new_node;
	t_line	*last_tile;

	if (!game || !content)
		close_game("Error on add_new_node call", game, CLOSE_OTHERS);
	new_node = malloc(sizeof(t_line));
	if (!new_node)
		close_game("ft_calloc failure on new node", game, CLOSE_FAILURE);
	new_node->content = content;
	new_node->next_line = NULL;
	if (!game->map.list)
	{
		game->map.list = new_node;
		return ;
	}
	last_tile = last_node(game->map.list);
	last_tile->next_line = new_node;
}

void	build_map(t_game *game, char *filename)
{
	int		file_fd;
	char	*buffer;
	int		line_len;
	int		line_count;
	t_line	*last_row;

	if (!game || !filename)
		close_game("Invalid build_map call", game, CLOSE_OTHERS);
	game->map.list = NULL;
	game->map.map = NULL;
	game->map.grid = NULL;
	game->map.types = NULL;
	game->map.types = "01P"; //will this be available outside function? Check later
	file_fd = open(filename, O_RDONLY);
	if (file_fd == -1)
		close_game("Open function failure", game, CLOSE_FAILURE);
	line_count = 0;
	line_len = 0;
	while (1)
	{
		buffer = get_next_line(file_fd); //Create special stuff to force get_next_line till the end, on the cleaning function
		//Create control when file has nothing and get_next_line (probably) return NULL?
		//The problem is that Get Next line can return NULL if it reaches the end of the file, so we need to diferenciate first call from last call
		if (!buffer)
			break ;
		line_len = ft_strlen(buffer);
		if (buffer[line_len - 1] == '\n')
		{
			buffer[line_len - 1] = '\0';
			line_len -= 1;
		}
		if (line_count == 0)
		{
			if (!ft_is_string_char_set(buffer, "1"))
			{
				free(buffer);
				close_game("First row must be made only by walls", game, CLOSE_OTHERS);
			}
			game->map.horizontal_tiles = (line_len);
		}
		else
		{
			if (buffer[0] != '1' || buffer[line_len - 1] != '1')
			{
				free(buffer);
				close_game("Map is not surrounded by walls", game, CLOSE_OTHERS);
			}
			if ((line_len) != game->map.horizontal_tiles)
			{
				free(buffer);
				close_game("Map is not rectangular", game, CLOSE_OTHERS);
			}
		}
		if (!ft_is_string_char_set(buffer, game->map.types))
		{
			free(buffer);
			close_game("Invalid map char", game, CLOSE_OTHERS);
		}
		add_new_node(game, buffer);
		line_count++;
	}
	last_row = last_node(game->map.list);
	if (!ft_is_string_char_set(last_row->content, "1"))
		close_game("Last row must be made only by walls", game, CLOSE_OTHERS);
	game->map.vertical_tiles = line_count;
	// print_list_values(game->map.list);
	// close(file_fd); //see best way to handle it
	//Scenario of empty file
	//Error if there's no player
}

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2 || !argv || !argv[0] || !argv[1])
		close_game("Invalid game arguments", NULL, CLOSE_OTHERS);
	if (!check_extension(argv[1]))
		close_game("Map file must be .ber type", NULL, CLOSE_OTHERS);
	game.mlx_ptr = NULL;
	game.window = NULL;
	game.grid = NULL; //Fix this shit later
	game.images.player = NULL;
	game.images.background = NULL;
	game.images.wall = NULL;
	build_map(&game, argv[1]);
	start_graphics(&game);
	start_images(&game);
	grid_creation(&game);
	mlx_key_hook(game.window, key_press, &game);
	mlx_loop(game.mlx_ptr);
	close_game(NULL, &game, CLOSE_SUCCESS);
}

	// new_tile->type = game->map.list->content[i];

	// if (new_tile->x_grid == 0 && new_tile->y_grid == 0) //Temporary code while we dont have a map
	// {
	// 	new_tile->type = copy_pointer[i];
	// 	new_tile->image = game->images.player;
	// 	game->player.tile = new_tile;
	// }
	// else
	// {
	// 	new_tile->image = game->images.background;
	// 	new_tile->type = '0';
	// }

	// new_tile->image = image_creation(game, new_tile);
	// mlx_put_image_to_window(game->mlx_ptr, game->window, new_tile->image, x * TILE_WIDTH, y * TILE_HEIGHT);
	//Create separate function to do a loop of assigning the tile type, assigning the image and putting on window

// void	pixel_put(t_image *image, int x_axis, int y_axis, unsigned int color)
// {
// 	char	*pixel;

// 	if (!image)
// 		close_game("Error on pixel_put call", NULL, CLOSE_FAILURE);
// 	pixel = NULL;
// 	pixel = image->address;
// 	pixel += y_axis * image->line_lenght;
// 	pixel += x_axis * image->bytes_per_pixel;
// 	*(unsigned int *)pixel = color;
// }

// void	pixel_fill(t_image *image, t_game *game, t_tile *new_tile)
// {
// 	int				x_axis;
// 	int				y_axis;
// 	unsigned int	color;

// 	if (!image || !game || !new_tile)
// 		close_game("Error on pixel_fill call", NULL, CLOSE_FAILURE);
// 	if (new_tile->type == '0') //Check how to properly handle this later
// 		color = 0x00FFFFFF;
// 	else //if (new_tile->type == 'P')
// 		color = 0x00FF0000;
// 	y_axis = 0;
// 	while (y_axis < TILE_HEIGHT)
// 	{
// 		x_axis = 0;
// 		while (x_axis < TILE_WIDTH)
// 		{
// 			pixel_put(image, x_axis, y_axis, color);
// 			x_axis++;
// 		}
// 		y_axis++;
// 	}
// }

// void	*image_creation(t_game *game, t_tile *new_tile)
// {
// 	t_image	new_image;

// 	if (!game || !new_tile)
// 		close_game("Error on image_creation call", NULL, CLOSE_FAILURE);
// 	new_image.image_ptr = NULL;
// 	new_image.address = NULL;
// 	new_image.image_ptr = mlx_new_image(game->mlx_ptr, TILE_WIDTH, TILE_HEIGHT);
// 	if (!new_image.image_ptr)
// 		close_game("Failure creating new img", game, CLOSE_FAILURE);
// 	new_image.address = mlx_get_data_addr(new_image.image_ptr, &new_image.bits_per_pixel, &new_image.line_lenght, &new_image.endian);
// 	if (!new_image.address)
// 		close_game("Failure creating img address", game, CLOSE_FAILURE);
// 	new_image.bytes_per_pixel = (new_image.bits_per_pixel / 8);
// 	pixel_fill(&new_image, game, new_tile);
// 	return (new_image.image_ptr);
// }

// void	new_tile_coordinates(t_game *game, t_tile *tile, int x, int y) //Check if will be really necessary
// {
// 	if (x < (game->horizontal_tiles - 1))
// 		tile->right_tile = game->grid[y][x + 1];
// 	if (x > 0)
// 		tile->left_tile = game->grid[y][x - 1];
// 	if (y > 0)
// 		tile->up_tile = game->grid[y - 1][x];
// 	if (y < (game->vertical_tiles - 1))
// 		tile->down_tile = game->grid[y + 1][x];
// }

/*

Objectives:
1 - Initialize connection, window, etc.
2 - Put some shit on screen
3 - On ESC key, close program
4 - 
5 - 

Backlog: 
- Map and map structure
- Player
- Collectibles
- Usar mlx_get_screen_size para entender melhor como estruturar a parada, sepa jogo do tamanho da tela?
- mlx_hook(game.window, DestroyNotify, StructureNotifyMask, close_game_success, &game);
- If game is too much big for the current screen, display error
- Game file must be compatible with the map size. If map is 10 x 5, then stuff should be 10 x 64 (640) and 5 x 64 (320)

	//int	check_errors; map, argc, argv, etc.
	// if (argc != 2)
	// 	return (EXIT_FAILURE);

*/