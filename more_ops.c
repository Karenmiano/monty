#include "monty.h"
#include <stdlib.h>
#include <stdio.h>

void pop(stack_t **stack, unsigned int line_number)
{
	stack_t *temp;

	if (stack == NULL || *stack == NULL)
	{
		fprintf(stderr, "L<%u>: can't pop an empty stack\n", line_number);
		exit (EXIT_FAILURE);
	}
	temp = *stack;
	*stack = temp->next;
	if (temp->next != NULL)
		(*stack)->prev = NULL;
	free(temp);
}
