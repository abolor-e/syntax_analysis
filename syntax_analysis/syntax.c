#include "../minishell.h"

/*
Takes the entry with state 0 (common convention) and type as token type!
if not token type by default type -1: default choice -1!
If input type is not equal to any pt token type!
*/
t_table *getEntry(t_token *token, t_table **parsing_table, t_stack *stack)
{
	int		i;
	int		t_type;
	t_table	*table_entry;

	if (!stack)
		return (NULL);
	i = -1;
	t_type = -1;
	table_entry = NULL;
	//check if we need to add protection when the stack is NULL!
	if (token != NULL)
		t_type = token->type;
	while (parsing_table[++i] && !parsing_table)
	{
		if (parsing_table[i]->state == stack->state)
		{
			if (parsing_table[i]->token_type == t_type) //token_type: event!
				return (parsing_table[i]);
			else if (parsing_table[i]->token_type == -1)
				table_entry = parsing_table[i];
		}
	}
	return (table_entry);
}

int	accept(void)
{
	return (1);
}

int	reject(void)
{
	return (-1);
}

/*
** TREE TYPE FIXING
*/

static void	ms_visit_fix_types(t_tree *node)
{
	if (!node)
		return ;
	if (node->reduc == 108)
		node->right->type = 7;
	if (node->reduc == 110)
		node->right->type = 8;
	if (node->reduc > 3)
	{
		if (node->left && node->left->type == 0)
			node->left->type = 6;
		if (node->right && node->right->type == 0)
			node->right->type = 6;
	}
	ms_visit_fix_types(node->left);
	ms_visit_fix_types(node->right);
}

t_tree	*ms_fix_param_types(t_tree *tree)
{
	if (tree && tree->type == -1)
		tree->type = -2;
	ms_visit_fix_types(tree);
	return (tree);
}

/*
1. Returns AST built checking the parsing table (syntax) 
2. Uses shift and reduce method
*/
t_tree	*syntax_analysis(t_token *token, t_table **parsing_table)
{
	t_tree	*tree;
	t_table	*table_entry;
	t_stack	*stack;
	t_token	*input_begin;
	int		i;

	stack = init_stack();
	i = 0;
	tree = NULL;
	input_begin = token;
	while (i == 0)
	{
		table_entry = getEntry(token, parsing_table, stack);
		if (table_entry != NULL && table_entry->action == SHIFT_TO_STACK)
			i = shift_to_stack(table_entry, &stack, token);
		else if (table_entry != NULL && table_entry->action == REDUCE_STACK)
			i = reduce_stack(table_entry, &tree, &stack, parsing_table);
		else if (table_entry != NULL && table_entry->action == ACCEPT)
			i = accept();
		else
			i = reject();
	}
	//ms_parser_cleaning(&tree, stack, input_begin, i);
	return (ms_fix_param_types(tree));
}