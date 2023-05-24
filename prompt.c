#include "main.h"

/**
 * prompt - Print prompt.
 * Return: Void.
 */
void prompt(void)
{
	if (isatty(STDIN_FILENO))
	{
		write(STDOUT_FILENO, "#cisfun$ ", 9);
	}
}
