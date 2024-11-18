/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caubert <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 12:36:40 by caubert           #+#    #+#             */
/*   Updated: 2024/10/25 15:12:38 by caubert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"

# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <execinfo.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <signal.h>
# include <ctype.h>
# include <stdio.h>
# include <fcntl.h>
# include <errno.h>

# define PROMPT "minishell> "

extern volatile sig_atomic_t	g_exit_code;

typedef struct s_fd_info
{
	int					stdin_backup;
	int					stdout_backup;
	int					pipe_fd[2];
}	t_fd_info;

/* *key : key of the environment variable.
   *value : value of the environment variable.
   *next : pointer the the next environment variable. */
typedef struct s_env
{
	char				*key;
	char				*value;
	struct s_env		*next;
}	t_env;

/* t_ta stands for token array.
   **tokens : an array of strings containing each individual token.
   *token : temp buffer to construct each token individualy.
   quotechar : contains the type of quote, simple or double, encountered.
   tokenindex : keep the track of the current position within the token buf.
   count : counts the total number of token.
   inquotes : flag which indicates if we're inside quotes.
   tokensize : contains the length of a designed token.
   capacity : is the total number of tkens authorized to handle dynamically. */
typedef struct s_ta
{
	char				**tokens;
	char				*token;
	char				quotechar;
	size_t				tokenindex;
	size_t				tokensize;
	int					inquotes;
	int					count;
	int					capacity;
	int					trailing_space;
	int					*quoted;
	int					second_quote;
}	t_ta;

/* type : type of redirection, defined by 0 = <, 1 = >, 2 = << and 3 = >>.
   *file : it's the name of the file implicated in the redirection.
   *next : pointer to the next redirection. */
typedef struct s_redirect
{
	int					type;
	char				*file;
	struct s_redirect	*next;
}	t_redirect;

/* **args : array of the command's arguments.
   *name : name of the command.
   arg_count : number of arguments.
   *redirects : chained list of the redirections associated to the command.
   *next : pointer to the next command in case of pipes. */
typedef struct s_cmd
{
	int					arg_count;
	char				**args;
	char				*name;
	t_redirect			*redirects;
	struct s_cmd		*next;
	struct s_cmd		*prev;
	t_fd_info			*fd_info;
}	t_cmd;

/* *env : chained list of the environment variable. 
   *command :
   last_exit_status : output status of the last executed command. */
typedef struct s_shell_data
{
	t_cmd				*cmd;
	t_env				*env;
	int					last_exit_status;
}	t_shell_data;

/* minishell.c */
int				main(int ac, char **av, char **envp);

/* debug.c */
void			print_allocations(void);
void			untrack_allocation(void *ptr);
void			track_allocation(void *ptr, char *location, size_t size);

/* shell_management.c */
t_shell_data	*get_shell_data(void);
t_env			*copy_env_list(t_env *env);
void			set_env_value(t_env **env, const char *key, const char *value);

/* expand_vars.c */
char			*expand_variables(char *input, t_shell_data *shell_data);
size_t			calculate_expanded_size(char *input, t_shell_data *shel_data);

/* lexer.c */
t_ta			*lexer(char *input);
void			process_char(t_ta *ta, char **input);
void			process_input(t_ta *ta, char *input);
void			process_quotes(t_ta *ta, char **input);
void			handle_empty_quotes(t_ta *ta, char **input);
void			handle_quotes(t_ta *ta, char *input);
int				add_token(t_ta *ta, char *token);

/* struct_init.c */
t_ta			*tokenarray_init(void);
t_cmd			*cmd_init(void);
void			fd_info_init(t_cmd *cmd);

/* parse_tokens.c */
t_cmd			*parse_tokens(t_ta *ta);

/* parse_tokens_utils.c */

int				get_redirect_type(char *token);
void			add_redirect(t_cmd *cmd, int type, char *file);
void			add_argument(t_cmd *cmd, char *arg);

/* execute_commands.c */
void			execute_commands(t_cmd *cmd, t_shell_data *shell_data);
int				execute_builtin(t_cmd *cmd, t_shell_data *shell_data);
void			execute_single_command(t_cmd *cmd, t_shell_data *shell_data);
void			execute_piped_command(t_cmd *cmd, t_shell_data *sd, \
		int *old_pipe, int is_first);

/* execute_commands_utils.c */
char			*find_command_path(const char *cmd, t_env *env);
char			*join_path(const char *dir, const char *file);
int				is_builtin(char *cmd_name);
void			execute_external(t_cmd *cmd, t_shell_data *shell_data);

/* execute_single_commands_utils.c */
int				fork_and_execute(t_cmd *cmd, t_shell_data *shell_data);
void			handle_child_signals(int status);
void			execute_child_process(t_cmd *cmd, t_shell_data *shell_data);

/* builtins.c */
int				builtin_export(t_cmd *cmd, t_shell_data *shell_data);
int				builtin_exit(t_cmd *cmd, t_shell_data *shell_data);
void			builtin_env(t_shell_data *shell_data);
int				builtin_echo(t_cmd *cmd);
int				builtin_cd(t_cmd *cmd, t_shell_data *shell_data);

/* builtins_2.c */
void			builtin_unset(t_cmd *cmd, t_shell_data *shell_data);
void			builtin_pwd(void);

/* env_management.c */
char			**env_list_to_array(t_env *env);

/* env_management_utils.c */
void			remove_env_var(t_env **env, const char *key);
void			set_env_value(t_env **env, const char *key, const char *value);
void			*get_env_value(t_env *env, const char *key);

/* pipeline_manager.c */
void			execute_pipeline(t_cmd *cmd, t_shell_data *shell_data);
int				is_pipeline(t_cmd *cmd);
void			create_all_pipes(t_cmd *cmd_list);
void			fork_and_execute_command(t_cmd *cmd, int input_fd, \
		int *pipe_fds, t_shell_data *sd);

/* pipeline_utils.c */
void			cleanup_all_pipes(t_cmd *cmd);
void			cleanup_pipe(t_fd_info *fd_info);
int				create_pipe_for_cmd(t_cmd *cmd);
void			restore_fds(t_fd_info *fd_info);
void			backup_fds(t_fd_info *fd_info);

/* redirections_management.c */
int				apply_redirections(t_redirect *redirects);

/* signals_management.c */
void			init_signals(void);
void			setup_signals(void);

/* free's */
void			free_env_array(char **env_array);
void			free_tokenarray(t_ta *ta);
void			free_redirects(t_redirect *redirect);
void			free_command(t_cmd *cmd);
void			free_ptr(void *ptr);
void			ft_cleanup_shell(t_shell_data **shell);
void			ft_cleanup_env(t_env **env);

/* check/utils.c */
int				is_redirect(const char *token);
int				check_directory_path(char *input);
int				check_redir_pipe(char *input, int *i);
int				check_pipe_syntax(char *input);
int				is_redirect_char(char c);
int				check_syntax(char *input);
int				errmsg(char *errmsg, char *detail, int quotes);
char			*ft_join_errmsg(char *str, char *add);
char			*get_redirect_error(char **tokens, int count, int *i);

#endif
