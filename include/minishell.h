/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algaspar <algaspar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 15:15:06 by pamartin          #+#    #+#             */
/*   Updated: 2022/09/19 10:13:14 by algaspar         ###   ########.fr       */
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
# include <errno.h>
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
# define ERRNO errno

# define ERROR 1
# define SYNTAX_ERROR 1
# define MALLOC 1
# define EXEC_ERROR 126
# define CMD_ERROR 127
# define PATH_ERROR 127
# define FD_ERROR 1
# define PIPE_ERROR 258
# define SUCCES	0

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
# define OPTION	"echo -n"
# define CMD	"echo "
# define MSG_PIPE "pipe> "
# define MSG_HERE "heredoc> "

int	error_code;

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
	BU_EXPORT_EMPTY,
	BU_UNSET,
	BU_EXIT,
	BINARY,
	BAD_BINARY,
};

typedef struct s_struct
{
	char	**envp;
	int		shlvl;
	char	**pwd;
	char	*user;
	char	*tmp_1;
	char	*tmp_2;
	char	*tmp_3;
	int		type;
	int		check;
	int		pipe;
	int 	father_code;
}	t_struct;

//ENVIRONNEMENT
t_struct	*clone_env(char **env, t_struct *data);
char		**add_var(char **matrix, int len_matrix, int len_nline,
				char *n_line);
char		*var_exist(t_struct *data, char *variable);
int			is_numeric(char *value);
int			is_env_var(t_struct *data, char *export, int i);

//TOKENISATION
char		**tokenisation(char *line, char **tok, t_struct *data);
int			tok_fd_in(char **tok, char **line_split, int i);
int			tok_1(char **tok, char **line_split, int i, char *line);
int			check_type(char **tok, t_struct *data);
int			is_good_binary(t_struct *data, char *cmd);
int			ft_strcmp(char *s1, char *s2);
char		*get_fd(char *file, int type, char *token);
int			is_pipe(char *line);

//SIGNALS
void		rl_replace_line(const char *text, int clear_undo);

//BUILTINS
t_struct	*unset_global(t_struct *data, char *unset);
t_struct	*export_global(t_struct *data, char *export);
void		env_builtin(t_struct *data);
void		export_env(t_struct *data, char *cmd);
void		unset_env(t_struct *data, char *cmd);
void		export_empty(t_struct *data);
void		echo(char **tok);
void		pwd_builtin(void);
void		cd_builtin(t_struct *data, char **tok);
void		exit_builtins(void);
void		update_pwd(t_struct *data, int status);
t_struct	*update_var(t_struct *data, char *export, int i);
t_struct	*update_envp(t_struct *data, char *type);

//ENV
int			len_split(char **split);

//EXEC
void		execute(t_struct *data, char *cmd);
char		**path_list(char **envp);
char		*get_cmd_path(char **paths, char *cmd);
int			increment_j(int i, int j, char *str);
int 		increment_i(int i, char *str);
char		*cpy_dest(int i, int j, char *str, char *dest);
void		run_without_pipe(t_struct *data, char **tok);
void		run_exec(t_struct *data, char **tok);
void		run_bad_binary(t_struct *data, char *cmd);
char		**ft_split_pipe(char *s, char c);
void		pipe_exec(t_struct *data, char **tok, char *line);
void		call_exec(t_struct *data, char **tok, int fdin, int fdout);

//GNL
char		*get_next_line(int fd, char *msg);
char		*ft_strjoin_gnl(char *s1, char *s2);
char		*ft_strchr(char *s, int c);
void		*ft_free(char *save);

//PARSING
int			syntax_errors(char *line);
int			is_metachar(char c);
char		*parsing(char *line_to_pars, t_struct *data);
char		*parsing_dollar(t_struct *data, char *line_to_pars);
char		*str_dup_parts(char *src, int end, int start);
int			skip_double_quotes(char *line, int i);
int			skip_single_quotes(char *line, int i);
int			skip_all_quotes(char *line, int i);
char		*remove_single_quotes(char *line);
char		*remove_double_quotes(char *line);
int			is_end_of_dollar(char c);
int			update_i(char *line_pars, int i);
char		*remove_multi_space(char *line);
char		*get_full_pipe(char *line);

//Main
void		show_ghost(void);
void		protect_malloc(void *element);
void		ft_error(char *message, int code);
void		ft_error_exit(char *message, int code);

//Utils
char		*msg(char *cmd, char *element, char *msg);

//Initializer
t_struct	*initializer(char **envp, int argc, char **argv);

//Signals
void		run_signals(int sig);

//Welcome
void		welcome(void);

#endif
