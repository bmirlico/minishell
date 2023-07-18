/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmirlico <bmirlico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 12:33:40 by bmirlico          #+#    #+#             */
/*   Updated: 2023/07/17 23:27:11 by bmirlico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// fonction d'excution des commandes
// A quel moment vient le syntax error rdir => hypothèse : ds le child process
void	execution(char *input, t_command **cmds, char **env)
{
	t_command	*tmp;
	t_pipex		vars;

	if (input == NULL)
		return ;
	tmp = *cmds;
	init_struct(&vars, cmds, input);
	while (tmp != NULL)
	{
		open_rdirs(&(tmp->redirections));
		if (vars.nb_pipes == 0 && is_builtin(tmp->cmd_args[0]))
			exec_builtin(tmp);
		else if (vars.nb_pipes >= 0)
		{
			//printf("OK\n");
			pipex(tmp, vars, &(tmp->redirections), env);
		}
		tmp = tmp->next;
	}
	free_pipefd(vars.pipefd, vars.nb_pipes);
}

// fonction qui réalise le fork et l'exécution des commandes ds un child process
void	pipex(t_command *tmp, t_pipex vars, t_token **rdirs, char **env)
{
	pid_t	pid;

	init_pipe(vars, tmp->index);
	pid = fork();
	if (pid == -1)
		return (perror("fork"));
	else if (pid == 0)
		child_process(tmp, vars, rdirs, env);
	else if (pid > 0)
		parent_process(tmp, vars, pid);
}

// fonction qui gere le process child, i.e. redirige les fd et execute la cmd
void	child_process(t_command *tmp, t_pipex vars, t_token **rdirs, char **env)
{
	handle_errors_rdirs(tmp, vars, rdirs);
	//ft_putstr_fd("OK2\n", 2);
	//printf("index: %d\n", tmp->index);
	pipe_redirection(vars, rdirs, tmp->index);
	//ft_putstr_fd("ERROR\n", 2);
	if (is_builtin(tmp->cmd_args[0]))
	{
		//printf("ERROR2\n");
		exec_builtin(tmp);
	}
	else
	{
		//printf("OK3\n");
		exec_cmd(tmp, env);
	}
}

// fonction qui gere le process parent et permet de récupérer le code de retour
// du child process
void	parent_process(t_command *tmp, t_pipex vars, pid_t pid)
{
	int	status;
	int	exit_code;
	int	pid_child;

	close_previous_pipe(vars, tmp->index);
	pid_child = waitpid(pid, &status, 0);
	if (WIFEXITED(status) && tmp->index == vars.nb_cmds - 1)
	{
		exit_code = WEXITSTATUS(status);
		printf("Child pid: %d ; Exit status: %d\n", pid_child, exit_code);
	}
	close_rdirs(&(tmp->redirections));
}

// fonction qui recupere le path de l'env et le split
// pour préparer l'execution de la commande
void	exec_cmd(t_command *tmp, char **env)
{
	char		*path;
	char		**paths;
	char		*cmd_with_path;

	//ft_putstr_fd("OK4\n", 2);
	path = get_path(env);
	paths = ft_split(path, ':');
	if (count_slash(tmp->cmd_args[0]) > 0 || path == NULL)
		cmd_with_path = ft_strdup(tmp->cmd_args[0]);
	else
	{
		cmd_with_path = get_cmd_with_path(tmp->cmd_args[0], paths);
		if (cmd_with_path == NULL)
			cmd_with_path = ft_strdup("");
	}
	handle_exec(cmd_with_path, tmp, env);
}
