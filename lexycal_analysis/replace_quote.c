#include "../minishell.h"

t_env	*g_envp = NULL;

int envvar_len(char *str)
{
    int i;

    i = 0;
    if (!(*str))
        return (0);
    if (ft_isdigit(str[0]))
        return (1);
    while (str[i] != '\0')
    {
        if (ft_isalnum(str[i]) || str[i] == '_')
            i++;
        else
            break;
    }
    if (i == 0)
        return (-1);
    return (i);
}

int replace_var_2(char *new, char *newstr, int *i_new, int len)
{
    int i;

    i = *i_new;
    while (newstr && *newstr)
    {
        new[i] = *newstr;
        newstr++;
        i++;
    }
    new[i] = '\0';
    return (len);
}

int replace_var(char *str, char *exit, int index, char *new, int *i_new)
{
    int length;
    char    *string;
    int     i;
    char    *newstr;

    i = 0;
    if (str[index] == '?')
        return (replace_var_2(new, exit, i_new, 1));
    length = envvar_len(str);
    string = malloc(sizeof(char) * (length + 1));
    if (!string || !length)
        return (0);
    if (length < 0)
    {
        free(string);
        return (replace_var_2(new, "$", i_new, 0));
    }
    while (i < length)
    {
        string[i] = str[i];
        i++;
    }
    string[i] = 0;
    newstr = ft_getenv(string);
    free(string);
    if (newstr)
        replace_var_2(new, newstr, i_new, length);
    return (length);
}

int check_envvar(char *str, char *exit, char *new, int *i_new, int a, int i, int quote_type)
{
    int temp;
    int variable_len;

    temp = a;
    while (str[a] != '\0' && a < i)
    {
        if (str[a] == '$' && str[a + 1])
        {
            variable_len = replace_var(str, exit, a + 1, new, i_new);
            *i_new = (int)ft_strlen(new);
            a = a + variable_len + 1;
        }
        else if ((str[a] == '\'' && quote_type == 1 && !strchr_check(str, temp, i, '\'')) ||
                (str[a] == '\"' && quote_type == 2 && !strchr_check(str, temp, i, '\"')))
            a++;
        else
        {
            new[*i_new] = str[a];
            a++;
            *i_new = *i_new + 1;
        }
    }
    new[(*i_new) + 1] = '\0';
    *i_new = ft_strlen(new);
    return (a); 
}

/*
Replaces quotes and takes only the input string
Returns whether quote exists or no
*/
int replace_quote(char *str, char *exit, char *new, int *i, int *i_new)
{
    int quote;
    int quote_type;
    int a;

    a = *i;
    quote = 0;
    quote_type = check_quote(i, str);
    if (quote_type == 1 || quote_type == 2)
        quote = 1;
    while (a < *i)
    {
        if (quote == 1 && str[a] == '\'')
        {
            if (check_ds(str, a, *i) && !sq_dollar(str, '\''))
                a = check_envvar(str, exit, new, i_new, a, *i, quote_type);
        }
        else
            a = replace_double(str, exit, new, i_new, a, *i, quote_type);
        a++;
    }
    new[(*i_new) + 1] = '\0';
    *i_new = ft_strlen(new);
    return (quote);
}