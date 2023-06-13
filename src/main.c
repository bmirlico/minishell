/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmirlico <bmirlico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 14:25:42 by bmirlico          #+#    #+#             */
/*   Updated: 2023/06/12 15:14:41 by bmirlico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	display_lexer(t_token **lst)
{
	t_token	*tmp;

	tmp = *lst;
	while (tmp != NULL)
	{
		ft_printf("Type: %d ; Value: %c ; Str: %s\n", tmp->type,
			tmp->value, tmp->str);
		tmp = tmp->next;
	}
}

void	display_lexers(t_token **lst, t_token **lst_j)
{
	display_lexer(lst);
	ft_printf("\n----------\n\n");
	display_lexer(lst_j);
}

void	display_parser(t_command **cmds)
{
	int			i;
	int			j;
	t_command	*tmp;

	j = 0;
	tmp = *cmds;
	while (tmp != NULL)
	{
		printf("\n---NODE no: %d----\n", j);
		i = 0;
		if (tmp->cmd_args != NULL)
		{
			while (tmp->cmd_args[i] != NULL)
			{
				ft_printf("CMD_ARGS: %s\n", tmp->cmd_args[i]);
				i++;
			}
		}
		while (tmp->redirections != NULL)
		{
			ft_printf("REDIRS: %s type: %d\n", tmp->redirections->str, tmp->redirections->type);
			tmp->redirections = tmp->redirections->next;
		}
		j++;
		tmp = tmp->next;
	}
}

void	minishell(char *input, t_token **lst, t_token **lst_j, t_command **cmds)
{
	if (check_syntax(input) == 0)
	{
		if (!ft_strncmp(input, "stop", ft_strlen(input) + 1))
		{
			free(input);
			exit (0);
		}
		lexer_char(lst, input);
		lexer_str(lst, lst_j);
		//display_lexer(lst_j);
		parser(lst_j, cmds);
		display_parser(cmds);
		free_lists(lst, lst_j, cmds);
	}
	free(input);
}

// main du projet minishell
int	main(int ac, char **av)
{
	char		*input;
	t_token		*lst;
	t_token		*lst_j;
	t_command	*cmds;

	(void)av;
	if (ac > 1)
		return (ft_printf("No arguments required to launch the shell.\n"), 1);
	while (1)
	{
		lst = create_list_lexer();
		lst_j = create_list_lexer();
		cmds = create_list_parser();
		input = readline("minishell> ");
		minishell(input, &lst, &lst_j, &cmds);
	}
	return (0);
}

// int	main(void)
// {
// 	char	**tab;
// 	char	**tmp;
// 	int		i;

// 	i = 0;
// 	tab = ft_split("hello g t p ok", ' ');
// 	while (tab[i] != NULL)
// 		printf("%s\n", tab[i++]);
// 	i = 0;
// 	tmp = tab;
// 	while (tmp[i] != NULL)
// 		printf("%s\n", tmp[i++]);
// 	return (0);
// }
