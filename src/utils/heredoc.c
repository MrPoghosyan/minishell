/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vapoghos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 13:31:04 by vapoghos          #+#    #+#             */
/*   Updated: 2025/10/22 14:11:58 by vapoghos         ###   ########.fr       */
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

void	process_heredoc(t_heredoc_ctx *ctx, t_ht *env)
{
	char	*line;

	while (1)
	{
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

static void	handle_heredoc_child(t_heredoc_ctx *ctx, t_ht *env)
{
	struct sigaction	sa;
	struct sigaction	sa_quit;

	g_signal_int = 0;
	sa.sa_handler = handle_heredoc_sigint;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
	sa_quit.sa_handler = SIG_IGN;
	sigemptyset(&sa_quit.sa_mask);
	sa_quit.sa_flags = 0;
	sigaction(SIGQUIT, &sa_quit, NULL);
	process_heredoc(ctx, env);
	close(ctx->fd);
	if (g_signal_int)
		exit(130);
	exit(0);
}

char	*handle_heredoc(char *delimiter, t_ht *env)
{
	t_heredoc_ctx		ctx;
	pid_t				pid;
	int					status;
	struct sigaction	sa_ignore;
	struct sigaction	sa_old;

	if (!init_heredoc_ctx(&ctx, delimiter))
		return (NULL);
	g_signal_int = 0;
	pid = fork();
	if (pid == 0)
		handle_heredoc_child(&ctx, env);
	sa_ignore.sa_handler = SIG_IGN;
	sigemptyset(&sa_ignore.sa_mask);
	sa_ignore.sa_flags = 0;
	sigaction(SIGINT, &sa_ignore, &sa_old);
	waitpid(pid, &status, 0);
	sigaction(SIGINT, &sa_old, NULL);
	if (handle_heredoc_status(status, &ctx, env) == 130)
	{
		rl_replace_line("", 0);
		return (NULL);
	}
	return (ctx.heredoc);
}
