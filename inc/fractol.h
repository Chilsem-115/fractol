#ifndef FRACTOL_H
# define FRACTOL_H

# include <stdlib.h>
# include <unistd.h>
# include <math.h>
# include <X11/X.h>
# include <X11/keysym.h>
# include "mlx.h"
# include "ft_printf.h"

#define ERROR_MESSAGE "How to use:\n\t~ ./fractol mandelbrot\n\t~ ./fractol julia <real_value> <imaginary_value>\n"
#define JULIA_EXAMPLES "Examples:\n\t~ ./fractol julia -0.4 0.6\n\t~ ./fractol julia 0.285 0.01\n\t~ ./fractol julia -0.8 0.156\n"

/* fractal types */
#define FRACTAL_MANDELBROT 0
#define FRACTAL_JULIA 1

/* Event macros */
#define ON_KEYDOWN 2
#define ON_DESTROY 17
#define KEY_PRESS_MASK (1L << 0)

#define WIDTH		1200
#define HEIGHT		1200
#define	MAX_ITER	100

#define ESC_KEY 65307

/* used as a variable type for storing complex numbers */

typedef struct	s_complex
{
	double	r;
	double	i;
}			t_complex;

/*
 * image
 * this would be used for pixels buffer
 */

typedef struct	s_img
{
	void	*img_ptr;
	char	*addr;
	int		bpp;
	int		endian;
	int		line_len;
}			t_img;

/* Window/context for MLX */

typedef struct	s_win
{
	char	*name;
	void	*mlx_connection;
	void	*mlx_window;
	t_img	img;
}			t_win;

/*
 *	Global state of the program.
 *	this will hold everything that the program produces.
 */

typedef struct	s_state
{
	t_win			win;
	int				fractal_type;
	long			max_iteration;
	double			off_x;
	double			off_y;
	double			zoom;
	t_complex		c;
}					t_state;

/* utilities */
int	ft_isdigit(int c);
int	is_valid_double(const char *s);
size_t	ft_strlen(const char *str);
int	ft_strncmp(char *s1, char *s2, int n);
double	ft_atodb(const char *str);

/* compute functions */
t_complex	new_complex(double real, double imag);
int		compute_iteration(t_complex z0, t_complex constant, int max_iteration);

/* fractal rendering */
void		render_fractal(t_state *state);
int			get_color(int n, int max_iter);
t_complex	pixel_to_complex(int x, int y, t_state *st);

/* init window */
void	init_window(t_state *state);

/* events */
void	panic_exit(int fd, const char *msg, t_state *state);
int		keypress_handler(int keysym, t_state *state);
int		close_handler(t_state *state);
int		mouse_handler(int button, int x, int y, t_state *st);

#endif
