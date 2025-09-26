/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vahstepa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 14:54:25 by vahstepa          #+#    #+#             */
/*   Updated: 2025/09/05 14:55:22 by vahstepa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define _POSIX_C_SOURCE 200809L
# include <stdio.h>
# include <stdlib.h>
# include <signal.h>
# include <curses.h>
# include <term.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <dirent.h>
# include <limits.h>
# include <sys/stat.h>
# include <sys/errno.h>
# include <unistd.h>

# ifdef __APPLE__
#  include <readline/readline.h>
#  include <readline/history.h>
# else
#  include <readline/readline.h>
#  include <readline/history.h>
# endif

# include "libft.h"
# include "get_next_line_bonus.h"
# include "enums.h"
# include "types.h"
# include "minishell_utils.h"
# include "env.h"
# include "token_lst.h"
# include "ast.h"
# include "builtins.h"
# include "expansion.h"

#endif
