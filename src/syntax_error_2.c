/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmirlico <bmirlico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 16:19:04 by clbernar          #+#    #+#             */
/*   Updated: 2023/06/21 12:12:34 by bmirlico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// Cette fonction check si il y a une syntax_error
// du a un backslash , a un ou plusieurs carcteres speciaux
// en dehors de quotes, ou un a des quotes non fermees
int	check_special_char(char *input)
{
	int	i;
	int	prev_state;

	prev_state = CLOSED;
	i = 0;
	while (input[i])
	{
		if (input[i] == '\\')
			return (0);
		prev_state = quotes_state(input[i], prev_state);
		if (prev_state == CLOSED && is_special_char(input[i]) == 0)
			return (0);
		i++;
	}
	if (prev_state != CLOSED)
		return (0);
	return (1);
}

// -Cas particulier avec 0 seul dans une variable d'environnement
// Il revient au shell par defaut
// -Cas particulier # seul dans une var d'environnement affiche
// 0: command not found
// Rajouter le cas de { ouverte simple SEULEMENT dans la
// partie commande et pas redir
int	check_bad_env_variable(char *input)
{
	int	i;
	int	var_env;

	i = 0;
	var_env = CLOSED;
	while (input[i])
	{
		if (input[i] == '$' && input[i + 1] == '{' && input[i + 2] == '}')
			return (2);
		else if (input[i] == '$' && input[i + 1] == '{')
		{
			var_env = SINGLE_OPEN;
			i++;
		}
		else if (var_env == SINGLE_OPEN && input[i] == '}')
			var_env = CLOSED;
		else if (var_env == SINGLE_OPEN && ft_isalnum(input[i]) != 1)
			return (2);
		i++;
	}
	if (var_env == SINGLE_OPEN)
		return (0);
	return (1);
}

int	check_rdir(int rdir)
{
	if (rdir != CLOSED)
		return (0);
	else
		return (1);
}
