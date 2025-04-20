#include "fractol.h"

/*
 * computes the pixel location and prints out the pixel based on the desired location.
 */
static void	put_pixel(t_img *img, int x, int y, int color)
{
	int		screen_x;
	int		screen_y;
	char	*dst;
	screen_x = (WIDTH / 2) + x;
	screen_y = (HEIGHT / 2) - y;

	if (screen_x >= 0 && screen_x < WIDTH && screen_y >= 0 && screen_y < HEIGHT)
	{
		dst = img->addr + (screen_y * img->line_len + screen_x * (img->bpp / 8));
		*(unsigned int *)dst = color;
	}
}

/*
 * Map a pixel at (x,y) — where (0,0) is the center —
 * into the complex plane, applying zoom and offset.
 */
t_complex	pixel_to_complex(int x, int y, t_state *st)
{
    float	norm_x;
    float	norm_y;
    float	real;
	float	imag;

	norm_x = (WIDTH/2 + x) / (float)WIDTH;
	norm_y = (HEIGHT/2 - y) / (float)HEIGHT;
    if (st->fractal_type == FRACTAL_MANDELBROT)
    {
        real = -2.5f + norm_x * (1.0f + 2.5f);
        imag =  1.0f - norm_y * (2.0f);
    }
    else if(st->fractal_type == FRACTAL_JULIA)
    {
        real = -2.0f + norm_x * 4.0f;
        imag =  2.0f - norm_y * 4.0f;
    }
    real = (real - st->off_x) / st->zoom + st->off_x;
    imag = (imag - st->off_y) / st->zoom + st->off_y;
    return (new_complex(real, imag));
}

static void	render_mandelbrot(t_state *state)
{
	t_complex	z0;
	int			x;
	int			y;
	int			n;

	y = -HEIGHT / 2;
	while (y < HEIGHT / 2)
	{
		x = -WIDTH / 2;
		while (x < WIDTH / 2)
		{
			z0 = pixel_to_complex(x, y, state);
			n = compute_iteration(new_complex(0, 0), z0, state->max_iteration);
			put_pixel(&state->win.img, x, y, get_color(n, state->max_iteration));
			x++;
		}
		y++;
	}
}

static void	render_julia(t_state *state)
{
	t_complex	z0;
	int			x;
	int			y;
	int			n;

	y = -HEIGHT / 2;
	while (y < HEIGHT / 2)
	{
		x = -WIDTH / 2;
		while (x < WIDTH / 2)
		{
			z0 = pixel_to_complex(x, y, state);
			n = compute_iteration(z0, state->c, state->max_iteration);
			put_pixel(&state->win.img, x, y, get_color(n, state->max_iteration));
			x++;
		}
		y++;
	}
}

/*
 * the function responsible for calculating each pixel on the screen.
 * and deciding which ones to draw and which to leave out.
 */
void render_fractal(t_state *state)
{
	if (state->fractal_type == FRACTAL_MANDELBROT)
		render_mandelbrot(state);
	else if (state->fractal_type == FRACTAL_JULIA)
		render_julia(state);
    mlx_put_image_to_window(state->win.mlx_connection,
                            state->win.mlx_window,
                            state->win.img.img_ptr,
                            0, 0);
}
