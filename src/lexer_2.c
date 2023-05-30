/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmirlico <bmirlico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 11:46:13 by bmirlico          #+#    #+#             */
/*   Updated: 2023/05/30 12:12:53 by bmirlico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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

// fonction qui indique si le caractere donne est un delimiteur ou non
int	is_delimiter(char c, char *delimiter)
{
	int	i;

	i = 0;
	while (delimiter[i] != '\0')
	{
		if (c == delimiter[i])
			return (1);
		i++;
	}
	return (0);
}

// fonction qui copie une string ds une autre sur une longueur donnee
void	ft_strncpy(char *value, char *input, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		value[i] = input[i];
		i++;
	}
	value[i] = '\0';
}

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

//free((*lst)->value);