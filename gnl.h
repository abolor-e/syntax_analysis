#ifndef GNL_H
# define GNL_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 32
# endif

# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>
# include <limits.h>
# include <fcntl.h>
# include <stddef.h>
# include <sys/types.h>
# include <sys/uio.h>

// get_next_line functions!
int	ft_get_next_line(int fd, char **line, int to_free);
static int	ft_init_bufline(char **bufline);
static int	ft_return_line(char **line, char **bufline, int status);
static int	ft_update_bufline(char **bufline);
static int	ft_fill_buffer_until_n(char **bufline, int fd);
char	*ft_strchr(const char *s, int c);
void	*ft_realloc(void *ptr, size_t size);
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);
char	*ft_strcpy(char *dst, const char *src);

#endif