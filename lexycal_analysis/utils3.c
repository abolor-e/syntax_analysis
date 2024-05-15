#include "../minishell.h"

int	ft_isalnum(int c)
{
	int	a;

	a = 0;
	if ((c >= 48 && c <= 57) || (c >= 65 && c <= 90) || (c >= 97 && c <= 122))
	{
		++a;
		return (a);
	}
	else
		return (0);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	if (!s1 || !s2)
		return (0);
	while (s1[i] == s2[i] && s1[i] && s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int strchr_check(char *str, int temp, int i, char sd)
{
    int j;

    j = 0;
    while (str[temp] != '\0' && temp <= i)
    {
        if (str[temp] == sd)
            j++;
        temp++;
    }
    if (j == 1)
        return (1);
    return (0);
}

int check_ds(char *str, int a, int i)
{
    while (str[a] != '\0' && a <= i)
    {
        if (str[a] == '$')
            return (1);
        a++;
    }
    return (0);
}
