/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamartin <pamartin@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 15:15:06 by pamartin          #+#    #+#             */
/*   Updated: 2022/08/05 15:15:08 by pamartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <limits.h>
# include "../libft/libft.h"

# define BLACK "\e[0;30m"
# define RED "\e[0;31m"
# define G "\e[0;32m"
# define Y "\e[0;33m"
# define BLUE "\e[0;34m"
# define MAGENTA "\e[0;35m"
# define CYAN "\e[0;36m"
# define WHITE "\e[0;37m"
# define R "\e[0m"

# define HERE_DOC "./here_doc"

# define BUFFER_SIZE 100

# define LESS "<"
# define DLESS "<<"
# define GREAT ">"
# define DGREAT ">>"
# define PIPE "|"

# define ECHO   "echo"
# define CD     "cd"
# define PWD    "pwd"
# define ENV    "env"
# define EXPORT "export"
# define UNSET  "unset"
# define EXIT   "exit"

enum	e_redirection
{
	REDIR_STDIN,
	REDIR_STDOUT
};

typedef struct s_struct
{
	char	**envp;
	int		shlvl;
	char	**pwd;
	char	*tmp_1;
	char	*tmp_2;
	char	*tmp_3;
}	t_struct;

void		welcome(void);

//tokenisation and utils
char		**tokenisation(char *line, char **tok);
int			ft_strcmp(char *s1, char *s2);
char		*get_fd(char *file, int type, char *token);

//Global Utils
int			len_split(char **split);

//Get Next Line
char		*get_next_line(int fd);
char		*ft_strjoin_gnl(char *s1, char *s2);
char		*ft_strchr(char *s, int c);
void		*ft_free(char *save);

//Environment Path Clone and Utils
t_struct	*clone_env(char **env, t_struct *data);
char		**add_var(char **matrix, int len_matrix, int len_nline,
				char *n_line);
char		*var_exist(t_struct *data, char *variable);
int			is_numeric(char *value);
int			is_env_var(t_struct *data, char *export, int i);

//Builtins
t_struct	*unset_global(t_struct *data, char *unset);
t_struct	*export_global(t_struct *data, char *export);
void		env_builtin(t_struct *data, char **tok);
t_struct	*export_env(t_struct *data, char **full_cmd);
t_struct	*unset_env(t_struct *data, char **full_cmd);
void		echo(char **tok);
void		pwd_builtin(t_struct *data, char **tok);
void		cd_builtin(t_struct *data, char *directory, char **tok);
void		exit_builtins(t_struct *data, char **tok);

//Execve Utils
void		execute(t_struct *data, char *cmd);
char		**path_list(char **envp);
char		*get_cmd_path(char **paths, char *cmd);

//call diffrent execute
void		call_execute(char **tok, t_struct *data);
void		exec_global(t_struct *data, char **tok, char *cmd);

//PARSING
char		*parsing_dollar(t_struct *data, char *line_to_pars);
int			syntax_error(char *line);

//QUOTES
char	*single_quote(char *line);

#endif
