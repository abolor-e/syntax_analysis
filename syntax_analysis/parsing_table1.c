// #include "../minishell.h"

// static int	ms_free_line_args(char *line, char **args, int code)
// {
// 	char	**begin;

// 	if (line)
// 		free(line);
// 	if (args)
// 	{
// 		begin = args;
// 		while (*args)
// 		{
// 			free(*args);
// 			++args;
// 		}
// 		free(begin);
// 	}
// 	return (code);
// }

// static t_table	*ms_new_transition(char **args)
// {
// 	t_table	*new;

// 	if (!args)
// 		return (NULL);
// 	new = (t_table *)malloc(sizeof(*new));
// 	if (!new)
// 		return (NULL);
// 	new->state = ft_atoi(args[0]);
// 	new->token_type = ft_atoi(args[1]);
// 	new->action = ft_atoi(args[2]);
// 	new->next_state = ft_atoi(args[3]);
// 	new->nb_reduce = ft_atoi(args[4]);
// 	return (new);
// }

// void	ms_free_table(t_table **trans)
// {
// 	t_table	**begin;

// 	if (trans)
// 	{
// 		begin = trans;
// 		while (*trans)
// 		{
// 			free(*trans);
// 			++trans;
// 		}
// 		free(begin);
// 	}
// }

// int	ms_create_all_transitions(int fd, t_table **trans)
// {
// 	int		i;
// 	int		ret;
// 	char	*line;
// 	char	**args;

// 	line = NULL;
// 	ret = ft_get_next_line(fd, &line, 0);
// 	i = -1;
// 	while (ret >= 0)
// 	{
// 		args = ft_split(line, 9);
// 		trans[++i] = ms_new_transition(args);
// 		ms_free_line_args(line, args, 0);
// 		line = NULL;
// 		if (!trans[i])
// 			return (-1);
// 		if (ret == 0)
// 			break ;
// 		ret = ft_get_next_line(fd, &line, 0);
// 	}
// 	if (ret == -1)
// 		return (-1);
// 	return (0);
// }

// t_table	**ms_init_parsing_table(void)
// {
// 	int		fd;
// 	t_table	**trans;

// 	trans = (t_table **)malloc(sizeof(*trans) * (100 + 1));
// 	if (!trans)
// 		return (NULL);
// 	trans[0] = NULL;
// 	trans[100] = NULL;
// 	fd = open(BISON_AUTOMATON, O_RDONLY);
// 	if (fd == -1)
// 	{
// 		ms_free_table(trans);
// 		return (NULL);
// 	}
// 	if (ms_create_all_transitions(fd, trans) == -1)
// 	{
// 		ms_free_table(trans);
// 		close(fd);
// 		return (NULL);
// 	}
// 	close(fd);
// 	int i = 0;
// 	while (trans[i])
// 	{
// 		printf("%d, %d, %d, %d, %d\n", trans[i]->state, trans[i]->token_type, trans[i]->action, trans[i]->next_state, trans[i]->nb_reduce);
// 		i++;
// 	}
// 	return (trans);
// }