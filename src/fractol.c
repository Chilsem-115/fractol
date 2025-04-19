#include "fractol.h"

static void	setup_state(t_state *state, int argc, char **argv)
{
	if (!ft_strncmp(argv[1], "mandelbrot", 11))
	{
		state->fractal_type = FRACTAL_MANDELBROT;
		state->c = (t_complex){0, 0};
	}
	else if (!ft_strncmp(argv[1], "julia", 6) && argc == 4)
	{
		state->fractal_type = FRACTAL_JULIA;
		state->c.r = atof(argv[2]);
		state->c.i = atof(argv[3]);
	}
	else
	{
		ft_dprintf(2, ERROR_MESSAGE);
		exit(EXIT_FAILURE);
	}
	state->max_iteration = 100;
	state->zoom = 1.0f;
	state->off_x = 0.0f;
	state->off_y = 0.0f;
	state->win.name = argv[1];
}

/*
 *	How to use:
 * 		~ ./fractol mandelbrot
 * 		~ ./fractol julia <real_value> <imaginary_value>
 *
 */

int	main(int argc, char **argv)
{
	t_state		state;
	
	if ((argc == 2 && !ft_strncmp(argv[1], "mandelbrot", 11))
			|| (argc == 4 && !ft_strncmp(argv[1], "julia", 6)))
	{
		setup_state(&state, argc, argv);
		init_window(&state);
		mlx_hook(state.win.mlx_window, 2, 1L << 0, keypress_handler, &state);
        mlx_hook(state.win.mlx_window, 17, 0, close_handler, &state);
		mlx_mouse_hook(state.win.mlx_window, mouse_handler, &state);
		render_fractal(&state);
		mlx_loop(state.win.mlx_connection);
	}
	else
	{
		ft_dprintf(2, ERROR_MESSAGE);
		exit(EXIT_FAILURE);
	}
}
