#include "../includes/mini.h"

// initie la liste de l'env (pas encore de contenu)
void	init_env(t_data *data, t_list **new_env, char *envp[])
{
	int	i;

	i = 0;
	while (envp[data->len_env])
		data->len_env++;
	while (i < data->len_env)
	{
		ft_lstadd_back(new_env, ft_lstnew(envp[i]));
		i++;
	}
}

// Intialize minishell data and setup the environment.
void	initializer(t_data *data, char *envp[])
{
	char	*shlvl;

	data->shlvl = 0;
	data->len_env = 0;
	data->new_env = NULL;


	init_env(data, &data->new_env, envp);
	shlvl = get_env(data->new_env, "SHLVL"); // Lis le shlvl de l'env actuel pour extraire le nombre
	if (!shlvl)
		add_env(data, &data->new_env, "SHLVL=1");
	// else
	// 	increment_shell_level(data, data->new_env);
}