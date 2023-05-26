/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmirlico <bmirlico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 14:43:42 by bmirlico          #+#    #+#             */
/*   Updated: 2023/05/26 19:35:14 by bmirlico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_token	*create_list_token(void)
{
	return (NULL);
}

t_token	*create_token(t_token_type type, char *value)
{
	t_token	*new_token;

	new_token = malloc(sizeof(t_token *) * 1);
	if (!new_token)
		return (NULL);
	new_token->type = type;
	new_token->value = value;
	return (new_token);
}

char	*get_token_value(char *input, char *delimiter)
{
	static char	*next_input;
	char		*value;
	int			i;

	i = 0;
	if (!input)
		input = next_input;
	if (!input)
		return (NULL);
	while (input[i] != '\0' && is_delimiter(input[i], delimiter))
		i++;
	while (input[i] != '\0' && is_delimiter(input[i], delimiter))
		i++;
	if (input[i] == '\0')
		i--;
	value = malloc(sizeof(char) * (i + 1));
	if (!value)
		return (NULL);
	ft_strncpy(value, input, i);
	return (value);
}

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

t_token	*lexer(char *input)
{
	t_token	*list;
	char	*token_value;
	char	*token_type;
	char	*input_copy;
	int		i;

	i = 0;
	input_copy = ft_strdup((const char *)input);
	list = create_list_token();
	token_value = get_token_value(input_copy, DELIMITER);
	while (token_value != NULL)
	{
		token_type = get_token_type(token_value);
		create_token(list, token_type, token_value);
		token_value = get_token_value(NULL, DELIMITER);
	}
	free(input_copy);
}
