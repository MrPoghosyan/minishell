/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vahstepa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 15:25:54 by vahstepa          #+#    #+#             */
/*   Updated: 2025/10/05 09:40:06 by vahstepa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_heredoc_name(void)
{
	char	*heredoc;
	char	*sym;
	int		i;

	i = 0;
	while (1)
	{
		sym = ft_itoa(i);
		heredoc = ft_strjoin(".heredoc_", sym);
		free(sym);
		if (!heredoc)
			return (NULL);
		if (access(heredoc, F_OK) != 0)
			break ;
		free(heredoc);
		++i;
	}
	return (heredoc);
}

void	process_heredoc_line(t_heredoc_ctx *ctx, char *line, t_ht *env)
{
	int		i;
	char	*key;
	char	*value;

	i = -1;
	while (line[++i])
	{
		if (!ctx->contain_quotes && line[i] == '$')
		{
			key = extract_var_name(line, &i);
			if (!key)
				continue ;
			value = ht_get(env, key);
			free(key);
			if (!value)
				continue ;
			ft_putstr_fd(value, ctx->fd);
		}
		else
			ft_putchar_fd(line[i], ctx->fd);
	}
	ft_putchar_fd('\n', ctx->fd);
}

void	process_heredoc(t_heredoc_ctx *ctx, t_ht *env)
{
	bool	is_not_a_tty;
	char	*line;

	is_not_a_tty = ht_get(env, "#ISNOTATTY");
	while (1)
	{
		if (is_not_a_tty)
			line = get_prompt_line();
		else
			line = readline("> ");
		if (!line || g_signal_int)
		{
			free(line);
			break ;
		}
		else if (!ft_strcmp(line, *ctx->target.arr))
		{
			free(line);
			break ;
		}
		process_heredoc_line(ctx, line, env);
		free(line);
	}
}

char	*handle_heredoc(char *delimiter, t_ht *env)
{
	t_heredoc_ctx	ctx;
	int				pid;
	int				status;

	if (!init_heredoc_ctx(&ctx, delimiter))
		return (NULL);
	g_signal_int = 0;
	pid = fork();
	if (pid == 0)
		handle_child_process(&ctx, env);
	waitpid(pid, &status, 0);
	if (!handle_heredoc_status(status, &ctx, env))
		return (NULL);
	return (ctx.heredoc);
}
