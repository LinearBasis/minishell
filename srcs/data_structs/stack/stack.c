#include "data_structs/stack.h"

t_stack	*stack_create(int value)
{
	t_stack	*out;

	out = malloc(sizeof(t_stack));
	if (!out)
		return (out);
	out->prev = NULL;
	out->value = value;
	return (out);
}

void	stack_push(t_stack **stack, t_stack *to_add)
{
	if (!stack || !to_add)
		return ;
	to_add->prev = *stack;
	*stack = to_add;
}

void	stack_pop(t_stack **stack)
{
	t_stack		*tmp;

	if (!stack || !*stack)
		return ;
	tmp = *stack;
	*stack = (*stack)->prev;
	free(tmp);
}

void	stack_clear(t_stack *stack)
{
	t_stack	*tmp;

	if (!stack)
		return ;
	while (stack)
	{
		tmp = stack;
		stack = stack->prev;
		free(tmp);
	}
}
