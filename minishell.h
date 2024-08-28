/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsharma <vsharma@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 12:06:51 by vsharma           #+#    #+#             */
/*   Updated: 2024/08/28 15:06:19 by vsharma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/ioctl.h>
# include <sys/wait.h>
# include <unistd.h>

# define SUCCESS 0
# define FAILURE -1
# define OPERATORS "|<>"
# define QUOTES "\"\'"

// STANDARD ERROR MESSAGES FROM BASH
# define FORK_ERR "minishell: fork() failed"
# define PIPE_ERR "minishell: pipe() failed"

// ft_cd
# define PATH_MAX 4096

# define CNTL_C 1
# define CNTL_D 2
# define CNTL_BACKSLASH 3

extern volatile sig_atomic_t	g_signal;

// enum list for token type
typedef enum e_operator
{
	NONE,
	RD_OUT,
	RD_APND,
	RD_IN,
	RD_HD,
	PIPE,
}								t_op;

// enum for shell mode required to handel signals
typedef enum e_mode
{
	INTERACTIVE,
	NON_INTERACTIVE,
	CHILD_PROCESS,
	HEREDOCS,
}								t_mode;

typedef struct s_heredoc
{
	char						*input;
	struct s_heredoc			*next;
}								t_heredoc;

// linked list to store the tokens created after parsing
typedef struct s_cmd
{
	int							argc;
	char						**argv;
	t_op						operator;
	struct s_cmd				*next;
}								t_cmd;

// linked list to store data of env varaibles
typedef struct s_elst
{
	char						*name;
	char						*value;
	bool						exported;
	struct s_elst				*next;
}								t_elst;

// structure to hold all required environment variable and token data
typedef struct s_data
{
	char						**env;
	t_elst						*env_lst;
	t_cmd						*head;
	int							exit_code;
	t_mode						mode;
}								t_data;

// builtins
/*builtin.c*/
int								builtin(t_cmd *cmd, t_data *data);
bool							is_valid_variable(char *str);

/*echo.c*/
int								echo(t_cmd *cmd);

/*env.c*/
int								env(t_data *data);

/*exit.c*/
void							exit_shell(t_cmd *cmd, t_data *data,
									int status_code);

/*ft_cd.c*/
int								cd(t_cmd *cmd, t_data *data, char *target_dir);

/*ft_export.c*/
int								export(t_cmd *cmd, t_data *data);

/*pwd.c*/
int								pwd(t_cmd *cmd);

/*unset.c*/
int								unset(t_cmd *cmd, t_elst **head);
int								unset_variable(char *name, t_elst **head);

// execution
/*system_commands.c*/
void							system_commands(t_cmd *cmd, t_data *data);

/*execute_handler.c*/
void							start_execution(t_cmd *cmd_list, t_data *data);
void							run_command(t_cmd *node, t_data *data);

/*pipe_execution.c*/
void							pipe_execution(t_cmd *node, t_data *data);

/*utils_linked_lists.c*/
// size_t							size_of_list(t_cmd *list);

// redirections
/*redirections.c*/
void 							handle_redirections(t_cmd *cmd, t_data *data);

/*redirections1.c*/
void							r_hd(t_data *data, t_cmd *node);


// validation
/*cleaup*/
void	free_parsed_tokens(t_cmd **cmd_list, t_data *data);
void	ft_clear_all(t_data *data);
/*input_handeling*/
bool	input_validation(char *input, t_data *data);
bool							check_operator(char *input);
/*validation_syntax*/
bool							mismatched_quotes(const char *str);
bool							invalid_sequence(char *str);
bool							invalid_operator(char *input);
bool							invalid_syntax(char *str);


// Parser
/*env_list*/
t_elst							*init_env_lst(char **env);
char							**split_env_var(char *env);
/*expander*/
char							*init_expander(char *str, t_data *data);
int								get_variable(char *str, char *input, int *i,
									t_data *data);
/*parser*/
t_cmd							*init_parser(char *input);
/*expander_utils*/
void							init_varaible(int *i, int *j, bool *quotes,
									bool *d_quotes);
int								get_exit_status(t_data *data, char *str,
									int *i);
int								input_size(char *str, t_data *data);
/*tokenizer*/
char							**allocate_token(char *str);
void							fill_tokens(char **token, char *str);
void							allocate_tokens_memory(char **token, char *str);
/*handel_quotes*/
char							*handel_quotes(char *str);


// Signals
void							handel_signals(t_data *data);

// utils
/*var_utils*/
int								store_env_var(char *cmd, t_elst **head,
									bool export);
char							*ft_lltoa(long long n);
long long						ft_atol(const char *str);
t_cmd							*newnode_par(int argc);
char							*get_fromvlst(char *var_name, t_elst **head);
char							*get_varvalue_fromvlst(char *var_name,
									t_data *data);
t_elst							*lstlast_env(t_elst *node);
void							lstadd_back_env(t_elst **head, t_elst *new);
bool							char_in_str(const char *str, int ch);
bool							str_equals(char *str1, char *str2);
bool							is_var_exported(char *name, t_elst **head);
t_elst							*newnode_env(char *var_name, char *var_value,
									bool is_exported);
char							*strip_whitespace(char *str);

// libft utils
void							ft_putchar_fd(char c, int fd);
void							ft_putendl_fd(char *str, int fd);
size_t							ft_strlen(const char *s);
char							**ft_split(char const *s, char c);
char							*ft_strchr(const char *s, int c);
char							*ft_strdup(const char *s1);
size_t							ft_strlen(const char *s);
char							*ft_substr(char const *s, unsigned int start,
									size_t len);
void							ft_putstr_fd(char *s, int fd);
char							*ft_strjoin(char const *s1, char const *s2);
bool							ft_isspace(char c);
int								ft_isalnum(int c);
int								ft_isdigit(int c);
char							*ft_strncpy(char *dest, const char *src,
									size_t n);

// signals
void							handle_signals(t_data *data);

#endif
