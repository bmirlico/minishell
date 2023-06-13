/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmirlico <bmirlico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 17:45:42 by bmirlico          #+#    #+#             */
/*   Updated: 2023/06/12 15:17:27 by bmirlico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// fonction de parsings de commandes qui regroupe les T_CMD dans un
// tableau de tableaux
// LEAKS A DEBUGGER
void	parser(t_token **lst_j, t_command **cmds)
{
	t_token		*tmp;
	char		**tab;
	t_token		*redirs;
	t_token		*redirs_elem;
	t_command	*new;

	tmp = *lst_j;
	tab = NULL;
	redirs = create_list_lexer();
	redirs_elem = NULL;
	while (tmp != NULL)
	{
		if (tmp->type == T_LR || tmp->type == T_RR
			|| tmp->type == T_HEREDOC || tmp->type == T_APPEND
			|| tmp->type == T_INFILE || tmp->type == T_LIMITOR
			|| tmp->type == T_OUTFILE || tmp->type == T_OUTFILE_APPEND)
		{
			redirs_elem = create_token(tmp->type, tmp->value, tmp->str);
			push_to_list(&redirs, redirs_elem);
			tmp = tmp->next;
		}
		else if (tmp->type == T_CMD)
		{
			while (tmp->type == T_CMD)
			{
				fill_tab_free(&tab, tmp->str);
				tmp = tmp->next;
			}
		}
		else if (tmp->type == T_PIPE || tmp->type == T_EOF)
		{
			new = create_command(tab, redirs);
			push_to_parser(cmds, new);
			tab = NULL;
			redirs = create_list_lexer();
			tmp = tmp->next;
		}
	}
}

void	fill_tab_free(char ***tab, char *str)
{
	char	**tmp;
	int		len_tab;
	int		len;
	int		i;

	i = 0;
	len = ft_strlen(str);
	len_tab = get_len_tab(*tab);
	tmp = malloc(sizeof(char *) * (len_tab + 1 + 1));
	if (!tmp)
		return ;
	if (*tab != NULL)
	{
		while (i < len_tab)
		{
			tmp[i] = (*tab)[i];
			i++;
		}
	}
	tmp[i] = malloc(sizeof(char *) * (len + 1));
	if (!tmp[i])
		return ;
	ft_strncpy(tmp[i], str, len);
	tmp[++i] = NULL;
	*tab = tmp;
}

int	get_len_tab(char **tab)
{
	int	len;
	int	i;

	len = 0;
	i = 0;
	if (tab == NULL)
		return (len);
	while (tab[i] != NULL)
	{
		len++;
		i++;
	}
	return (len);
}

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i] != NULL)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}
