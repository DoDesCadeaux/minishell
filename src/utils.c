#include "../includes/mini.h"

// ENVIRONNEMENT

char	*get_env(t_list *env, char *name)
{
	char	*content;
	int		len_name;

	len_name = ft_strlen(name);
	while (env)
	{
		content = (char *) env->content;
		if (!ft_strncmp(name, content, len_name) && content[len_name] == '=')
			return (content + len_name + 1);  //??
		env = env->next;
	}
	return (NULL);
}

void	add_env(t_data *data, t_list **env, char *str)
{
	ft_lstadd_back(env, ft_lstnew(ft_strdup(str)));
	data->len_env++;
}