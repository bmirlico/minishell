/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmirlico <bmirlico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 14:43:42 by bmirlico          #+#    #+#             */
/*   Updated: 2023/06/02 15:04:23 by bmirlico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	lexer_str(t_token **lst, char *input)
{
	t_token	*tmp;
	t_token	*lst_joined;
	t_token	*new;
	char	*join;

	tmp = *lst;
	lst_joined = create_list();
	while (tmp != NULL)
	{
		join = NULL;
		if (tmp->type == T_CMD)
		{
			while (tmp->type == T_CMD && tmp != NULL)
			{
				ft_join_free(&join, tmp->value);
				tmp = tmp->next;
			}
			new = create_token(tmp->type, '\0', join);
			push_to_list(&lst_joined, new);
			free(join);
		}
		else if ((tmp->type == T_LR && tmp->next->type == T_LR)
			|| (tmp->type == T_RR && tmp->next->type == T_RR))
		{
			ft_join_free(&join, tmp->value);
			ft_join_free(&join, tmp->next->value);
			new = create_token(tmp->type, '\0', join);
			push_to_list(&lst_joined, new);
			free(join);
			tmp = tmp->next->next;
		}
		else
			tmp = tmp->next;
	}
}

// fonction qui initialise notre liste et tokenise l'input
// pb a comprendre pk le strdup(value) ne fonctionne pas qd j'utilise readline
void	lexer_char(t_token **lst, char *input)
{
	t_token			*new;
	char			token_value;
	t_token_type	token_type;

	token_value = get_token_value(input);
	while (token_value != 0)
	{
		token_type = get_token_type(token_value);
		new = create_token(token_type, token_value, NULL);
		push_to_list(lst, new);
		token_value = get_token_value(NULL);
	}
	new = create_token(T_EOF, '\0');
	push_to_list(lst, new);
}

// fonction qui reproduit le comportement de strtok
// qui renvoie la string hors delimiteurs
char	get_token_value(char *input)
{
	static char	*next;
	char		c;

	if (input != NULL)
		next = input;
	else if (!next)
		return ('\0');
	if (*next == '\0')
		return ('\0');
	c = *next++;
	return (c);
}

// fonction qui renvoie le type de token associe a un char
t_token_type	get_token_type(char c)
{
	if (c == '|')
		return (T_PIPE);
	else if (c == '<')
		return (T_LR);
	else if (c == '>')
		return (T_RR);
	else if (c == ' ' || c == '\t')
		return (T_SPACE);
	else
		return (T_CMD);
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

//char			*input_copy;
//input_copy = ft_strdup(input);
//printf("INPUT: %s COPY: %s\n", input, input_copy);
//free(input_copy);

//free((*lst)->value);