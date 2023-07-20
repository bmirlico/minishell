/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmirlico <bmirlico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 12:46:59 by bmirlico          #+#    #+#             */
/*   Updated: 2023/07/20 12:47:02 by bmirlico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// fonction qui check si la commande est un builtin ou pas
int	is_builtin(char *cmd)
{
	int	len;

	len = ft_strlen(cmd);
	if (!ft_strncmp(cmd, "echo", len + 1) || !ft_strncmp(cmd, "cd", len + 1)
		|| !ft_strncmp(cmd, "pwd", len + 1)
		|| !ft_strncmp(cmd, "export", len + 1)
		|| !ft_strncmp(cmd, "unset", len + 1)
		|| !ft_strncmp(cmd, "env", len + 1)
		|| !ft_strncmp(cmd, "exit", len + 1))
		return (1);
	else
		return (0);
}

// Fonction qui appelle les fonctions d'execution
// des builtins
void	exec_builtin(t_command *tmp)
{
	int	len;

	len = ft_strlen(tmp->cmd_args[0]);
	if (!ft_strncmp(tmp->cmd_args[0], "cd", len + 1))
		built_in_cd(tmp);
	else if (!ft_strncmp(tmp->cmd_args[0], "pwd", len + 1))
		built_in_pwd();
	else if (!ft_strncmp(tmp->cmd_args[0], "exit", len + 1))
		built_in_exit(tmp);
}
