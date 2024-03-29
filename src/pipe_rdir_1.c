/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_rdir_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmirlico <bmirlico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 15:47:08 by bmirlico          #+#    #+#             */
/*   Updated: 2023/07/18 19:59:20 by bmirlico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// redirige la stdin et stdout en fonction de l'index de la commande
void	pipe_redirection(t_pipex vars, t_token **rdirs, int i)
{
	if (i == 0)
		pipe_first(vars, i, rdirs);
	else if (i == vars.nb_cmds - 1)
		pipe_last(vars, i, rdirs);
	else
		pipe_between(vars, i, rdirs);
}

// redirige pour la 1ere commande
void	pipe_first(t_pipex vars, int i, t_token **rdirs)
{
	t_token	*last_infile;
	t_token	*last_outfile;

	init_last_rdirs(&last_infile, &last_outfile, rdirs);
	if (last_infile != NULL)
	{
		if (dup2(last_infile->fd, STDIN_FILENO) < 0)
			exit(EXIT_FAILURE);
	}
	if (last_outfile != NULL)
	{
		if (dup2(last_outfile->fd, STDOUT_FILENO) < 0)
			exit(EXIT_FAILURE);
	}
	else if (!last_outfile && vars.nb_pipes > 0)
	{
		if (dup2(vars.pipefd[i][1], STDOUT_FILENO) < 0)
			exit(EXIT_FAILURE);
	}
	if (vars.nb_pipes > 0)
	{
		if (close(vars.pipefd[i][0]) < 0 || close(vars.pipefd[i][1]) < 0)
			exit(EXIT_FAILURE);
	}
	close_rdirs(rdirs);
}

// redirige pour la derniere commande
// Pk en fermant le pipefd[i - 1][0] on a une error bad file descriptor ?
void	pipe_last(t_pipex vars, int i, t_token **rdirs)
{
	t_token	*last_infile;
	t_token	*last_outfile;

	init_last_rdirs(&last_infile, &last_outfile, rdirs);
	if (last_infile != NULL)
	{
		if (dup2(last_infile->fd, STDIN_FILENO) < 0)
			exit(EXIT_FAILURE);
	}
	else if (!last_infile && vars.nb_pipes > 0)
	{
		if (dup2(vars.pipefd[i - 1][0], STDIN_FILENO) < 0)
			exit(EXIT_FAILURE);
	}
	if (last_outfile != NULL)
	{
		if (dup2(last_outfile->fd, STDOUT_FILENO) < 0)
			exit(EXIT_FAILURE);
	}
	if (close(vars.pipefd[i - 1][1]) < 0 || close(vars.pipefd[i - 1][0]) < 0)
		exit(EXIT_FAILURE);
	close_rdirs(rdirs);
}

// redirige pour les commandes entre la 1ere et la derniere
void	pipe_between(t_pipex vars, int i, t_token **rdirs)
{
	t_token	*last_infile;
	t_token	*last_outfile;

	init_last_rdirs(&last_infile, &last_outfile, rdirs);
	pipe_between_infile(last_infile, vars, i);
	pipe_between_outfile(last_outfile, vars, i);
	if (vars.nb_pipes > 0)
	{
		if (close(vars.pipefd[i - 1][0]) < 0 || close(vars.pipefd[i][1]) < 0
			|| close(vars.pipefd[i][0]) < 0 || close(vars.pipefd[i - 1][1]) < 0)
			exit(EXIT_FAILURE);
	}
	close_rdirs(rdirs);
}

// fonction qui gere la partie redirection infiles pour les commandes
// intermédiaires d'un pipe (entre la 1ere et la derniere)
void	pipe_between_infile(t_token *last_infile, t_pipex vars, int i)
{
	if (last_infile != NULL)
	{
		if (dup2(last_infile->fd, STDIN_FILENO) < 0)
			exit(EXIT_FAILURE);
	}
	else if (!last_infile && vars.nb_pipes > 0)
	{
		if (dup2(vars.pipefd[i - 1][0], STDIN_FILENO) < 0)
			exit(EXIT_FAILURE);
	}
}
