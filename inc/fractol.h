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

#define WIDTH	1200
#define HEIGHT	1200

#define BLACK	0x000000
#define WHITE	0xFFFFFF
#define RED		0xFF0000
#define GREEN	0x00FF00
#define BLUE	0x0000FF

#define ESC_KEY 65307

/* for storing the fractal type */

typedef enum e_fractal_type
{
	FRACTAL_MANDELBROT,
	FRACTAL_JULIA
}	t_fractal_type;

/* used as a variable type for storing complex numbers */

typedef struct	s_complex
{
	float	r;
	float	i;
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
	long			max_iteration;
	float			off_x;
	float			off_y;
	float			zoom;
	t_complex		c;
	t_fractal_type	fractal_type;
}					t_state;

/* utilities */
size_t	ft_strlen(const char *str);
int		ft_atoi(const char *str);
int		ft_strncmp(char *s1, char *s2, int n);
float	ft_atof(const char *str);

/* compute functions */
t_complex	new_complex(float real, float imag);
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
