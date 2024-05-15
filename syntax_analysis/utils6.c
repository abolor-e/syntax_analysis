#include "../minishell.h"

static size_t	ft_slen(const char *s, char c)
{
	size_t	ret;

	ret = 0;
	while (*s)
	{
		if (*s != c)
		{
			++ret;
			while (*s && *s != c)
				++s;
		}
		else
			++s;
	}
	return (ret);
}

char	**ft_free(char **split_array)
{
	size_t	i;

	i = 0;
	while (split_array[i] != 0)
	{
		free(split_array[i]);
		i++;
	}
	free(split_array);
	return (0);
}

char	**ft_split(const char *s, char c)
{
	char	**res;
	size_t	i;
	size_t	a;
	size_t	b;

	i = 0;
	b = 0;
	if (!s)
		return (0);
	res = malloc(sizeof(char *) * (ft_slen(s, c) + 1));
	if (!res)
		return (NULL);
	while (b < ft_slen(s, c))
	{
		while (s[i] == c && s[i] != 0)
			i++;
		a = i;
		while (s[i] != c && s[i] != 0)
			i++;
		res[b] = ft_substr(s, a, i - a);
		if (res[b++] == NULL)
			return (ft_free(res));
	}
	res[ft_slen(s, c)] = 0;
	return (res);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	s;
	int	res;

	s = 1;
	i = 0;
	res = 0;
	while (str[i] == '\n' || str[i] == '\t' || str[i] == ' '
		|| str[i] == '\v' || str[i] == '\f' || str[i] == '\r')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			s = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = (res * 10) + (str[i] - '0');
		i++;
	}
	return (res * s);
}

char	*ft_substr(char const *s, int start, size_t len)
{
	char	*dest;
	size_t	nlen;

	if (!s)
		return (NULL);
	if (start > ft_strlen(s))
	{
		dest = ft_calloc(1, sizeof(char));
		if (!dest)
			return (NULL);
	}
	else
	{
		nlen = ft_strlen(s + start);
		if (!(nlen < len))
			nlen = len;
		dest = (char *)malloc(sizeof(char) * (nlen + 1));
		if (!dest)
			return (NULL);
		dest[nlen] = 0;
		while (nlen-- > 0)
			dest[nlen] = s[start + nlen];
	}
	return (dest);
}

void	*ft_calloc(size_t count, size_t size)
{
	size_t	i;
	void	*res;
	char	*temp;

	res = NULL;
	res = malloc(count * size);
	if (!res)
		return (NULL);
	temp = res;
	i = 0;
	while (i < count * size)
		temp[i++] = 0;
	return (res);
}