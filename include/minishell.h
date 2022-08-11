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
# include "../libft/libft.h"

# define BLACK "\e[0;30m"
# define RED "\e[0;31m"
# define GREEN "\e[0;32m"
# define YELLOW "\e[0;33m"
# define BLUE "\e[0;34m"
# define MAGENTA "\e[0;35m"
# define CYAN "\e[0;36m"
# define WHITE "\e[0;37m"
# define RESET "\e[0m"

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

typedef struct  s_struct
{
    char    **envp;
    int     shlvl;
    char    **pwd;
}   t_struct;


//Parsing
char	**parsing(char *line);

//log des mallocs et free
void	    log_file(char *type, char *name, char **matrix, char *string);

//Global Utils
int		    len_split(char **split);

//Environment Path Clone and Utils
t_struct    *clone_env(char **env, t_struct *data);                                         //clean
char        **add_var(char **matrix, int len_matrix, int len_nline, char *n_line);          //clean
char	    *var_exist(t_struct *data, char *variable);
int	        is_numeric(char *value);
int	        is_env_var(t_struct *data, char *export, int i);


//Builtins
t_struct	*unset_env(t_struct *data, char *unset);                        //Unset
t_struct	*export_env(t_struct *data, char *export);                      //Export        //clean
void	    env_builtin(t_struct *data, char **parse);                                    //Env           //clean
void	    echo(char **parse);                                             //Echo
void	    pwd_builtin(t_struct *data, char **parse);                                    //Pwd
void	    cd_builtin(t_struct *data, char *directory);
//Cd

//Execve Utils
char	    *get_full_cmd(char **argv);


//call diffrent execute
void	call_execute(char **parse, t_struct *data);

#endif
