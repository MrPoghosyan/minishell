/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_util.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vahstepa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 09:27:16 by vahstepa          #+#    #+#             */
/*   Updated: 2025/10/05 09:45:06 by vahstepa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_heredoc_ctx(t_heredoc_ctx *ctx, char *delimiter)
{
	ctx->heredoc = get_heredoc_name();
	ctx->fd = open(ctx->heredoc, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	ctx->target.size = 1;
	ctx->target.arr = (char **)ft_calloc(2, sizeof(char *));
	if (!ctx->target.arr)
		return (0);
	ctx->target.arr[0] = ft_strdup(delimiter);
	free(delimiter);
	ctx->contain_quotes = (ft_strchr(*ctx->target.arr, '\'')
			|| ft_strchr(*ctx->target.arr, '"'));
	remove_quotes(&ctx->target);
	return (1);
}

void	handle_child_process(t_heredoc_ctx *ctx, t_ht *env)
{
	signal(SIGINT, handle_heredoc_sigint);
	signal(SIGQUIT, SIG_IGN);
	process_heredoc(ctx, env);
	close(ctx->fd);
	free_char_arr(&ctx->target);
	if (g_signal_int)
		exit(130);
	else
		exit(0);
}

int	handle_heredoc_status(int status, t_heredoc_ctx *ctx, t_ht *env)
{
	free_char_arr(&ctx->target);
	close(ctx->fd);
	if ((WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
			|| (WIFEXITED(status) && WEXITSTATUS(status) == 130))
	{
		g_signal_int = 1;
		unlink(ctx->heredoc);
		free(ctx->heredoc);
		ht_set(env, ft_strdup("?"), ft_strdup("130"));
		return (130);
	}
	ht_set(env, ft_strdup("?"), ft_strdup("0"));
	return (0);
}
