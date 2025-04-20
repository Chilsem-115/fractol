#include "fractol.h"

static void	setup_state(t_state *state, int argc, char **argv)
{
	if (!ft_strncmp(argv[1], "mandelbrot", 11))
	{
		state->fractal_type = FRACTAL_MANDELBROT;
		state->c = (t_complex){0, 0};
		state->zoom = 0.8f;
	}
	else if (!ft_strncmp(argv[1], "julia", 6) && argc == 4)
	{
		state->fractal_type = FRACTAL_JULIA;
		state->c.r = ft_atodb(argv[2]);
		state->c.i = ft_atodb(argv[3]);
		state->zoom = 1.0f;
	}
	else
	{
		ft_dprintf(2, ERROR_MESSAGE);
		exit(EXIT_FAILURE);
	}
	state->max_iteration = MAX_ITER;
	state->off_x = 0.0f;
	state->off_y = 0.0f;
	state->win.name = argv[1];
}

static int	validate_input(int argc, char **argv)
{
    if ((argc == 2 && !ft_strncmp(argv[1], "mandelbrot", 11))
        || (argc == 4 && !ft_strncmp(argv[1], "julia", 6)
            && is_valid_double(argv[2])
            && is_valid_double(argv[3])))
        return (1);
    return (0);
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
	
	if (validate_input(argc, argv))
	{
		setup_state(&state, argc, argv);
		init_window(&state);
		mlx_hook(state.win.mlx_window, ON_KEYDOWN, KEY_PRESS_MASK, keypress_handler, &state);
        mlx_hook(state.win.mlx_window, ON_DESTROY, 0, close_handler, &state);
		mlx_mouse_hook(state.win.mlx_window, mouse_handler, &state);
		render_fractal(&state);
		mlx_loop(state.win.mlx_connection);
	}
	else
	{
		ft_dprintf(2, ERROR_MESSAGE JULIA_EXAMPLES);
		exit(EXIT_FAILURE);
	}
}
