#include "../minishell.h"

/*
Counts quotes
*/
int quote_count(int *i, char *str, t_sdQuote *quote)
{
    if (str[*i] == '\'')
    {
        if (quote->double_q == 2)
            return (0);
        quote->double_q++;
    }
    else if (str[*i] == '\"')
    {
        if (quote->single_q == 2)
            return (0);
        quote->single_q++;
    }
    return (1);
}

/*
Returns quote type
*/
int check_quote(int *i, char *str)
{
    int a;
    int type;
    t_sdQuote   quote;

    a = ft_strlen(str);
    init_sdQuote(&quote);
    while (*i < a)
    {
        if (!quote_count(i, str, &quote))
            break;
        *i = *i + 1;
        if ((type = quote_type(&quote)))
            break;
    }
    if (type == 1 || type == 2)
        return (type);
    if (quote.type == 2 && quote.double_q != 0 && quote.single_q >= 2)
        return (1);
    else if (quote.double_q >= 2 && quote.single_q != 0 && quote.type == 1)
        return (2);
    return (0);
}

int quote_type(t_sdQuote *quote)
{
    if (quote->double_q == 1 && quote->type == 0)
        quote->type = 2;
    else if (quote->single_q == 1 && quote->type == 0)
        quote->type = 1;
    if (quote->single_q == 2 && quote->type == 1)
        return (1);
    else if (quote->double_q == 2 && quote->type == 2)
        return (2);
    if (quote->double_q == 2 && quote->single_q == 2)
        return (3);
    return (0);
}

int sq_dollar(char *str, char sq)
{
    int i;

    i = 0;
    while (str[i] != '\0')
    {
        if (str[i] == sq)
        {
            while (str[i] != '\0')
            {
                if (str[i] == sq)
                    return (0);
                if (str[i] == '$')
                    return (1);
                i++;
            }
        }
        i++;
    }
    return (0);
}

int replace_double(char *str, char *exit, char *new, int *i_new, int a, int i, int quote_type)
{
    if ((quote_type == 1 && str[a] != '\'') || (quote_type == 2 && str[a] != '\"'))
    {
        new[(*i_new)] = str[a];
        (*i_new) = (*i_new) + 1;
    }
    else if (quote_type == 2 && str[a] == '\"')
    {
        if (check_ds(str, a, i))
            a = check_envvar(str, exit, new, i_new, a, i, quote_type);
    }
    else if (quote_type == 0)
    {
        if (check_ds(str, a, i))
            a = check_envvar(str, exit, new, i_new, a, i, quote_type);
        else
        {
            new[*i_new] = str[a];
            (*i_new) = (*i_new) + 1;
        }
    }
    return (a);
}