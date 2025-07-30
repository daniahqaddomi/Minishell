/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhasoneh <mhasoneh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 17:23:08 by mhasoneh          #+#    #+#             */
/*   Updated: 2025/05/26 17:23:08 by mhasoneh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <limits.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft/libft.h"

// ==============================
// ENUMS
// ==============================

typedef enum e_token_type
{
	WORD,
	COMMAND,
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	APPEND,
	HEREDOC,
	UNKNOWN
}	t_token_type;

// ==============================
// STRUCTS
// ==============================

typedef struct s_token
{
	char			*value;
	t_token_type	type;
	struct s_token	*next;
}	t_token;

typedef struct s_data
{
	char	**env;
	int		last_status;
}	t_data;

typedef struct s_split
{
    char *value;
    int type; //  WORD, COMMAND, PIPE, ...
    struct t_split *next;
} t_split;

typedef struct s_command
{
	char	**argv;
	int		builtin_fun; //flag 1 if its builtin
	pid_t	pid;
	t_token	*redirections; //linkedlist to store all input/output {"<","file.txt"}
	struct s_command	*next_cmd;
}	t_command;

// ==============================
// CORE SHELL
// ==============================

void	shell_loop(t_data *data);
char	*get_input(t_data *data);
char	**copy_env(char **envp);

// ==============================
// TOKENIZATION / PARSING
// ==============================

t_token	*split_line_to_words(char *line);
void	create_token(t_token **token, char *value, t_token_type type);
void	tokenize(t_token *tokens);
void	mark_commands(t_token *tokens);
int		is_syntax_error(t_token *tokens);
void	free_tokens(t_token *token);

// ==============================
// EXPANSION
// ==============================

void	expand(t_token *tokens, t_data *data);
char	*expand_token_value(char *input, t_data *data);
char	*handle_single_quote(char *input, int *i);
char	*handle_double_quote(char *input, int *i, t_data *data);
char	*handle_dollar(char *input, int *i, t_data *data);
char	*join_and_free(char *a, char *b);
int		is_quoted(char *str);
void	replace_token_with_multiple(t_token **head, t_token *cur, char **parts);

// ==============================
// BUILTIN EXECUTION
// ==============================

void	execute_builtin_tokens(t_token *tokens, t_data *data);
int	valid_identifier(char *str);
void	free_env(char **env);
void	handle_echo_command(t_token *token);
// void	handle_cd_command(char **argv, t_data *data);
// void	handle_pwd_command(void);
void	handle_export_command(char **argv, t_data *data);
void	handle_unset_command(char **argv, t_data *data);
void	handle_env_command(char **args, t_data *data);
void	handle_exit_command(char **argv, t_data *data);

// ==============================
// SIGNALS
// ==============================

void	set_signals_interactive(void);

//split_words
t_token *split_line_to_words(char *line);
void free_tokens(t_token *head);
#endif
