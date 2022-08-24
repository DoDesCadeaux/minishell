void	begin_end_with_separator(char *line)
{
	int		max;
	char	*str;
	char	**split;

	if (g_error_code)
		return ;
	split = ft_split(line, ' ');
	if (!split)
		exit(EXIT_FAILURE);
	str = join_the_split(split);
	if (line[0] == '|')
		print_s_error(line[0], 0, 0, 258);
	max = ft_strlen(str) - 1;
	if (is_metachar(str[max]))
		print_s_error(0, 0, "newline", 258);
	else if (str[max - 1] && (str[max - 1] == '<'
							  || str[max - 1] == '>') && is_metachar(str[max]))
		print_s_error(str[max], 0, 0, 258);
	free_split(split);
}

int	syntax_error(char *line)
{
	int		save_value_error_code;

	save_value_error_code = //var globale?
	if (begin_end_with_separator(line))
		return (1);
	?? = save_value_error_code;

	return (0);
}