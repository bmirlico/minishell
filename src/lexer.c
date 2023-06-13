/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmirlico <bmirlico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 14:43:42 by bmirlico          #+#    #+#             */
/*   Updated: 2023/06/07 13:28:41 by bmirlico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// fonction qui regroupe les elements de la liste renvoyee par le lexer_char
// pour avoir cette fois des strings
void	lexer_str(t_token **lst, t_token **lst_j)
{
	t_token	*tmp;
	t_token	*new;
	char	*join;

	tmp = *lst;
	while (tmp != NULL)
	{
		join = NULL;
		if (tmp->type == T_CMD)
		{
			while (tmp->type == T_CMD)
			{
				ft_join_free(&join, tmp->value);
				tmp = tmp->next;
			}
			new = create_token(T_CMD, '\0', join);
			push_to_list(lst_j, new);
		}
		else if ((tmp->type == T_LR && tmp->next->type == T_LR)
			|| (tmp->type == T_RR && tmp->next->type == T_RR))
		{
			ft_join_free(&join, tmp->value);
			ft_join_free(&join, tmp->next->value);
			if (tmp->type == T_LR)
				tmp->type = T_HEREDOC;
			else if (tmp->type == T_RR)
				tmp->type = T_APPEND;
			new = create_token(tmp->type, '\0', join);
			push_to_list(lst_j, new);
			tmp = tmp->next->next;
		}
		else if (tmp->type == T_SPACE)
			tmp = tmp->next;
		else
		{
			ft_join_free(&join, tmp->value);
			new = create_token(tmp->type, '\0', join);
			push_to_list(lst_j, new);
			tmp = tmp->next;
		}
	}
	tokenize_remaining(lst_j);
}

void	tokenize_remaining(t_token **lst_j)
{
	t_token	*tmp;

	tmp = *lst_j;
	while (tmp != NULL)
	{
		if (tmp->type == T_LR && tmp->next->type == T_CMD)
			tmp->next->type = T_INFILE;
		else if (tmp->type == T_RR && tmp->next->type == T_CMD)
			tmp->next->type = T_OUTFILE;
		else if (tmp->type == T_HEREDOC && tmp->next->type == T_CMD)
			tmp->next->type = T_LIMITOR;
		else if (tmp->type == T_APPEND && tmp->next->type == T_CMD)
			tmp->next->type = T_OUTFILE_APPEND;
		tmp = tmp->next;
	}
}

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
// mais qui ne ne renvoie pas un string mais le char suivant a chaque
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

// fonction qui indique si le caractere donne est un delimiteur ou non
// fonction NON UTILISEE pour le moment
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

	if (!value || !input)
		return ;
	i = 0;
	while (i < len)
	{
		value[i] = input[i];
		i++;
	}
	value[i] = '\0';
}
