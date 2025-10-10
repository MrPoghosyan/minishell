/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_util.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vahstepa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 09:00:26 by vahstepa          #+#    #+#             */
/*   Updated: 2025/10/05 09:02:51 by vahstepa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	child_process(t_ast **node, t_ht *env)
{
	setpgid(0, 0);
	tcsetpgrp(STDIN_FILENO, getpid());
	reset_signals();
	if (handle_redirections((*node)->cmd, env))
		exit(1);
	if ((*node)->token == T_CMD)
		exec_non_builtin(node, env);
	exit(0);
}

void	handle_parent_process(pid_t pid, struct termios *tmodes)
{
	pid_t	shell_pgid;

	shell_pgid = getpgrp();
	setpgid(pid, pid);
	tcsetpgrp(STDIN_FILENO, pid);
	tcsetpgrp(STDIN_FILENO, shell_pgid);
	tcsetattr(STDIN_FILENO, TCSADRAIN, tmodes);
}
