/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_display.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clbernar <clbernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 14:16:20 by clbernar          #+#    #+#             */
/*   Updated: 2023/07/18 13:47:30 by clbernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// Displays the env when export command has no arguments
void	display_export(t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp != NULL)
	{
		ft_printf("export %s=\"%s\"\n", tmp->var_name, tmp->var_value);
		tmp = tmp->next;
	}
	new_return_value(env, "0");
}

// Displays an error_message due to the varenv name
void	display_not_a_valid_identifier(char *str, t_env *env)
{
	char	*tmp1;
	char	*tmp2;

	tmp1 = NULL;
	tmp2 = NULL;
	tmp1 = ft_strjoin("export : ", str);
	tmp2 = ft_strjoin(tmp1, " : not a valid identifier\n");
	ft_putstr_fd(tmp2, 2);
	if (tmp1 != NULL)
		free(tmp1);
	if (tmp2 != NULL)
		free(tmp2);
	new_return_value(env, "1");
}

// This function checks if the var_env that is about to be export
// already exist or not
int	already_exist(t_env *env, char *declaration)
{
	int		i;
	char	*name;
	t_env	*tmp;

	i = 0;
	name = NULL;
	tmp = env;
	while (declaration[i] != '=')
		i++;
	name = ft_substr(declaration, 0, i);
	// ft_printf("%s\n", name);
	while (tmp != NULL)
	{
		if (ft_strncmp(tmp->var_name, name, ft_strlen(name) + 1) == 0)
		{
			if (name != NULL)
				free(name);
			return (1);
		}
		tmp = tmp->next;
	}
	if (name != NULL)
		free(name);
	return (0);
}
