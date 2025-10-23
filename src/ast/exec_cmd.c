/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vapoghos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 13:34:31 by vapoghos          #+#    #+#             */
/*   Updated: 2025/10/22 12:27:56 by vapoghos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_first_non_empty(t_char_arr *expanded, t_ast **node, t_ht *env)
{
	while (!expanded)
	{
		expanded = expand_text((*node)->cmd->name, env);
		if (!expanded->arr)
		{
			if (find_last_index((*node)->cmd->args) <= 1)
			{
				free_char_arr(expanded);
				free(expanded);
				return (0);
			}
			free((*node)->cmd->name);
			shift_args(node);
			(*node)->cmd->name = (*node)->cmd->args[0];
			free_char_arr(expanded);
			free(expanded);
			expanded = NULL;
		}
	}
	free_char_arr(expanded);
	free(expanded);
	return (1);
}

int	validate_name(t_ast **node)
{
	t_char_arr	unquoted;
	int			status;

	status = 0;
	unquoted.size = 1;
	unquoted.arr = ft_calloc(2, sizeof(char *));
	unquoted.arr[0] = ft_strdup((*node)->cmd->name);
	remove_quotes(&unquoted);
	if (!ft_strcmp(*unquoted.arr, "."))
	{
		print_error("minishell: .: filename argument required",
			"\n", ".: usage: . filename [arguments]");
		status = 2;
	}
	else if (**unquoted.arr == '\0' || !ft_strcmp(*unquoted.arr, ".."))
	{
		print_error(*unquoted.arr, ": ", "command not found");
		status = 127;
	}
	else if (is_builtin(unquoted.arr[0]))
		status = -2;
	free_char_arr(&unquoted);
	return (status);
}

static int	wait_and_handle_signals(pid_t pid)
{
	int	status;
	int	sig;

	if (waitpid(pid, &status, 0) == -1)
	{
		perror("waitpid");
		return (-1);
	}
	if (WIFSIGNALED(status))
	{
		sig = WTERMSIG(status);
		if (sig == SIGQUIT)
			write(STDERR_FILENO, "Quit (core dumped)\n", 19);
		else if (sig == SIGINT)
			write(STDERR_FILENO, "\n", 1);
		return (128 + sig);
	}
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (-1);
}

int	exec_cmd(t_ast **node, t_ht *env)
{
	pid_t			pid;
	int				status;
	struct termios	tmodes;

	if (isatty(STDIN_FILENO))
		tcgetattr(STDIN_FILENO, &tmodes);
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	pid = fork();
	if (pid == 0)
		child_process(node, env);
	if (pid < 0)
	{
		perror("minishell: for:k");
		return (-1);
	}
	status = wait_and_handle_signals(pid);
	handle_parent_process(pid, &tmodes);
	return (status);
}

int	execute_command(t_ast **node, t_ht *env)
{
	int					status;
	int					last;
	t_char_arr			*expanded;

	expanded = NULL;
	if (!(*node)->cmd->name)
		return (handle_redirections((*node)->cmd, env));
	if (!find_first_non_empty(expanded, node, env))
		return (0);
	status = validate_name(node);
	if (status == -2)
		return (exec_builtin(node, env));
	else if (status != 0)
		return (status);
	last = find_last_index(&(*node)->cmd->args[1]);
	expanded = expand_text((*node)->cmd->args[last], env);
	if (!expanded)
		return (1);
	if (expanded->size > 0)
		ht_set(env, ft_strdup("_"),
			ft_strdup(expanded->arr[expanded->size - 1]));
	free_char_arr(expanded);
	free(expanded);
	return (exec_cmd(node, env));
}
