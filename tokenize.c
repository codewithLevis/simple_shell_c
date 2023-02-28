#include "shell.h"

#define TOK_BUFSIZE 64
#define TOK_DELIM " \t\r\n\a"

/**
*my_reallocate - allocate memory for array of strings
*@ptr_arr: pointer to an array of strings
*@old_len: old array size
*@new_len: new array size
*Return: pointer to a newly allocated memory
*/

char **my_reallocate(char **ptr_arr, unsigned int old_len, unsigned int new_len)
{
	char **new;
	unsigned int i;

	if (ptr_arr == NULL)
		return (malloc(sizeof(char*) * new_len));

	if (new_len == old_len)
		return (pointer_array);

	new = malloc(sizeof(char*) * new_len);

	if (new_pointer_array == NULL)
		return (NULL);

	if (new_len < old_len)
		old_len = new_len;

	for (i = 0; i < old_len; i++)
		new[i] = ptr_arr[i];

	free(ptr_arr);
	return (new);
}

/**
*tokenize - splits input to tokens
*@str: pointer to input
*@delim: delimiter
*Return: an array of strings
*/

char **tokenize(char *input, const char *delim)
{
	size_t bufsize = TOK_BUFSIZE;
	size_t i;
	char token,**tokens = malloc(bufsize * sizeof(char*));

	if (tokens == NULL)
		return (NULL);

	token = my_strtok(input, delim);

	i = 0;
	while (token != NULL)
	{
		tokens[i++] = strdup(token);
		if (i >= bufsize)
		{
			bufsize += TOK_BUFSIZE;
			tokens = my_reallocate(tokens, i, bufsize * sizeof(char*));

			if (tokens == NULL)
			{
				write(STDERR_FILENO, ": allocation error\n", 18);
				exit(EXIT_FAILURE);
			}
		}
		token = my_strtok(NULL, delim);
	}
	tokens[i] = NULL;
	return (tokens);
}