/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vapoghos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 13:13:26 by vapoghos          #+#    #+#             */
/*   Updated: 2025/10/22 12:53:33 by vapoghos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	process_prompt(char *line, t_ht *map)
{
	t_list	*token_lst;
	t_ast	*ast;

	if (*line == '\0')
		return (free(line));
	if (!ht_get(map, "#ISNOTATTY"))
		add_history(line);
	token_lst = get_token_lst(line);
	free(line);
	if (!token_lst)
		return ;
	ast = ast_create_from_tokens(&token_lst, 0, map);
	ft_lstclear(&token_lst, del_token);
	if (!ast)
		return (ht_set(map, ft_strdup("?"), ft_strdup("2")));
	if (g_signal_int)
	{
		ht_set(map, ft_strdup("?"), ft_strdup("130"));
		g_signal_int = 0;
		return ;
	}
	handle_ast(ast, map);
}

int	process_not_tty_prompt(t_ht *map)
{
	char	*line;
	int		status;

	ht_set(map, ft_strdup("#ISNOTATTY"), ft_strdup("TRUE"));
	line = get_prompt_line();
	while (line)
	{
		g_signal_int = 0;
		process_prompt(line, map);
		unlink_heredocs();
		status = (unsigned char)ft_atoi(ht_get(map, "?"));
		if (status == 2)
			return (status);
		line = get_prompt_line();
	}
	status = (unsigned char)ft_atoi(ht_get(map, "?"));
	return (status);
}

int	process_tty_prompt(t_ht *map)
{
	char		*line;
	const char	*prompt = "\033[1;35m(\033[1;36mMinishell\033[1;35m)"
		"─>\033[1;32m$ \033[0m";

	while (1)
	{
		line = readline(prompt);
		if (!line)
		{
			tputs("exit\n", 1, ft_putchar);
			return (0);
		}
		if (g_signal_int == 130)
			ht_set(map, ft_strdup("?"), ft_strdup("130"));
		g_signal_int = 0;
		process_prompt(line, map);
		unlink_heredocs();
	}
	return (0);
}

int	prompt_loop(t_ht *map)
{
	if (!isatty(fileno(stdin)))
		return (process_not_tty_prompt(map));
	return (process_tty_prompt(map));
}

int	main(int argc, char *argv[], char *envp[])
{
	t_ht			map;
	unsigned char	status;
	char			*pwd;

	status = 0;
	if (argc > 1)
		return (0);
	setup_signals();
	ht_init_from_env(&map, envp);
	ht_set(&map, ft_strdup("?"), ft_strdup("0"));
	ht_set(&map, ft_strdup("0"), ft_strdup(argv[0]));
	pwd = ht_get(&map, "PWD");
	if (!pwd)
	{
		pwd = getcwd(NULL, 0);
		ht_set(&map, ft_strdup("PWD"), pwd);
	}
	if (!ht_get(&map, "SHLVL"))
		ht_set(&map, ft_strdup("SHLVL"), ft_strdup("1"));
	ht_set(&map, ft_strdup("#BASE_PATH"), ft_strdup(pwd));
	status = prompt_loop(&map);
	rl_clear_history();
	ht_clear(&map);
	return (status);
}
