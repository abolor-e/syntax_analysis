#include "../minishell.h"

int	ft_digits(int n)
{
	int	i;

	i = 0;
	if (n == 0)
		return (1);
	while (n != 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	char		*res;
	long int	i;
	int			digits;

	i = n;
	digits = ft_digits(n);
	if (n < 0)
	{
		i *= -1;
		digits++;
	}
	res = (char *)malloc(sizeof(char) * (digits + 1));
	if (!res)
		return (NULL);
	*(res + digits) = 0;
	while (digits--)
	{
		*(res + digits) = i % 10 + '0';
		i = i / 10;
	}
	if (n < 0)
		*(res + 0) = '-';
	return (res);
}

char	*ft_strdup(const char *s1)
{
	int		len;
	int		i;
	char	*res;

	len = 0;
	i = 0;
	while (s1[len] != '\0')
	{
		len++;
	}
	res = (char *)malloc(sizeof(char) * (len + 1));
	if (!res)
		return (NULL);
	while (s1[i] != '\0')
	{
		res[i] = s1[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}

int	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

int	ft_isdigit(int c)
{
	int	a;

	a = 0;
	if (c > 47 && c < 58)
	{
		++a;
		return (a);
	}
	else
		return (0);
}