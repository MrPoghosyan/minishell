/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   exec_cmd_util.c                                    :+:      :+:    :+:   */
/*													+:+ +:+		 +:+	 */
/*   By: vahstepa <marvin@42.fr>					+#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2025/10/05 09:00:26 by vahstepa		  #+#	#+#			 */
/*   Updated: 2025/10/21 19:03:25 by vapoghos         ###   ########.fr       */
/*																			*/
/* ************************************************************************** */

#include <minishell.h>

void	child_process(t_ast **node, t_ht *env)
{
	reset_signals();
	if (handle_redirections((*node)->cmd, env))
		exit(1);
	if ((*node)->token == T_CMD)
		exec_non_builtin(node, env);
	exit(0);
}

void	handle_parent_process(pid_t pid, struct termios *tmodes)
{
	setup_signals();
	if (isatty(STDIN_FILENO))
	{
		tcsetpgrp(STDIN_FILENO, pid);
		tcsetattr(STDIN_FILENO, TCSADRAIN, tmodes);
	}
}
