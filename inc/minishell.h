/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmirlico <bmirlico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 14:24:06 by bmirlico          #+#    #+#             */
/*   Updated: 2023/06/12 14:47:46 by bmirlico         ###   ########.fr       */
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
	T_SPACE, // 0
	T_CMD, // 1
	T_PIPE, // 2
	T_LR, // 3
	T_RR, // 4
	T_HEREDOC, // 5
	T_APPEND, // 6
	T_INFILE, // 7
	T_LIMITOR, // 8
	T_OUTFILE, // 9
	T_OUTFILE_APPEND, // 10
	T_EOF, // 11
}	t_token_type;

typedef struct s_token {
	t_token_type	type;
	char			value;
	char			*str;
	struct s_token	*next;
}	t_token;

typedef struct s_command {
	char					**cmd_args;
	t_token					*redirections;
	struct s_command		*next;
}	t_command;

/* 0) MAIN */

// main.c

void			display_list(t_token **lst);

void			display_lists(t_token **lst, t_token **lst_j);

void			minishell(char *input, t_token **lst, t_token **lst_j,
					t_command **cmds);

/* 0-bis) PRE-PARSING i.e gestion d'erreurs et caracteres speciaux */

// syntax_error.c

int				check_syntax(char *input);

int				check_unclosed_quotes(char *input);

int				check_special_chars(char *input);

int				check_pipe_and_redir(char *input);

int				get_num_quotes(char *input, int c);

int				find_chars(char *input);

/* 1) LEXER i.e tokenisation de l'input */

// lexer.c

void			lexer_str(t_token **lst, t_token **lst_j);

void			lexer_char(t_token **lst, char *input);

void			ft_join_free(char **join, char c);

char			*char_to_str(char c);

void			tokenize_remaining(t_token **lst_j);

char			get_token_value(char *input);

t_token_type	get_token_type(char c);

int				is_delimiter(char c, char *delimiter);

void			ft_strncpy(char *value, char *input, int len);

// lexer_list.c

t_token			*create_list_lexer(void);

t_token			*create_token(t_token_type type, char c, char *str);

void			push_to_list(t_token **lst, t_token *new);

void			free_lexer_char(t_token **lst);

void			free_lexer_str(t_token **lst);

/* 2) PARSING i.e traitement syntaxique de l'input */

// parser.c

void			parser(t_token **lst_j, t_command **cmds);

void			fill_tab_free(char ***tab, char *str);

int				get_len_tab(char **tab);

void			free_tab(char **tab);

// parser_list.c

t_command		*create_list_parser(void);

t_command		*create_command(char **tab, t_token *redirs);

void			push_to_parser(t_command **lst, t_command *new);

void			free_parser(t_command **cmds);

void			free_lists(t_token **lst, t_token **lst_j, t_command **cmds);

#endif
