#include "../minishell.h"

void	pop_check(t_stack **red, t_stack *stack)
{
	t_stack	*pop;

	if (*red == NULL)
		*red = stack;
	else
	{
		pop = *red;
		while ((*red)->next)
			*red = (*red)->next;
		(*red)->next = stack;
		*red = pop;
	}
	stack->next = NULL;
}

t_stack	*pop_oper(t_stack **stack, int reduce)
{
	t_stack	*temp = NULL;
	t_stack	*red_stack = NULL;
	int		i;

	i = 0;
	red_stack = NULL;
	if (stack)
	{
		i = 0;
		while (i < reduce)
		{
			temp = (*stack)->next;
			*stack = temp;
			temp = (*stack)->next;
			pop_check(&red_stack, *stack);
			*stack = temp;
			i++;
		}
	}
	return (red_stack);
}

int	push_reducted(t_stack **stack, int next)
{
	t_stack	*new_red;

	new_red = (t_stack *)malloc(sizeof(*new_red));
	if (!new_red)
		return (-1);
	new_red->data = NULL;
	new_red->next = *stack;
	*stack = new_red;
	new_red->state = -1;
	new_red->type = next;
	return (0);
}

int	pro_red_next_state(t_stack *stack, t_table **parsing_table)
{
	int	i;
	int	state;
	int	next_state;

	state = stack->next->state;
	i = -1;
	while (parsing_table[++i])
	{
		if (parsing_table[i]->state == state)
		{
			if (parsing_table[i]->token_type == stack->type)
				return (parsing_table[i]->next_state);
			else if (parsing_table[i]->token_type == -1)
				next_state = parsing_table[i]->next_state;
		}
	}
	return (next_state);
}

void	ms_clear_stack(t_stack *stack)
{
	t_stack	*next = NULL;

	while (stack)
	{
		next = stack->next;
		free(stack->data);
		free(stack);
		stack = next;
	}
}


int	reduce_stack(t_table *table_entry, t_tree **tree, t_stack **stack, t_table **pt)
{
	t_stack	*pop_stack = NULL;
	int	j;

	pop_stack = pop_oper(stack, table_entry->nb_reduce);
	if (pop_stack)
	{
		if (!push_reducted(stack, table_entry->next_state))
		{
			j = pro_red_next_state(*stack, pt);
			if (!change_stack_state(j, stack))
			{
				if (!ms_add_tree(tree, &pop_stack, table_entry->next_state))
				{
					ms_clear_stack(pop_stack);
					return (0);
				}
			}
		}
		ms_clear_stack(pop_stack);
	}
	return (-1);
}

/*
Stack has pushed input and another stack element with next state
change_stack_state creates an element with the next state to go in the pt*/

// int	ms_push_state(t_stack **stack, int state)
// {
// 	t_stack	*new;

// 	if (state == -1)
// 		return (-1);
// 	new = (t_stack *)malloc(sizeof(*new));
// 	if (!new)
// 		return (-1);
// 	new->type = -1;
// 	new->state = state;
// 	new->data = NULL;
// 	new->next = *stack;
// 	*stack = new;
// 	return (0);
// }

int	change_stack_state(int next_state, t_stack **stack)
{	
	t_stack	*new_stack;

	new_stack = (t_stack *)malloc(sizeof(*new_stack));
	if (!new_stack)
		return (-1);
	new_stack->data = NULL;
	new_stack->state = next_state;
	new_stack->next = *stack;
	*stack = new_stack;
	new_stack->type = -1;
	return (0);
}

/*Shift action: 
1. Pushes an element to the stack
2. Creates new stack element which will be the next element (change of state)
*/

// int	ms_push_input(t_stack **stack, t_token *input)
// {
// 	t_stack	*new;

// 	new = (t_stack *)malloc(sizeof(*new));
// 	if (!new)
// 		return (-1);
// 	new->type = input->type;
// 	new->quote = input->quote;
// 	new->state = -1;
// 	new->data = input->value;
// 	input->value = NULL;
// 	new->next = *stack;
// 	*stack = new;
// 	return (0);
// }


/*Initialize the stack:
Stack is needed to use the reduce and shift method
Reduces when 
*/
t_stack *init_stack(void)
{
    t_stack *new;

    new = (t_stack *)malloc(sizeof(*new));
    if (!new)
        return (NULL);
    new->state = 0;
    new->next = NULL;
    new->data = NULL;
    new->type = -1;
	return (new);
}