#include "shell.h"

/**
*add_node - adds node to linked list of VarNode_t
*@start: the head of the list
*@len_var: variable length
*@len_val: value length
*@val: value
*Return: modified linked list
*/
VarNode_t *add_node(VarNode_t **start, int len_var, char *val, int len_val)
{
	VarNode_t *new_node, *temp;

	new_node = malloc(sizeof(VarNode_t));

	if (new_node == NULL)
		return (NULL);
	new_node->len_var = len_var;
	new_node->value = val;
	new_node->len_val = len_val;
	new_node->next = NULL;

	if (*start == NULL)
		*start = new_node;

	else
	{
		temp = *start;
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new_node;
	}

	return (*start);
}

/**
*free_VarNode_t - frees a VarNode_t list
*@start: pointer to the head of the linked list
*Return: void
*/
void free_VarNode_t(VarNode_t **start)
{
	VarNode_t *prev, *current;

	if (start != NULL)
	{
	current = *start;

	do {
		prev = current;
		current = current->next;
		free(prev);
	} while (current != NULL);

	*start = NULL;
	}
}
/**
*add_CommandLineNode - adds commands node
*@start: pointer to start of node
*@command: token of user input as a result of
*being separeted tokenization by separators
*Return: modified list
*/
CommandLineNode *add_CommandLineNode(CommandLineNode **start, char *command)
{
	CommandLineNode *new_node, *curr;
	new_node = malloc(sizeof(CommandLineNode));
	if (new_node == NULL)
	return (NULL);

	new_node->command = command;
	new_node->next = NULL;

	if (*start == NULL)
		*start = new_node;

	else
	{
		curr = *start;
		do {
			curr = curr->next;
		} while (curr->next != NULL);
		curr->next = new_node;
	}

	return (*start);
}

/**
*add_SeparatorNode - adds node
*@head: pointer to beginning of list
*@symbol: separator
*Return: modified node
*/
SeparatorNode *add_SeparatorNode(SeparatorNode **head, char symbol)
{
	SeparatorNode current_node, *new_node = malloc(sizeof(SeparatorNode));

	if (new_node == NULL)
		return (NULL);

	new_node->symbol = symbol;
	new_node->next = NULL;

	if (*head == NULL)
		*head = new_node;
	else
	{
		current_node = *head;
		while (current_node->next != NULL)
			current_node = current_node->next;

		current_node->next = new_node;
	}

	return (*head);
}
char *replace_operators(char *input_string, int encode)
{
	char *result = input_string;
	char *current_char = result;

	// Check whether we need to encode or decode the input string
	if (encode == 1)
	{
		// Loop through the input string and replace '|' and '&' with their respective ASCII codes
		while (*current_char != '\0')
		{
			if (*current_char == '|')
			{
				// If the '|' is not part of '||', replace it with the ASCII code for '|'
				if (*(current_char + 1) != '|')
					*current_char = 16;
				// If the '|' is part of '||', skip over the next character
				else
					current_char++;
			}
			if (*current_char == '&')
			{
				// If the '&' is not part of '&&', replace it with the ASCII code for '&'
				if (*(current_char + 1) != '&')
					*current_char = 12;
				// If the '&' is part of '&&', skip over the next character
				else
					current_char++;
			}
			current_char++;
		}
	}
	else
	{
		// Loop through the input string and replace ASCII codes with '|' and '&'
		while (*current_char != '\0')
		{
			if (*current_char == 16)
				*current_char = '|';
			if (*current_char == 12)
				*current_char = '&';
			current_char++;
		}
	}
	// Return the modified input string
	return result;
}
