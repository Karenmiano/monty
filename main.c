#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "monty.h"
char *opcodenarg;

int main(int argc, char *argv[])
{
	FILE *fp;
	char buf[1024], *line, *find;
	unsigned int i, l_no = 0;
	instruction_t arr[] = {
		{"push", push}, {"pall", pall}, {"pint", pint},
		{"pop", pop}, {NULL, NULL}};
	stack_t *top = NULL;

	if (argc != 2)
	{
		fprintf(stderr, "USAGE: monty file\n");
		exit(EXIT_FAILURE);
	}
	fp = fopen(argv[1], "r");
	if (fp == NULL)
	{
		fprintf(stderr, "Error: Can't open file %s\n", argv[1]);
		exit(EXIT_FAILURE);
	}
	while ((line = fgets(buf, 1024, fp)) != NULL)
	{
		l_no++;
		find = strchr(line, '\n');
		*find = '\0';
		opcodenarg = strtok(line, " \t");
		if (opcodenarg != NULL)
		{
			for (i = 0; arr[i].opcode != NULL; i++)
			{
				if (!strcmp(opcodenarg, arr[i].opcode))
				{
					arr[i].f(&top, l_no);
					break;
				}
			}
			if (arr[i].opcode == NULL)
			{
				fprintf(stderr, "L%u: unknown instruction %s\n", l_no, opcodenarg);
				free_stack(top);
				exit(EXIT_FAILURE);
			}
		}
	}
	free_stack(top);
	fclose(fp);
	return (0);
}
void push(stack_t **stack, unsigned int line_number)
{
	stack_t *new, *temp;

	new = malloc(sizeof(stack_t));
	new->prev = NULL;
	opcodenarg = strtok(NULL, " \t");
	if (opcodenarg == NULL)
	{
		fprintf(stderr, "L%u: usage: push integer\n", line_number);
		free(new);
		free_stack(*stack);
		exit(EXIT_FAILURE);
	}
	else if (atoi(opcodenarg) == 0 && isdigit(opcodenarg[0]) == 0)
	{
		fprintf(stderr, "L%u: usage: push integer\n", line_number);
		free(new);
		free_stack(*stack);
		exit(EXIT_FAILURE);
	}
	else
	{
		new->n = atoi(opcodenarg);
		new->prev = NULL;
	}
	if (*stack == NULL)
	{
		new->next = NULL;
		*stack = new;
	}
	else
	{
		temp = *stack;
		new->next = temp;
		temp->prev = new;
		*stack = new;
	}
}
void pall(stack_t **stack, unsigned int line_number __attribute__((unused)))
{
	stack_t *temp;

	if (*stack == NULL)
		return;
	temp = *stack;
	while (temp != NULL)
	{
		printf("%d\n", temp->n);
		temp = temp->next;
	}
}
void pint(stack_t **stack, unsigned int line_number)
{
	if (*stack == NULL)
	{
		fprintf(stderr, "L%u: can't pint, stack empty\n", line_number);
		exit (EXIT_FAILURE);
	}
	printf("%d\n", (*stack)->n);
}
void free_stack(stack_t *top)
{
	stack_t *trav;

	if (top == NULL)
		return;
	while (top->prev != NULL)
		top = top->prev;
	trav = top;
	while (trav->next != NULL)
	{
		trav = trav->next;
		free(trav->prev);
	}
	free(trav);
}
