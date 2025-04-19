#include "fractol.h"

void	init_window(t_state *state)
{
	t_win	*window;

	window = &state->win;
	window->mlx_connection = mlx_init();
	if (!window->mlx_connection)
		panic_exit(2, "Error", state);
	window->mlx_window = mlx_new_window(window->mlx_connection, WIDTH, HEIGHT, window->name);
	if (!window->mlx_window)
		panic_exit(2, "Error", state);
	window->img.img_ptr = mlx_new_image(window->mlx_connection, WIDTH, HEIGHT);
	if (!window->img.img_ptr)
		panic_exit(2, "Error", state);
	window->img.addr = mlx_get_data_addr(
			window->img.img_ptr,
			&window->img.bpp,
			&window->img.line_len,
			&window->img.endian
			);
	if (!window->img.addr)
		panic_exit(2, "Error", state);
}
