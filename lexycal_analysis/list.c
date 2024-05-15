#include "../minishell.h"

t_ttypes	catego_toketype(char *content, int c)
{
	if (!content)
		return (T_END);
	if (!ft_strcmp(content, "|") && !c)
		return (T_PIPE);
	else if (!ft_strcmp(content, "<<") && !c)
		return (T_DLESS);
	else if (!ft_strcmp(content, ">>") && !c)
		return (T_DGREAT);
	else if (!ft_strcmp(content, ">") && !c)
		return (T_RED_TO);
	else if (!ft_strcmp(content, "<") && !c)
		return (T_RED_FROM);
	else
		return (T_WORD);
}

void	ft_tokenadd_back(t_token **lst, t_token *new)
{
	t_token	*current;

	if (!(*lst))
	{
		(*lst) = new;
		return ;
	}
	current = (*lst);
	while (current->next != 0)
	{
		current = current->next;
	}
	current->next = new;
}

t_token	*ft_newtoken(void *content, int c)
{
	t_token		*re;

	re = (t_token *)malloc(sizeof(t_token));
	if (!re)
		return (0);
	re->value = content;
	re->type = (int)catego_toketype(content, c);
	re->quote = c;
	re->next = 0;
	return (re);
}