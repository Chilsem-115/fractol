#include "fractol.h"

int	get_color(int n, int max_iter)
{
	double	t;
	int		r;
	int		g;
	int		b;

	if (n == max_iter)
		return	(0x000000);
	t = (double)n / max_iter;
	r = (int)(9 * (1 - t) * t * t * t * 255);
	g = (int)(15 * (1 - t) * (1 - t) * t * t * 255);
	b = (int)(8.5 * (1 - t) * (1 - t) * (1 - t) * t * 255);
	return ((r << 16) | (g << 8) | b);
}
