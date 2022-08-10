#ifndef MINI_H
#define MINI_H

#include "../libft/libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct s_data
{
	int		shlvl;
	int		len_env;  //?
	t_list	new_env;
	char	*line;
	char	*cmd;
}	t_data;

char	*get_env(t_list *env, char *name);


#endif