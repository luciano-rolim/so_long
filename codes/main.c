/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeneghe <lmeneghe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 20:13:27 by lmeneghe          #+#    #+#             */
/*   Updated: 2024/07/10 23:07:48 by lmeneghe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"
// #include "mlx/mlx.h"
// #include <stdlib.h>


void initialization()
{




}

int main(int argc, char **argv)
{


	void *mlx_ptr;
	void *win_ptr;

	mlx_ptr = NULL;
	win_ptr = NULL;

	write(1, "u\n", 2);
	printf("%p\n", mlx_ptr);
	mlx_ptr = mlx_init();
	printf("%p\n", mlx_ptr);
	if (!mlx_ptr)
		return (EXIT_FAILURE);
	printf("%p\n", win_ptr);
	win_ptr = mlx_new_window(mlx_ptr, 600, 400, "hi :)");
	printf("%p\n", win_ptr);
	if (!win_ptr)
	{
		write(2, "jajaja\n", 7);
		return (free(mlx_ptr), 1);
	}
	sleep(5);
	// mlx_loop(mlx_ptr);

	// // mlx_destroy_window(mlx_ptr, win_ptr);
	// // mlx_destroy_display(mlx_ptr);
	// free(mlx_ptr);
	// return (0);
}
