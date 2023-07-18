/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmirlico <bmirlico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 14:49:29 by bmirlico          #+#    #+#             */
/*   Updated: 2023/07/18 15:35:28 by bmirlico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// fonction qui gere l'execution de la commande et les differents
// cas d'erreurs possibles avec les exit status associes
// ATTENTION A BIEN FREE TOUTES LES LISTES, etc (pas fait encore)
void	handle_exec(char *cmd_p, t_command *tmp, char **env)
{
	struct stat	buf;
	char		*error;

	error = NULL;
	if (stat(cmd_p, &buf) == 0 && S_ISDIR(buf.st_mode))
	{
		error = ft_strjoin(cmd_p, ": Is a directory\n");
		ft_putstr_fd(error, 2);
		free(error);
		free(cmd_p);
		exit(126);
	}
	else if (access(cmd_p, F_OK) == -1)
		if_file_unexists(cmd_p, error, tmp, env);
	else if (access(cmd_p, F_OK) == 0)
		if_file_exists(cmd_p, error, tmp, env);
}

// fonction qui gere le cas ou le fichier n'existe pas
void	if_file_unexists(char *cmd_p, char *error, t_command *tmp, char **env)
{
	if (count_slash(tmp->cmd_args[0]) > 0 || !is_path_set(env))
	{
		error = ft_strjoin(cmd_p, ": No such file or directory\n");
		ft_putstr_fd(error, 2);
	}
	else
	{
		error = ft_strjoin(cmd_p, ": command not found\n");
		ft_putstr_fd(error, 2);
	}
	free(error);
	free(cmd_p);
	exit(127);
}

// fonction qui gere le cas ou le fichier existe et est executable ou non
void	if_file_exists(char *cmd_p, char *error, t_command *tmp, char **env)
{
	if (access(cmd_p, X_OK) == -1)
	{
		error = ft_strjoin(cmd_p, ": Permission denied\n");
		ft_putstr_fd(error, 2);
		free(error);
		free(cmd_p);
		exit(126);
	}
	else
	{
		execve(cmd_p, tmp->cmd_args, env);
		free(cmd_p);
		exit(1);
	}
}
