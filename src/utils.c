#include "fractol.h"

int	ft_isdigit(int c)
{
    return (c >= '0' && c <= '9');
}

int	is_valid_double(const char *s)
{
	int	i;
	int	has_digit;

	i = 0;
	has_digit = 0;
	if (s[i] == '+' || s[i] == '-')
		i++;
	while (s[i] && ft_isdigit(s[i]))
	{
		has_digit = 1;
		i++;
	}
	if (s[i] == '.' && ft_isdigit(s[i + 1]))
	{
		i += 2;
		has_digit = 1;
		while (s[i] && ft_isdigit(s[i]))
			i++;
	}
	if (!has_digit || s[i] != '\0')
		return (0);
	return (1);
}

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
	while (ft_isdigit(*str))
		int_part = int_part * 10 + (*str++ - '0');
	i = -1;
	if (*str == '.' && *str++)
	{
		while (ft_isdigit(*str))
			dec_part += (pow(10, i--) * (*str++ - '0'));
	}
	return (sign * (int_part + dec_part));
}
