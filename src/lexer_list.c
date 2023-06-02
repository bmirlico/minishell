/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmirlico <bmirlico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 12:48:22 by bmirlico          #+#    #+#             */
/*   Updated: 2023/06/02 14:35:09 by bmirlico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// cree une nouvelle liste
t_token	*create_list(void)
{
	return (NULL);
}

// fonction qui cree un element t_token avec un type et une valeur
// pb a comprendre pk le strdup(value) ne fonctionne pas qd j'utilise readline
t_token	*create_token(t_token_type type, char c, char *str)
{
	t_token	*new_token;

	new_token = malloc(sizeof(t_token) * 1);
	if (!new_token)
		return (NULL);
	new_token->type = type;
	new_token->value = c;
	new_token->str = str;
	new_token->next = NULL;
	return (new_token);
}

// ajoute un nouvel element a une liste chainee
void	push_to_list(t_token **lst, t_token *new)
{
	t_token	*tmp;

	tmp = *lst;
	if (!*lst)
		*lst = new;
	else
	{
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new;
	}
}

// fonction qui free la liste du lexer
void	free_list(t_token **lst)
{
	t_token	*tmp;

	tmp = *lst;
	while (*lst != NULL)
	{
		tmp = (*lst)->next;
		free(*lst);
		*lst = tmp;
	}
}
