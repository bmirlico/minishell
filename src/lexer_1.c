/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmirlico <bmirlico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 14:43:42 by bmirlico          #+#    #+#             */
/*   Updated: 2023/05/30 13:36:06 by bmirlico         ###   ########.fr       */
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
t_token	*create_token(t_token_type type, char *value)
{
	t_token	*new_token;

	new_token = malloc(sizeof(t_token) * 1);
	if (!new_token)
		return (NULL);
	new_token->type = type;
	new_token->value = value;
	new_token->next = NULL;
	return (new_token);
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
// pb a comprendre pk le strdup(value) ne fonctionne pas qd j'utilise readline
void	lexer(t_token **lst, char *input)
{
	t_token			*new;
	char			*token_value;
	t_token_type	token_type;

	token_value = get_token_value(input, DELIMITER);
	while (token_value != NULL)
	{
		token_type = get_token_type(token_value);
		new = create_token(token_type, token_value);
		push_to_list(lst, new);
		token_value = get_token_value(NULL, DELIMITER);
	}
	new = create_token(T_EOF, "");
	push_to_list(lst, new);
}

//char			*input_copy;
//input_copy = ft_strdup(input);
//printf("INPUT: %s COPY: %s\n", input, input_copy);
//free(input_copy);