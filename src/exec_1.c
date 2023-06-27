/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmirlico <bmirlico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 12:06:57 by bmirlico          #+#    #+#             */
/*   Updated: 2023/06/27 15:07:03 by bmirlico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// fonction d'excution des commandes
void	execution(t_command **cmds)
{
	t_command	*tmp;

	tmp = *cmds;
	while (tmp != NULL)
	{
		if (tmp->cmd_args != NULL)
		{
			if (is_builtin(tmp->cmd_args[0]))
				exec_builtin(tmp);
		}
		tmp = tmp->next;
	}
}

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

// Commande builtin CD
// Cas non gere : cd - (qui retourne ds le $OLDPWD)
void	built_in_cd(t_command *tmp)
{
	int		len_tab;
	char	*error_str;

	len_tab = get_len_tab(tmp->cmd_args);
	error_str = ft_strjoin("cd: ", tmp->cmd_args[1]);
	if (len_tab > 2)
		ft_putstr_fd("cd: too many arguments\n", 2);
	else if (chdir(tmp->cmd_args[1]) == -1)
		perror(error_str);
	free(error_str);
}

// Commande builtin PWD
void	built_in_pwd(void)
{
	char	*cwd;

	cwd = malloc(sizeof(char) * (PATH_MAX));
	if (getcwd(cwd, PATH_MAX) != NULL)
		ft_printf("%s\n", cwd);
	else
		perror("pwd");
	free(cwd);
}
