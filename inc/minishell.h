/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmirlico <bmirlico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 14:24:06 by bmirlico          #+#    #+#             */
/*   Updated: 2023/07/03 15:32:26 by bmirlico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/inc/libft.h"
# include "../libft/inc/get_next_line_bonus.h"
# include "../libft/inc/ft_printf.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <limits.h>
# include <errno.h>

# define DELIMITER " "
# define SPECIAL_CHAR "#&~*`();\\"
# define SINGLE_OPEN 1
# define DOUBLE_OPEN 2
# define CLOSED 3

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
	T_SINGLEQ,
	T_DOUBLEQ,
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

// main.c @Bastien

void			minishell(char *input);

void			display_parser(t_command **lst);

void			display_lexer(t_token **lst);

void			display_lexers(t_token **lst, t_token **lst_j);

/* 0-bis) PRE-PARSING i.e gestion d'erreurs et caracteres speciaux */

// syntax_error_1.c @Clement

int				check_syntax(char *input);

int				check_pipe_error(char *input);

int				check_empty_and_double_pipe(char *input);

int				check_redirections(char *input);

int				check_empty_redirection(char *input);

// syntax_error_2.c @Clement

int				check_special_char(char *input);

int				check_bad_env_variable(char *input);

int				check_last_exitcode_case(char *input, int index);

int				check_rdir(int rdir);

// utils.c @Bastien @Clement

int				is_special_char(char c);

int				quotes_state(char c, int prev_state);

int				is_delimiter(char c, char *delimiter);

void			ft_strncpy(char *value, char *input, int len);

/* 1) LEXER i.e tokenisation de l'input */

// lexer_1.c @Bastien

void			lexer_str(t_token **lst, t_token **lst_j);

void			group_quotes(t_token **tmp, t_token **lst_j, char *join);

void			group_str(t_token **tmp, t_token **lst_j, char *join);

void			group_redirs(t_token **tmp, t_token **lst_j, char *join);

void			add_char_to_str(t_token **tmp, t_token **lst_j, char *join);

// lexer_2.c @Bastien

void			tokenize_remaining(t_token **lst_j);

void			ft_join_free(char **join, char c);

char			*char_to_str(char c);

void			lexer_char(t_token **lst, char *input);

char			get_token_value(char *input);

// lexer_3.c @Bastien

t_token_type	get_token_type(char c);

// lexer_list.c @Bastien

t_token			*create_list_lexer(void);

t_token			*create_token(t_token_type type, char c, char *str);

void			push_to_list(t_token **lst, t_token *new);

void			free_lexer_char(t_token **lst);

void			free_lexer_str(t_token **lst);

/* 2) PARSING i.e traitement syntaxique de l'input */

// parser_1.c @Bastien

void			parser(t_token **lst_j, t_command **cmds);

void			add_redirs(t_token **tmp, t_token **redirs);

void			add_command_to_tab(t_token **tmp, char ***tab);

void			add_command_to_list(t_token **tmp, t_token **redirs,
					char ***tab, t_command **cmds);

void			fill_tab_free(char ***tab, char *str);

// parser_2.c @Bastien

void			fill_in_tmp(char **dest, char **src, int len);

void			free_previous_str(char **tab, int i);

int				get_len_tab(char **tab);

void			free_tab(char **tab);

// parser_list.c @Bastien

t_command		*create_list_parser(void);

t_command		*create_command(char **tab, t_token *redirs);

void			push_to_parser(t_command **lst, t_command *new);

void			free_parser(t_command **cmds);

void			free_lists(t_token **lst, t_token **lst_j, t_command **cmds);

/* 3) EXPAND i.e traitement des variables d'env */

// var_env_state.c @Clement

int				var_env_state(char *str, int i, int var_env_state, int q_state);

int				var_env_declaration(char *str, int i, int quote_state);

int				end_var_env_declaration(char *str, int i);

int				is_closing_scope(char *str, int index);

// expand_substitution.c @Clement

int				to_be_modified(char *str);

int				nb_quotes(char *str);

void			new_str(char *str, char *new);

int				var_env_copy(char *str, int index, char *new, int dest);

// get_expand_info @Clement

int				get_varname_len(char *str);

int				get_varenv_value_len(char *str);

int				get_varenv_len(char *str, int i);

int				get_var_env_end(char *str, int i);

int				get_nb_empty(char **tab);

// clean_post_expand.c @Clement

void			clean_lst(t_command *cmds);

char			**replace_tab(char **tab, int new_len);

// expand.c @Clement

void			expand(t_command **cmds);

void			expand_tab(char **tab);

void			expand_str_tab(char **tab, int i);

void			expand_rdir(t_token	*redirections);

void			expand_rdir_lst(t_token *rdir);

// remove_quote.c @Clement

void			remove_quotes_rdir(t_token	*redirections);

void			quote_removing_rdir(t_token *rdir, int quotes);

void			remove_quotes_tab(char **tab);

void			quote_removing_tab(char **tab, int index, int quotes);

/* 4) EXECUTION i.e execution des commandes et des builtins */
// echo, cd, pwd, export, unset, env, exit

// exec_1.c @Bastien

void			execution(t_command **cmds);

int				is_builtin(char *cmd);

void			exec_builtin(t_command *tmp);

void			built_in_cd(t_command *tmp);

void			built_in_pwd(void);

// exec_2.c @Bastien

void			built_in_exit(t_command *tmp);

void			conditions_exit(t_command *tmp, long long exit_code,
					char *error_str, int len_tab);

int				is_numeric(char *str);

void			exit_non_numeric(char **error, char *str);

int				is_out_of_range(long long exit_code, char *str);

// exec_3.c @Bastien

long long		ft_strtoll(const char *nptr);

void			init_strtoll(int *i, int *sign, long long *res, int *digit);

void			check_sign(char c, int *i, int *sign);

void			handle_bounds(int *sign, long long *res);

#endif
