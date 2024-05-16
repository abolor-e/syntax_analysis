#include "../minishell.h"
#include "../gnl.h"

static int	ft_fill_buffer_until_n(char **bufline, int fd)
{
	char	*buf;
	int		linelen;
	int		ret;

	buf = (char *)malloc(sizeof(*buf) * (BUFFER_SIZE + 1));
	if (!buf)
		return (-1);
	while (!ft_strchr(*bufline, '\n'))
	{
		ret = read(fd, buf, BUFFER_SIZE);
		if (ret == 0 || ret == -1)
		{
			free(buf);
			return (ret);
		}
		buf[ret] = '\0';
		linelen = (ft_strchr(*bufline, 0) - *bufline) + ret + 1;
		*bufline = ft_realloc(*bufline, linelen);
		ft_strlcat(*bufline, buf, linelen);
	}
	free(buf);
	return (1);
}

static int	ft_update_bufline(char **bufline)
{
	char	*tofree;
	int		nl_index;

	tofree = *bufline;
	nl_index = ft_strchr(*bufline, '\n') - *bufline;
	*bufline = ft_substr(*bufline, nl_index + 1, \
		(ft_strchr(*bufline, 0) - *bufline) - (nl_index + 1));
	if (!*bufline)
	{
		*bufline = tofree;
		return (-1);
	}
	free(tofree);
	return (0);
}

static int	ft_return_line(char **line, char **bufline, int status)
{
	int		nl_index;

	if (status == -1)
		return (-1);
	if (status == 0)
	{
		*line = ft_substr(*bufline, 0, ft_strchr(*bufline, 0) - *bufline);
		if (!*line)
			return (-1);
		return (0);
	}
	else
	{
		nl_index = ft_strchr(*bufline, '\n') - *bufline;
		*line = ft_substr(*bufline, 0, nl_index);
		if (!*line)
			return (-1);
		if (ft_update_bufline(bufline) == -1)
			return (-1);
		return (1);
	}
}

static int	ft_init_bufline(char **bufline)
{
	if (!*bufline)
	{
		*bufline = (char *)malloc(sizeof(**bufline) * (BUFFER_SIZE + 1));
		if (!*bufline)
			return (-1);
		*bufline[0] = 0;
	}
	return (0);
}

int	ft_get_next_line(int fd, char **line, int to_free)
{
	static char	*bufline = NULL;
	int			result;

	if (to_free)
	{
		free(bufline);
		return (0);
	}
	if (fd < 0 || !line || BUFFER_SIZE <= 0 || ft_init_bufline(&bufline) == -1)
		return (-1);
	result = ft_fill_buffer_until_n(&bufline, fd);
	if (ft_return_line(line, &bufline, result) == -1)
	{
		free(bufline);
		bufline = NULL;
		return (-1);
	}
	if (result == 0)
	{
		free(bufline);
		bufline = NULL;
	}
	return (result);
}

char	*ft_strchr(const char *s, int c)
{
	if (!s)
		return (NULL);
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		++s;
	}
	if (c == 0)
		return ((char *)s);
	return (NULL);
}

void	*ft_realloc(void *ptr, size_t size)
{
	char	*new;

	if (!ptr || size == 0)
	{
		if (size == 0)
			size = 1;
		new = (char *)malloc(sizeof(*new) * size);
		if (!new)
		{
			free(ptr);
			return (NULL);
		}
		return (new);
	}
	new = (char *)malloc(sizeof(*new) * size);
	if (!new)
	{
		free(ptr);
		return (NULL);
	}
	new = ft_strcpy(new, ptr);
	free(ptr);
	return (new);
}

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	s_len;
	size_t	d_len;
	size_t	i;
	size_t	result;

	i = 0;
	s_len = ft_strlen(src);
	d_len = ft_strlen(dst);
	if (dstsize >= d_len)
		result = s_len + d_len;
	else
		result = s_len + dstsize;
	if (dstsize > d_len)
	{
		while (src[i] && d_len < dstsize - 1)
		{
			dst[d_len] = src[i];
			++d_len;
			++i;
		}
	}
	dst[d_len] = '\0';
	return (result);
}

char	*ft_strcpy(char *dst, const char *src)
{
	size_t	i;

	i = -1;
	if (!src)
	{
		dst[0] = 0;
		return (dst);
	}
	while (src[++i])
		dst[i] = src[i];
	dst[i] = '\0';
	return (dst);
}