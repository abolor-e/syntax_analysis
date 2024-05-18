#include "../minishell.h"

t_tree	*ms_stack_to_node(t_stack *popped)
{
	t_tree	*node;

	node = (t_tree *)malloc(sizeof(*node));
	if (node)
	{
		node->type = popped->type;
		node->reduc = -1;
		if (popped->type >= 100)
		{
			node->type = -1;
			node->reduc = popped->type;
		}
		node->data = popped->data;
		node->qt_rm = popped->quote;
		popped->data = NULL;
		node->left = NULL;
		node->right = NULL;
		node->next = NULL;
		return (node);
	}
	return (NULL);
}

/*
** REMOVE NODE FROM LIST
** Remove a node from the node list that will be attached under a reduction
** node
*/

void	ms_remove_node_from_list(t_tree **tree, t_tree *node)
{
	t_tree	*previous = NULL;
	t_tree	*tmp = NULL;

	if (*tree == node)
	{
		*tree = node->next;
		return ;
	}
	else
	{
		previous = NULL;
		tmp = *tree;
		while (tmp)
		{
			if (tmp == node)
			{
				previous->next = tmp->next;
				return ;
			}
			previous = tmp;
			tmp = tmp->next;
		}
	}
}

/*
** SEARCH REDUCTION
** Search for a reduction node in the node list to attach it
** under the current reduction node.
*/

t_tree	*ms_search_reduction(t_tree **tree, int reduction)
{
	t_tree	*begin;
	t_tree	*result;

	result = NULL;
	begin = *tree;
	*tree = (*tree)->next;
	while (*tree)
	{
		if ((*tree)->reduc == reduction)
		{
			result = *tree;
			ms_remove_node_from_list(&begin, *tree);
			break ;
		}
		*tree = (*tree)->next;
	}
	*tree = begin;
	return (result);
}

/*
** ADD REDUCTION FRONT
** Creates a node for the current reduction and adds it in front
** of the node list;
*/

t_tree	*ms_add_reduction_front(t_tree **tree, int reduction)
{
	t_tree	*node;

	node = (t_tree *)malloc(sizeof(*node));
	if (node)
	{
		node->type = -1;
		node->reduc = reduction;
		node->data = NULL;
		node->left = NULL;
		node->right = NULL;
		node->next = *tree;
		*tree = node;
		return (node);
	}
	return (NULL);
}

/*
** BUILD TREE
** Attach the right nodes under the reduction node.
*/

int	ms_build_tree(t_tree **tree, t_tree *reduc_node, t_stack **popped)
{
	int		i;
	t_tree	*child = NULL;
	t_stack	*begin;

	i = -1;
	begin = *popped;
	while (*popped)
	{
		if ((*popped)->type >= 100)
			child = ms_search_reduction(tree, (*popped)->type);
		else
			child = ms_stack_to_node(*popped);
		if (!child)
			return (-1);
		if (++i == 0)
			reduc_node->right = child;
		else
			reduc_node->left = child;
		if (i == 1 && (*popped)->next)
			reduc_node = reduc_node->left;
		(*popped) = (*popped)->next;
	}
	*popped = begin;
	return (0);
}

/*
** ADD TREE
** Add the popped elements from the stack to the output tree, under
** the reduction node.
*/

int	ms_add_tree(t_tree **tree, t_stack **popped, int reduction)
{
	t_tree	*reduc_node = NULL;

	reduc_node = ms_add_reduction_front(tree, reduction);
	if (reduc_node)
	{
		if (!ms_build_tree(tree, reduc_node, popped))
			return (0);
	}
	return (-1);
}