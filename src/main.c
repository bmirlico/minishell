/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmirlico <bmirlico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 14:25:42 by bmirlico          #+#    #+#             */
/*   Updated: 2023/05/30 13:28:23 by bmirlico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	display_list(t_token **lst)
{
	t_token	*tmp;

	tmp = *lst;
	while (tmp != NULL)
	{
		ft_printf("Type: %d ; Value: %s\n", tmp->type,
			tmp->value);
		tmp = tmp->next;
	}
}

// main du projet minishell
int	main(int ac, char **av)
{
	char	*g_commands;
	t_token	*lst;

	(void)av;
	if (ac > 1)
		return (ft_printf("No arguments required to launch the shell.\n"), 1);
	while (1)
	{
		lst = create_list();
		g_commands = readline("minishell> ");
		if (!ft_strncmp(g_commands, "STOP", ft_strlen(g_commands)))
		{
			free(g_commands);
			exit (0);
		}
		lexer(&lst, g_commands);
		display_list(&lst);
		free_list(&lst);
		free(g_commands);
	}
	return (0);
}
