#include "../includes/mini.h"

int	main(int argc, char *argv[], char *envp[])
{
	t_data	data;

	(void) argc;
	(void) argv;
	initializer(&data, envp);
	// while (42)
	// {
	// 	data.line = reader(&data);
	// 	if (!data.line || !syntax_error(&data) || is_only_space(data.line))
	// 		continue ;
	// }
	return (1);
}