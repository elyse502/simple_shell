#include "main.h"

/**
 * main - Entry to Simple Shell program.
 * @argc: Number of arguments.
 * @argv: Pointer to array of arguments.
 * Return: Always 0 if success else 1.
 */

int main(int argc, char *argv[])
{
	char *line;
	int Status;
	char **tokens;

	(void)argc;

	signal(SIGINT, ctrlc);
	Status = 0;
	while (Status == 0)
	{
		prompt();

		line = read_line();
		if (_strcmp(line, "\n") == 0)
		{
			tokens = NULL;
			free(line);
			continue;
		}
		tokens = _strtotokens(line);
		if (tokens[0] == NULL)
		{
			free(tokens);
			free(line);
			continue;
		}

		if (_strcmp(tokens[0], "exit") == 0)
		{
			_exitSimpleShell(tokens, line);
		}
		else
		{
			Status =  _execute(tokens, argv[0]);
		}
		free(line);
		free(tokens);
	}
	return (Status);
}
