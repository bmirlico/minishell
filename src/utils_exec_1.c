/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exec_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmirlico <bmirlico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 15:48:30 by bmirlico          #+#    #+#             */
/*   Updated: 2023/07/12 15:13:34 by bmirlico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// fonction qui initialise la structure t_pipex qui va contenir 
// les vars nb_pipes et le tableau de pipes pour l'execution des commandes
void	init_struct(t_pipex *vars, t_command **cmds, char *input)
{
	get_index_cmds(cmds);
	vars->nb_pipes = get_nb_pipes(input);
	vars->nb_cmds = vars->nb_pipes + 1;
	vars->pipefd = init_pipefd(vars->nb_pipes);
}

// fonction qui index les éléments de la liste chainée t_command
// sert à garder trace du numéro de la commande pour l'execution
void	get_index_cmds(t_command **cmds)
{
	t_command	*tmp;
	int			i;

	tmp = *cmds;
	i = 0;
	while (tmp != NULL)
	{
		tmp->index = i;
		tmp = tmp->next;
		i++;
	}
}

// fonction qui compte le nb de pipes présents ds l'input
int	get_nb_pipes(char *input)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	if (input == NULL)
		return (count);
	while (input[i])
	{
		if (input[i] == '|')
			count++;
		i++;
	}
	return (count);
}

//write a function that counts the number of / in the string
// DO NOT KNOW YET IF I WILL USE IT
int	count_slash(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	if (!str)
		return (count);
	while (str[i])
	{
		if (str[i] == '/')
			count++;
		i++;
	}
	return (count);
}

// strjoin modifie avec 3 chaines de caracteres
char	*ft_strjoin3(char *str1, char *str2, char *str3)
{
	char	*tmp;
	char	*tmp2;

	tmp = ft_strjoin((const char *)str1, (const char *)str2);
	tmp2 = ft_strjoin((const char *)tmp, (const char *)str3);
	free(tmp);
	return (tmp2);
}
