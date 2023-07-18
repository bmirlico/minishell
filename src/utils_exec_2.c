/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exec_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmirlico <bmirlico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 15:06:14 by bmirlico          #+#    #+#             */
/*   Updated: 2023/07/12 16:07:57 by bmirlico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// fonction qui recupere le path de l'env
char	*get_path(char **env)
{
	int		i;
	char	*path;

	i = 0;
	while (env[i] != NULL)
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
		{
			path = ft_strdup(env[i] + 5);
			return (path);
		}
		i++;
	}
	return (NULL);
}

// fonction utilise pour gerer le cas de unset $PATH
int	is_path_set(char **env)
{
	int		i;

	i = 0;
	while (env[i] != NULL)
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
			return (1);
		i++;
	}
	return (0);
}

// fonction qui recupere la commande et le path concatene
char	*get_cmd_with_path(char *cmd, char **paths)
{
	int		i;
	char	*cmd_with_path;

	i = 0;
	while (paths[i] != NULL)
	{
		cmd_with_path = ft_strjoin3(paths[i], "/", cmd);
		if (access(cmd_with_path, F_OK) == 0)
			return (cmd_with_path);
		free(cmd_with_path);
		i++;
	}
	return (NULL);
}
