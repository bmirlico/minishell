/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exec_3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmirlico <bmirlico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 18:02:58 by bmirlico          #+#    #+#             */
/*   Updated: 2023/07/18 18:06:22 by bmirlico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// fonction qui free uniquement les elements de la structure vars hors listes
void	free_pipex(t_pipex vars)
{
	free_pipefd(vars.pipefd, vars.nb_pipes);
	if (vars.path != NULL)
	{
		free(vars.path);
		free_tab(vars.paths);
	}
}
