#include "fractol.h"

int	get_color(int n, int max_iter)
{
	float	t;
	int		r;
	int		g;
	int		b;

	if (n == max_iter)
		return 0x000000;
	t = (float)n / max_iter;
	r = (int)(9 * (1 - t) * t * t * t * 255);
	g = (int)(15 * (1 - t) * (1 - t) * t * t * 255);
	b = (int)(8.5 * (1 - t) * (1 - t) * (1 - t) * t * 255);
	return ((r << 16) | (g << 8) | b);
}

/*
int	get_color(int n, int max_iter)
{
	float	t;
	int		intensity;

	if (n == max_iter)
		return (0xFFFFFF); // Inside the set = full white glow
	t = (float)n / max_iter;
	intensity = (int)(255 * pow(t, 3)); // low for early escape, brightens slowly
	return ((intensity << 16) | (intensity << 8) | intensity);
}
*/
