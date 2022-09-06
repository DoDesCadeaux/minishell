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
# include <signal.h>
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

enum	e_type
{
	BU_ECHO,
	BU_CD,
	BU_PWD,
	BU_ENV,
	BU_EXPORT,
	BU_UNSET,
	BU_EXIT,
	BINARY,
	BINARY_PIPE //utile ?
};

typedef struct s_struct
{
	char	**envp;
	int		shlvl;
	char	**pwd;
	char	*tmp_1;
	char	*tmp_2;
	char	*tmp_3;
	int		fd;
	
}	t_struct;

void		welcome(void);
void		show_ghost(void);

//tokenisation and utils
char		**tokenisation(char *line, char **tok);
int			ft_strcmp(char *s1, char *s2);
char		*get_fd(char *file, int type, char *token);
int			is_pipe(char *line);
void		pipe_exec(t_struct *data, char **tok, char *line);
char		*create_heredoc(char *delimiter);
int			tok_1(char **tok, char **line_split, int i);
void		call_exec(t_struct *data, char **tok, int fdin, int fdout, int type);
int			check_type(char **tok);


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
void		env_builtin(t_struct *data);
t_struct	*export_env(t_struct *data, char *cmd);
t_struct	*unset_env(t_struct *data, char *cmd);
void		echo(char **tok);
void		pwd_builtin(void);
void		cd_builtin(t_struct *data, char **tok);
void		exit_builtins(t_struct *data, char **tok);

//Execve Utils
void		execute(t_struct *data, char *cmd);
char		**path_list(char **envp);
char		*get_cmd_path(char **paths, char *cmd);
void		run_signals(int sig);

//call diffrent execute


//PARSING
char		*parsing_dollar(t_struct *data, char *line_to_pars);
int			syntax_error(char *line);

//SIGNALS
void		rl_replace_line(const char *text, int clear_undo);

//UTILS
void	ft_putstr(char *str);


#endif
