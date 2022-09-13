/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamartin <pamartin@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 13:32:28 by pamartin          #+#    #+#             */
/*   Updated: 2022/08/18 13:32:31 by pamartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_error_exit(char *message, int code)
{
	error_code = code;
	write(2, message, ft_strlen(message));
	write(2, "\n", 1);
	exit(EXIT_FAILURE);
}

void	ft_error(char *message, int code)
{
	error_code = code;
	write(2, message, ft_strlen(message));
	write(2, "\n", 1);
}
char 	*ft_malloc(int size)
{
	char *str;

	str = malloc(size + 1);
	if (!str)
	{
		error_code = 1;
		return (NULL);
	}
	return (str);
}

void	show_ghost()
{
	printf(G " /▔▔▔▔▔▔▔▔\\  ╭━━━━╮\n"R);
	printf(G "| ╭--╮╭--╮ | |BOO…|\n" R);
	printf(G "| |╭-╯╰-╮| | ╰━┳━━╯\n" R);
	printf(G "| ╰╯ ╭╮ ╰╯ |━━━╯ \n" R);
	printf(G "|    ╰╯    | \n" R);
}

char	*prompt(void)
{
	char	*str;

	run_signals(1);
	show_ghost();
	str = readline(G "|/\\_/\\/\\_/\\|	->" R);
	return (str);
}

int	main(int argc, char **argv, char **envp)
{
	t_struct	*data;
	char		*line;
	char		**tok;
	int			type;

	if (argc != 1)
		ft_error_exit("Number of arguments is different than 1", 1);
	printf("ARGV[0] = %s\n", argv[0]);
//	initializer(&data, envp);
	data = malloc(sizeof(t_struct));
	if (!data)
		return (0);
	welcome();
	data = clone_env(envp, data);
	while (19)
	{
		tok = malloc(sizeof(char *) * 4 + 1);
		if (!tok)
			return (0);

		line = prompt();
		if (!line)
			ft_error_exit("", 1);
		if (syntax_errors(line))
		{
			ft_error("Syntax error", 1);
			continue;
		}
		add_history(line);

		//a mettre dans la tokenisation/exec ??
//		line = remove_single_quotes(line);
//		line = remove_double_quotes(line);

		if (!is_pipe(line))
		{
			//line = parsing(line, data);
			tok = tokenisation(line, tok, data);
			if (tok)
			{
				type = check_type(tok);
				call_exec(data, tok, ft_atoi(tok[0]), ft_atoi(tok[2]), type);
				ft_clear_split(tok);
			}
			free(tok);
		}
		else
			printf("TEST\n");
//			pipe_exec(data, tok, line);

	}
	return (0);
}
