/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vahstepa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 14:53:54 by vahstepa          #+#    #+#             */
/*   Updated: 2025/09/05 14:53:57 by vahstepa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

int	ft_echo(char **args, t_ht *env);
int	ft_pwd(char **args, t_ht *env);
int	ft_cd(char **args, t_ht *env);
int	ft_unset(char **args, t_ht *env);
int	ft_exit(char **args, t_ht *env);
int	ft_env(char **args, t_ht *env);
int	ft_export(char **args, t_ht *env);

#endif
