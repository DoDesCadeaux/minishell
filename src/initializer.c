#include "../include/minishell.h"

t_struct 	*initializer(char **envp, int argc, char **argv)
 {
	t_struct *data;

	if (argc != 1)
		 ft_error_exit("Number of arguments != 1", 1);
	if (ft_strcmp(argv[0], "./minishell"))
		ft_error_exit("Bad program name", 1);
	welcome();
	data = malloc(sizeof(t_struct));
	if (!data)
		ft_error("Malloc error", 1); //Que ecrire ??welcome();
	 data = clone_env(envp, data);
	 return (data);
 }
