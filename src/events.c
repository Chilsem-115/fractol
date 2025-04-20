#include "fractol.h"

void	panic_exit(int fd, const char *msg, t_state *state)
{
	t_win	*window;

	window = &state->win;
	if (window->img.img_ptr && window->mlx_connection)
		mlx_destroy_image(window->mlx_connection, window->img.img_ptr);
	if (window->mlx_window && window->mlx_connection)
		mlx_destroy_window(window->mlx_connection, window->mlx_window);
	if (window->mlx_connection)
	{
		mlx_destroy_display(window->mlx_connection);
		free(window->mlx_connection);
	}
	if (!(msg == NULL))
		ft_dprintf(fd, "%s\n", msg);
	exit(EXIT_FAILURE);
}

int	keypress_handler(int keysym, t_state *state)
{
	if (keysym == XK_Escape)
		panic_exit(1, NULL, state);
	render_fractal(state);
	return (0);
}

int	mouse_handler(int button, int x, int y, t_state *state)
{
	(void)x;
	(void)y;
	if (button == 4)
		state->zoom *= 1.5;
	else if (button == 5)
		state->zoom *= 0.6;
	render_fractal(state);
	return (0);
}

int	close_handler(t_state *state)
{
    panic_exit(1, NULL, state);
	return (0);
}
