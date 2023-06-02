/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmirlico <bmirlico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 14:24:06 by bmirlico          #+#    #+#             */
/*   Updated: 2023/06/02 14:36:17 by bmirlico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/inc/libft.h"
# include "../libft/inc/get_next_line_bonus.h"
# include "../libft/inc/ft_printf.h"
# include <readline/readline.h>
# include <readline/history.h>

# define DELIMITER " "
# define SPECIAL_CHARS ";\\"

typedef enum s_token_type {
	T_SPACE,
	T_CMD,
	T_PIPE,
	T_LR,
	T_RR,
	T_HEREDOC,
	T_APPEND,
	T_INFILE,
	T_LIMITOR,
	T_OUTFILE,
	T_OUTFILE_APPEND,
	T_EOF,
}	t_token_type;

typedef struct s_token {
	t_token_type	type;
	char			value;
	char			*str;
	struct s_token	*next;
}	t_token;

typedef struct s_command {
	char					**cmd_args;
	int						fdin;
	int						fdout;
	struct s_simple_command	*next;
}	t_command;

/* 0) MAIN */

// main.c

void			display_list(t_token **lst);

/* 1) LEXER i.e tokenisation de l'input */

// lexer.c

void			lexer_char(t_token **lst, char *input);

char			get_token_value(char *input);

t_token_type	get_token_type(char c);

int				is_delimiter(char c, char *delimiter);

void			ft_strncpy(char *value, char *input, int len);

// lexer_list.c

t_token			*create_list(void);

t_token			*create_token(t_token_type type, char c, char *str);

void			push_to_list(t_token **lst, t_token *new);

void			free_list(t_token **lst);

// syntax_error.c

int				check_syntax(char *input);

int				check_unclosed_quotes(char *input);

int				check_special_chars(char *input);

int				check_pipe_and_redir(char *input);

int				get_num_quotes(char *input, int c);

int				find_chars(char *input);

/* 2) PARSING i.e traitement syntaxique de l'input */



#endif
