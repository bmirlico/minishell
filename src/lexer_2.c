/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmirlico <bmirlico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 16:45:08 by bmirlico          #+#    #+#             */
/*   Updated: 2023/06/13 16:53:17 by bmirlico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// fonction qui groupe caractere par caractere pour former une
// string, et free bien la chaine d'avant
void	ft_join_free(char **join, char c)
{
	int		i;
	int		len;
	char	*str_j;

	i = 0;
	len = ft_strlen(*join);
	if (*join == NULL)
		str_j = char_to_str(c);
	else
	{
		str_j = malloc(sizeof(char) * (len + 1 + 1));
		if (!str_j)
			return ;
		while (i < len)
		{
			str_j[i] = (*join)[i];
			i++;
		}
		str_j[i] = c;
		str_j[i + 1] = '\0';
	}
	free(*join);
	*join = str_j;
}

// fonction qui convertit un char en str
char	*char_to_str(char c)
{
	char	*str;

	str = malloc(sizeof(char) * 2);
	if (!str)
		return (NULL);
	str[0] = c;
	str[1] = '\0';
	return (str);
}

// fonction qui initialise notre liste et tokenise l'input
// le lexer tokenise caractere par caractere et permet de gerer les espaces
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
	new = create_token(T_EOF, '\0', NULL);
	push_to_list(lst, new);
}

// fonction qui reproduit le comportement de strtok
// mais qui ne ne renvoie pas une string mais le char suivant a chaque
// appel de la fonction (utilisation d'une var statique) 
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
