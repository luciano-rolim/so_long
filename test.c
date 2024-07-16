
int main(int argc, char **argv)
{
	void*	mlx_start;
	void*	mlx_window;

	//Create protection for appropriate number of files + againt NULL argv or NULL argv[0]
	mlx_start = mlx_init();
	if (!mlx_start)
		return (EXIT_FAILURE);
	mlx_window = mlx_new_window(mlx_start, 600, 400, "Custom Pac-Man");
	if (!mlx_window)
		return (EXIT_FAILURE);
	sleep(5);
	return (EXIT_SUCCESS);
}

typedef struct	s_data {
	void	*img; //A pointer to the image
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

void	my_mlx_pixel_put(t_data *new_img, int x, int y, int color) //void function, does not return anything, only inser the pixels and etc.
{
	char	*dst;

	dst = NULL;
	dst = new_img->addr;
	dst += (y * new_img->line_length);
	dst += (x * (new_img->bits_per_pixel / 8));
	*(unsigned int*)dst = color;

}

int	main(void)
{
	void	*mlx;
	void	*mlx_win;
	t_data	new_img;

	new_img.img = NULL;
	new_img.addr = NULL;

	mlx = mlx_init(); //ok, começa a conexão
	mlx_win = mlx_new_window(mlx, 600, 400, "Hello world!"); //ok, abre a janela

	new_img.img = mlx_new_image(mlx, 600, 400); //Inicia uma imagem de acordo com o tamanho especificado

	new_img.addr = mlx_get_data_addr(new_img.img, &new_img.bits_per_pixel, &new_img.line_length, &new_img.endian);

	my_mlx_pixel_put(&new_img, 5, 5, 0x00FF10F0);
	// my_mlx_pixel_put(&new_img, 5, 5, 0xFFFFFFFFF);
	// my_mlx_pixel_put(&new_img, 6, 6, 0x00FF0000);
	mlx_put_image_to_window(mlx, mlx_win, new_img.img, 0, 0); //Insere a imagem. Precisa da conexão, janela, imagem e eixos x e y
	sleep(6);
}

///////////////////////////////

typedef struct s_data
{
	void *img; // A pointer to the image
	char *addr;
	int bits_per_pixel;
	int line_length;
	int endian;
} t_data;

void my_mlx_pixel_put(t_data *new_img, int x, int y, int color) // void function, does not return anything, only inser the pixels and etc.
{
	char *dst;
	dst = NULL;
	dst = new_img->addr;
	dst += (y * new_img->line_length);
	dst += (x * (new_img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int main(void)
{
	void *mlx;
	void *mlx_win;
	t_data new_img;
	int width;
	int height;
	int test_width;
	int test_height;
	t_data second_img;

	new_img.img = NULL;
	new_img.addr = NULL;

	mlx = mlx_init(); // ok, começa a conexão
	width = 600;
	height = 400;
	mlx_win = mlx_new_window(mlx, width, height, "Hello world!"); // ok, abre a janela
	new_img.img = mlx_new_image(mlx, width, height);			  // Inicia uma imagem de acordo com o tamanho especificado
	new_img.addr = mlx_get_data_addr(new_img.img, &new_img.bits_per_pixel, &new_img.line_length, &new_img.endian);
	test_height = 0;
	while (test_height < height)
	{
		test_width = 0;
		while (test_width < width)
		{
			my_mlx_pixel_put(&new_img, test_width, test_height, 0x00FFC0CB);
			test_width++;
		}
		test_height++;
	}
	mlx_put_image_to_window(mlx, mlx_win, new_img.img, 0, 0); // Insere a imagem. Precisa da conexão, janela, imagem e eixos x e y
	sleep(3);
	mlx_destroy_display(mlx);
	sleep(3);
	// int test = 99;
	// test = mlx_destroy_image(mlx, new_img.img);
	// printf("%i\n", test);
	// second_img.img = mlx_new_image(mlx, width, height); // Inicia uma imagem de acordo com o tamanho especificado
	// second_img.addr = mlx_get_data_addr(second_img.img, &second_img.bits_per_pixel, &second_img.line_length, &second_img.endian);
	// test_height = 0;
	// while (test_height < height)
	// {
	// 	test_width = 0;
	// 	while (test_width < width)
	// 	{
	// 		my_mlx_pixel_put(&second_img, test_width, test_height, 0x00FF0000);
	// 		test_width++;
	// 	}
	// 	test_height++;
	// }
	// mlx_put_image_to_window(mlx, mlx_win, second_img.img, 0, 0); // Insere a imagem. Precisa da conexão, janela, imagem e eixos x e y
	// sleep(3);
	// mlx_destroy_display(mlx);
	// mlx_put_image_to_window(mlx, mlx_win, new_img.img, 0, 0); // Insere a imagem. Precisa da conexão, janela, imagem e eixos x e y
	// sleep(3);
}

///////////////////////////////

#include <X11/keysym.h>

typedef struct s_vars {
    void *mlx;
    void *win;
} t_vars;

int handle_keypress(int keycode, t_vars *vars) {
    // Check if the ESC key was pressed
    if (keycode == XK_Escape) {
        mlx_destroy_window(vars->mlx, vars->win);
        exit(0); // Close the program
    }
    return (0);
}

int main(void)
{
    t_vars vars;

    vars.mlx = mlx_init();
    vars.win = mlx_new_window(vars.mlx, 600, 400, "Press ESC to close");

    // Set up key press event handler. THIS IS THE IMPORTANT PART.
    mlx_hook(vars.win, 2, 1L<<0, handle_keypress, &vars);

    mlx_loop(vars.mlx);
	sleep(5);
    return (0);
}

#include <stddef.h>

static int cb() {
  return 0;
}

int main() {
  void *mlx = mlx_init();
  void *win = mlx_new_window(mlx, 800, 600, "Hello, world!");
  (void)win;
  mlx_loop_hook(mlx, cb, NULL);
  mlx_hook()
  mlx_loop(mlx);
  return 0;
}t_mask.o obj/mlx_hook.o obj/mlx_rgb.o obj/mlx_destroy_image.o obj/mlx_mouse.o obj/mlx_screen_size.o obj/mlx_destroy_display.o
