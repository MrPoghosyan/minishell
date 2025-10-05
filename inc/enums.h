/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enums.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vahstepa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 14:53:14 by vahstepa          #+#    #+#             */
/*   Updated: 2025/09/05 14:53:16 by vahstepa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENUMS_H
# define ENUMS_H

typedef enum e_cmd_token_types	t_cmd_token_types;
typedef enum e_quoting_state	t_quoting_state;

enum e_cmd_token_types
{
	T_NONE,
	T_WORD,
	T_CMD,
	T_PIPE,
	T_INPUT,
	T_OUTPUT,
	T_APPEND,
	T_HEREDOC,
	T_AND,
	T_OR,
	T_OPEN_PARENTHESIS,
	T_CLOSE_PARENTHESIS,
	T_UNHANDLED,
};

enum e_quoting_state
{
	Q_NONE,
	Q_SINGLE,
	Q_DOUBLE,
};

#endif
