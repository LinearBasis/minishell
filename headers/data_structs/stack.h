#ifndef STACK_H
# define STACK_H

# include <stdlib.h>

typedef struct s_stack
{
	struct s_stack	*prev;
	int				value;
}	t_stack;

t_stack		*stack_create(int value);

void		stack_push(t_stack **stack, t_stack *to_add);
void		stack_pop(t_stack **stack);

void		stack_clear(t_stack *stack);

#endif