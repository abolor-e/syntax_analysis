#include "../minishell.h"

int tok_sep_len(char *line, int i)
{
    while (check_sep(*line) == 1 && *line != ' ')
    {
        i++;
        line++;
    }
    return (i);
}

int check_sep(char c)
{
    if (c == ' ' || c == '|' || c == '<' || c == '>')
        return (1);
    return (0);
}

int sep_to_sep_len(char *line, t_sdQuote *sdQ)
{
    int a;
    int j;

    a = 0;
    j = 0;
    while (line[a])
    {
        if (line[a] == '\'')
            sdQ->single_q++;
        if (line[a] == '\"')
            sdQ->double_q++;
        if (check_sep(line[a]) == 1)
        {
            if (sdQ->double_q % 2 == 0 && sdQ->single_q == 0)
            break;
            else if (sdQ->double_q % 2 == 1 && sdQ->single_q == 2)
            break;
            else if (sdQ->double_q % 2 == 2 && sdQ->single_q == 1)
            break;
        }
        a++;
        j++;
    }
    if (check_sep(*line))
        j = tok_sep_len(line, j);
    return j;
}

void   init_sdQuote(t_sdQuote *q)
{
    q->single_q = 0;
    q->double_q = 0;
    q->type = 0;
}

char	*ft_getenv(char *var)
{
	t_env	*temp;

	temp = g_envp;
	while (temp)
	{
		if (!ft_strcmp(var, temp->name))
			return (temp->content);
		temp = temp->next;
	}
	return (NULL);
}