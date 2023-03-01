#include "shell.h"


int (*find_builtin_func(char *cmd))(ShellData *)
{
	builtin_t builtins[] = {
		{ "env", _env },
		{ "exit", exit_shell },
		{ "setenv", _setenv },
		{ "unsetenv", _unsetenv },
		{ "cd", change_directory },
		{ "help", get_help },
		{ NULL, NULL }
	};

	for (int i = 0; builtins[i].name != NULL; i++)
	{
		if (_strcmp(builtins[i].name, cmd) == 0)
			return (builtins[i].f);
	}

	return (NULL);
}

/**
*_env - prints shell environs
*@ptr: pointer to the shell struct
*Return: 1
*/

int _env(ShellData *ptr)
{
	int i = 0, j = 0;

	while ((*ptr).environment_vars[i])
	{
		j = 0;
		while ((*ptr).environment_vars[i][i][j])
			j++;

		dprintf(STDOUT_FILENO, "%s\n", (*ptr).environment_vars[i][i]);
		i++;
	}

	(*ptr).exit_status = 0;
	return (1);
}


/**
 * exit_handler - Handles the exit builtin command
 * @data: A pointer to a data_shell struct
 *
 * Return: Always returns 0 to signal the shell to exit
 */
int exit_handler(ShellData *ptr)
{
	unsigned int exit_status;
	int is_digit, str_len, is_big_number;

	if (data->args[1] != NULL)
	{
		exit_status = _atoi((*ptr).parsed_input_args[1]);
		is_digit = _isdigit((*ptr).parsed_input_args[1]);
		str_len = _strlen((*ptr).parsed_input_args[1]);
		is_big_number = exit_status > (unsigned int)INT_MAX;

		if (!is_digit || str_len > 10 || is_big_number)
		{
			handle_error(ptr, 2);
			dprintf(STDERR_FILENO, "hsh: %d: exit: Illegal number: %s\n", data->line_count, data->args[1]);
			(*ptr).exit_status = 2;
			return (1);
		}

		(*ptr).exit_status = (exit_status % 256);
	}

	return (0);
}