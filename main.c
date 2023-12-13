#include "shell.h"

/**
 * main - main function
 * @argc: arguments count
 * @argv: arguments vector
 *
 * Return: 0 on success or 1 on error
 */
int main(int argc, char **argv)
{
	shell_t data[] = {{NULL, 0, NULL, NULL, NULL, 0, 0,
		0, NULL, NULL, 0, NULL, NULL, 0, 0, NULL, 0, 0}};
	int i = 2;

	if (argc == 2)
	{
		i = open(argv[1], O_RDONLY);
		if (i == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				print_err(argv[0]);
				print_err(": 0: Can't open ");
				print_err(argv[1]);
				print_char_err('\n');
				print_char_err(-1);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		data->readfd = i;
	}


	populate_env_list(data);
	read_history(data);
	shell_loop(data, argv);

	return (EXIT_SUCCESS);
}
