#include "minishell.h"

int main(void)
{
    t_token *input;
    char    *inp;
    t_tree  *tree;
    t_table **parsing_table;

    inp = readline("");
    input = ft_lexer(inp);
    parsing_table = ft_init_parsing_table();
    //printf("%d, %d, %d\n", input->type, input->next->type, input->next->next->type);
    tree = syntax_analysis(input, parsing_table);
    if (!tree)
        printf("Tree is NULL\n");
    //printf("%d, %d, %d\n", tree->type, tree->right->type, tree->left->type);
    //printf("%d, %d\n", tree->type, tree->right->type);
    // printf("%d, %d, %d\n", tree->type, tree->left->type, tree->left->right->type);
}