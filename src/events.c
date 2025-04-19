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
	else if (keysym == XK_plus)
		state->max_iteration += 10;
	else if (keysym == XK_minus)
		state->max_iteration -= 10;
	render_fractal(state);
	return (0);
}

int	mouse_handler(int button, int x, int y, t_state *st)
{
	t_complex	mouse_pos;
	double		zoom_factor;

	if (button == 4 || button == 5)
	{
		mouse_pos = pixel_to_complex(x - WIDTH / 2, HEIGHT / 2 - y, st);
		if (button == 4)
			zoom_factor = 1.5;
		else
			zoom_factor = 0.6;
		st->zoom *= zoom_factor;
		st->off_x = mouse_pos.r + (st->off_x - mouse_pos.r) / zoom_factor;
		st->off_y = mouse_pos.i + (st->off_y - mouse_pos.i) / zoom_factor;
		render_fractal(st);
	}
	return (0);
}

int	close_handler(t_state *state)
{
    panic_exit(1, NULL, state);
	return (0);
}
