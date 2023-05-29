/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmirlico <bmirlico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 14:25:42 by bmirlico          #+#    #+#             */
/*   Updated: 2023/05/29 17:33:01 by bmirlico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// main du projet minishell
int	main(int ac, char **av)
{
	(void)ac;
	t_token	*lst;
	t_token	*tmp;

	lst = create_list();
	// if (ac > 1)
	// 	return (ft_printf("Invalid input. No arguments required.\n"), 1);
	lexer(&lst, av[1]);
	tmp = lst;
	while (tmp != NULL)
	{
		printf("Type: %d ; Value: %s\n", tmp->type, tmp->value);
		tmp = tmp->next;
	}
	free_list(&lst);
	return (0);
}
