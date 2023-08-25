#include "monty.h"
#include <stdlib.h>
#include <stdio.h>
/**
 * pop - pops the top element from a stack
 * @stack: pointer to pointer to top element of stack
 * @line_number: line_number where the opcode is called
 * Return: nothing
 */
void pop(stack_t **stack, unsigned int line_number)
{
	stack_t *temp;

	if (*stack == NULL)
	{
		fprintf(stderr, "L%u: can't pop an empty stack\n", line_number);
		exit(EXIT_FAILURE);
	}
	temp = *stack;
	*stack = temp->next;
	if (temp->next != NULL)
		(*stack)->prev = NULL;
	free(temp);
}
