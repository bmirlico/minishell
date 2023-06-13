/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmirlico <bmirlico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 16:42:44 by bmirlico          #+#    #+#             */
/*   Updated: 2023/06/13 16:43:28 by bmirlico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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
