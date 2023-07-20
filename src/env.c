/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clbernar <clbernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 13:40:26 by clbernar          #+#    #+#             */
/*   Updated: 2023/07/10 17:53:48 by clbernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// This function diplays the env
void	built_in_env(t_command *cmd, char **env_tab, t_env *env)
{
	if (get_len_tab(cmd->cmd_args) != 1)
	{
		ft_putstr_fd("env must take no options or arguments\n", 2);
		new_return_value(env, "1");
	}
	else
	{
		// Gestion des redirections
		if (cmd)
			display_tab(env_tab);
		new_return_value(env, "0");
	}
}
