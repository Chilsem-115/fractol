#include "fractol.h"

/*
 * this function is for computing the next element for the number
 */
static t_complex	compute_next(t_complex current, t_complex constant)
{
	float		zr;
	float		zi;

	zr = current.r * current.r - current.i * current.i;
	zi = 2.0 * current.r * current.i;
	return (new_complex(zr + constant.r, zi + constant.i));
}

/*
 * returns the mod squared
 */
static float	mod2(t_complex z)
{
	return (z.r * z.r + z.i * z.i);
}

/*
 * set and return the complex value
 */
t_complex	new_complex(float real, float imag)
{
	t_complex	c;
	c.r = real;
	c.i = imag;
	return (c);
}

/*
 * computes the sequence of elements until mod exceeds threshold or max iteration is reached
 */
int	compute_iteration(t_complex z0, t_complex constant, int max_iteration)
{
	t_complex	zn;
	int			iteration;

	zn = z0;
	iteration = 0;
	while (mod2(zn) < 4.0f && iteration < max_iteration)
	{
		zn = compute_next(zn, constant);
		iteration++;
	}
	return (iteration);
}
