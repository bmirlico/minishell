/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmirlico <bmirlico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 14:43:42 by bmirlico          #+#    #+#             */
/*   Updated: 2023/05/29 17:30:29 by bmirlico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// cree une nouvelle liste
t_token	*create_list(void)
{
	return (NULL);
}

// fonction qui cree un element t_token avec un type et une valeur
t_token	*create_token(t_token_type type, char *value)
{
	t_token	*new_token;

	new_token = malloc(sizeof(t_token) * 1);
	if (!new_token)
		return (NULL);
	new_token->type = type;
	new_token->value = ft_strdup((const char *)value);
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

// fonction qui reproduit le comportement de strtok
// qui renvoie la string hors delimiteurs
char	*get_token_value(char *input, char *delimiter)
{
	static char	*next;
	char		*start;

	if (input != NULL)
		next = input;
	else if (!next)
		return (NULL);
	while (*next && is_delimiter(*next, delimiter))
		next++;
	if (*next == '\0')
		return (NULL);
	start = next;
	while (*next && !is_delimiter(*next, delimiter))
		next++;
	if (*next != '\0')
		*next++ = '\0';
	return (start);
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

// fonction qui renvoie le type de token associe a une string
t_token_type	get_token_type(char *value)
{
	int	len;

	len = ft_strlen(value);
	if (ft_strncmp(value, "|", len) == 0)
		return (T_PIPE);
	else if (ft_strncmp(value, "<", len) == 0)
		return (T_LR);
	else if (ft_strncmp(value, ">", len) == 0)
		return (T_RR);
	else if (ft_strncmp(value, "<<", len) == 0)
		return (T_HEREDOC);
	else if (ft_strncmp(value, ">>", len) == 0)
		return (T_APPEND);
	else
		return (T_WORD);
}

// fonction qui initialise notre liste et tokenise l'input
void	lexer(t_token **lst, char *input)
{
	char			*token_value;
	t_token_type	token_type;
	char			*input_copy;
	t_token			*new;

	input_copy = ft_strdup((const char *)input);
	token_value = get_token_value(input_copy, DELIMITER);
	while (token_value != NULL)
	{
		token_type = get_token_type(token_value);
		new = create_token(token_type, token_value);
		push_to_list(lst, new);
		token_value = get_token_value(NULL, DELIMITER);
	}
	new = create_token(T_EOF, "");
	push_to_list(lst, new);
	free(input_copy);
}

void	free_list(t_token **lst)
{
	t_token	*tmp;

	tmp = *lst;
	while (*lst != NULL)
	{
		tmp = (*lst)->next;
		free((*lst)->value);
		free(*lst);
		*lst = tmp;
	}
}
