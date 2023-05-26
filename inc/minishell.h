/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmirlico <bmirlico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 14:24:06 by bmirlico          #+#    #+#             */
/*   Updated: 2023/05/26 16:31:30 by bmirlico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/inc/libft.h"
# include "../libft/inc/get_next_line_bonus.h"
# include "../libft/inc/ft_printf.h"

# define DELIMITER " "

typedef enum s_token_type {
	T_WORD,
	T_ARG,
	T_PIPE,
	T_LR,
	T_RR,
	T_HEREDOC,
	T_APPEND,
	T_NL,
	T_EOF,
}	t_token_type;

typedef struct s_token {
	t_token_type	type;
	char			*value;
	struct s_token	*next;
}	t_token;

/* 1) LEXER i.e tokenisation de l'input */

t_token			*create_list_token(void);

t_token			*create_token(t_token_type type, char *value);

t_token_type	get_token(char *input);

t_token			**lexer(char *input);

/* 2) PARSING i.e traitement syntaxique de l'input */

#endif
