/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmirlico <bmirlico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 14:43:42 by bmirlico          #+#    #+#             */
/*   Updated: 2023/05/26 16:48:42 by bmirlico         ###   ########.fr       */
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
	int		i;
	char	*value;

	i = 0;
	if (!input)
		return (NULL);
	while (input[i] != '\0' && !is_delimiter(input[i], delimiter))
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
		
	}
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

char	*get_token_type(char *input, char *delimiter)
{
	int	i;

	i = 0;
	if (input[i] == '|')
		return (T_PIPE);
	else if (input[i] == '<')
		return (T_LR);
	else if (input[i] == '>')
		return (T_RR);
	else if (input[i] == '<<')
		return (T_HEREDOC);
	else if (input[i] == '>>')
		return (T_APPEND);
	else if (ft_isalpha((int)input[i]))
		return (T_WORD);
}

t_token	**lexer(char *input)
{
	t_token	**list;
	int		i;

	
}
