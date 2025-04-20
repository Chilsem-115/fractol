#include "fractol.h"

size_t	ft_strlen(const char *str)
{
	int	x;

	x = 0;
	while (str[x])
		x++;
	return (x);
}


int	ft_strncmp(char *s1, char *s2, int n)
{
	if (NULL == s1 || NULL == s2 || n <= 0)
		return (0);
	while (*s1 == *s2 && n > 0 && *s1 != '\0')
	{
		++s1;
		++s2;
		--n;
	}
	return (*s1 - *s2);
}

double	ft_atodb(const char *str)
{
	double	int_part;
	double	dec_part;
	double	sign;
	int		i;

	int_part = 0.0;
	dec_part = 0.0;
	sign = 1.0;
	if (*str == '+' || *str == '-')
		if (*str++ == '-')
			sign = -1.0;
	while (*str >= '0' && *str <= '9')
		int_part = int_part * 10 + (*str++ - '0');
	i = -1;
	if (*str == '.' && *str++)
	{
		while (*str >= '0' && *str <= '9')
			dec_part += (pow(10, i--) * (*str++ - '0'));
	}
	return (sign * (int_part + dec_part));
}
/*
double	ft_atodb(const char *str)
{
	double	res;
	double	res2;
	const char	*tmp;
	int		len;
	
	tmp = str;
	res = ft_atoi(tmp);
	while(*tmp && *tmp != '-')
		tmp++;
	if (*tmp == '.')
		tmp++;
	res2 = ft_atoi(tmp);
	len = ft_strlen(tmp);
	while (len--)
		res2 /= 10;
	if (res >= 0)
		return (res + res2);
	else
		return (res + -res2);
}
*/
