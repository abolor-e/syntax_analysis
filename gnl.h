#ifndef GNL_H
# define GNL_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# elif BUFFER_SIZE != 1
#  undef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>
# include <limits.h>
# include <fcntl.h>

typedef struct s_list
{
	char			*str_buf;
	struct s_list	*next;
}				t_list;

// get_next_line functions!
char	*get_next_line(int fd);
void	create_buffer_list(t_list **list, int fd);
void	include_list(t_list **list, char *res);
char	*get_until_newline(t_list *list);
void	prep_for_next_line(t_list **list);
int		newline_check_list(t_list *list);
int		len_until_newline(t_list *list);
void	copy(t_list *list, char *new_str);
void	free_list(t_list **list, t_list *new_node, char *str);
t_list	*ft_lstlast(t_list *list);

#endif