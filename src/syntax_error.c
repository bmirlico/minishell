/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmirlico <bmirlico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 11:28:07 by bmirlico          #+#    #+#             */
/*   Updated: 2023/05/31 13:48:55 by bmirlico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	check_syntax(char *input)
{
	if (check_unclosed_quotes(input) || check_special_chars(input)
		|| check_pipe_and_redir(input))
	{
		ft_printf("Syntax error.\n");
		return (1);
	}
	else
		return (0);
}

int	check_unclosed_quotes(char *input)
{
	int	num_s;
	int	num_d;

	num_s = get_num_quotes(input, 39);
	num_d = get_num_quotes(input, 34);
	if (num_s % 2 != 0 || num_d % 2 != 0)
		return (1);
	else
		return (0);
}

int	get_num_quotes(char *input, int c)
{
	int	i;
	int	num;

	i = 0;
	num = 0;
	while (input[i] != '\0')
	{
		if (input[i] == (char)c)
			num++;
		i++;
	}
	return (num);
}

int	check_special_chars(char *input)
{
	int	i;

	i = 0;
	while (input[i] != '\0')
	{
		if (is_delimiter(input[i], SPECIAL_CHARS))
			return (1);
		i++;
	}
	return (0);
}

int	check_pipe_and_redir(char *input)
{
	if (find_chars(input) == 0)
		return (1);
	else
		return (0);
}

int	find_chars(char *input)
{
	int	i;

	i = 0;
	while (input[i] != '\0')
	{
		if (!(input[i] == '|' || input[i] == '>' || input[i] == '<'))
			return (1);
		else if (!(input[i] == '>' && input[i + 1] == '>'))
			return (1);
		else if (!(input[i] == '<' && input[i + 1] == '<'))
			return (1);
		i++;
	}
	return (0);
}
