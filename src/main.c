/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmirlico <bmirlico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 14:25:42 by bmirlico          #+#    #+#             */
/*   Updated: 2023/06/02 14:36:09 by bmirlico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	display_list(t_token **lst)
{
	t_token	*tmp;

	tmp = *lst;
	while (tmp != NULL)
	{
		ft_printf("Type: %d ; Value: %c\n", tmp->type,
			tmp->value);
		tmp = tmp->next;
	}
}

// main du projet minishell
int	main(int ac, char **av)
{
	char	*input;
	t_token	*lst;

	(void)av;
	if (ac > 1)
		return (ft_printf("No arguments required to launch the shell.\n"), 1);
	while (1)
	{
		lst = create_list();
		input = readline("minishell> ");
		if (check_syntax(input) == 0)
		{
			if (!ft_strncmp(input, "stop", ft_strlen(input)))
			{
				free(input);
				exit (0);
			}
			lexer_char(&lst, input);
			display_list(&lst);
			free_list(&lst);
		}
		free(input);
	}
	return (0);
}
