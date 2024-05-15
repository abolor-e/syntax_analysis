#include "minishell.h"

int main(void)
{
    t_token *input;
    char    *inp;
    t_tree  *tree;
    t_table **parsing_table;

    inp = readline("");
    input = ft_lexer(inp);
    parsing_table = ms_init_parsing_table();
    printf("%d, %d, %d, %d\n", input->type, input->next->type, input->next->next->type, input->next->next->next->type);
    tree = syntax_analysis(input, parsing_table);
}