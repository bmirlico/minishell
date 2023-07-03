/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clbernar <clbernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 20:01:19 by clbernar          #+#    #+#             */
/*   Updated: 2023/07/03 15:03:09 by clbernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// This function malloc the new string and replace the old string by the new one
void	expand_str_tab(char **tab, int i)
{
	int		new_len;
	char	*new;
	int		var_env_len;

	var_env_len = get_varenv_value_len(tab[i]);
	new_len = ft_strlen(tab[i]) - get_varname_len(tab[i]) + var_env_len;
	new = NULL;
	new = malloc(sizeof(char) * (new_len + 1));
	if (new == NULL)
		return ;
	new[new_len] = '\0';
	new_str(tab[i], new);
	if (tab[i] != NULL)
		free(tab[i]);
	tab[i] = new;
}

// This function checks if each line of the args tab needs to be modified
void	expand_tab(char **tab)
{
	int	i;

	i = 0;
	if (tab == NULL)
		return ;
	while (tab[i])
	{
		if (to_be_modified(tab[i]) == 0)
			expand_str_tab(tab, i);
		i++;
	}
}

// This function is called when a str from the redirection list needs to be
// expand. It create a new str that will be the new string
// and replaces the old one
void	expand_rdir_lst(t_token *rdir)
{
	int		new_len;
	char	*new;
	int		var_env_len;

	var_env_len = get_varenv_value_len(rdir->str);
	new_len = ft_strlen(rdir->str) - get_varname_len(rdir->str) + var_env_len;
	new = NULL;
	new = malloc(sizeof(char *) * (new_len + 1));
	if (new == NULL)
		return ;
	new[new_len] = '\0';
	new_str(rdir->str, new);
	if (rdir->str)
		free(rdir->str);
	rdir->str = new;
}

// This function checks each string in the redirection list to determine
// if it needs to be expand or not
void	expand_rdir(t_token	*redirections)
{
	t_token			*tmp;
	t_token_type	prev_type;

	prev_type = 0;
	tmp = redirections;
	if (tmp == NULL)
		return ;
	while (tmp != NULL)
	{
		if (to_be_modified(tmp->str) == 0 && prev_type != T_HEREDOC)
			expand_rdir_lst(tmp);
		prev_type = tmp->type;
		tmp = tmp->next;
	}
}

// This function checks the command list to replace the strings
// that need to be replace
void	expand(t_command **cmds)
{
	t_command	*tmp;

	tmp = *cmds;
	while (tmp != NULL)
	{
		expand_tab(tmp->cmd_args);
		expand_rdir(tmp->redirections);
		tmp = tmp->next;
	}
	tmp = *cmds;
	while (tmp != NULL)
	{
		remove_quotes_tab(tmp->cmd_args);
		remove_quotes_rdir(tmp->redirections);
		tmp = tmp->next;
	}
	clean_lst(*cmds);
}
