/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_arr.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vahstepa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 15:25:10 by vahstepa          #+#    #+#             */
/*   Updated: 2025/09/05 15:25:12 by vahstepa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_char_arr(t_char_arr *arr)
{
	arr->arr = NULL;
	arr->size = 0;
}

void	free_char_arr(t_char_arr *arr)
{
	size_t	i;

	i = 0;
	while (i < arr->size)
		free(arr->arr[i++]);
	free(arr->arr);
	arr->arr = NULL;
	arr->size = 0;
}

void	append_to_result(t_char_arr *arr, char *new_item)
{
	char	**tmp;
	size_t	i;

	tmp = (char **)malloc((arr->size + 2) * sizeof (char *));
	i = -1;
	while (++i < arr->size)
		tmp[i] = arr->arr[i];
	tmp[i++] = new_item;
	tmp[i] = NULL;
	free(arr->arr);
	arr->arr = tmp;
	++(arr->size);
}

void	split_and_append(t_char_arr *result, const char *str)
{
	char	**tokens;
	int		i;

	tokens = ft_split(str, ' ');
	if (!tokens)
		return ;
	i = -1;
	while (tokens[++i])
		append_to_result(result, tokens[i]);
	free(tokens);
}

void	split_and_update(char **current, t_char_arr *result, int last_space)
{
	split_and_append(result, *current);
	free(*current);
	if (result->size > 0 && !last_space)
	{
		*current = result->arr[result->size - 1];
		result->size--;
	}
	else
		*current = ft_strdup("");
}
