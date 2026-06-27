#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <signal.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <string.h>
# include <errno.h>
# include <limits.h>

# include <readline/readline.h>
# include <readline/history.h>

# define NO_QUOTE 0
# define SINGLE_QUOTE 1
# define DOUBLE_QUOTE 2

extern int	g_signal;

typedef enum e_token_type
{
	WORD,
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	APPEND,
	HEREDOC
}	t_token_type;

typedef struct s_token
{
	char			*value;
	t_token_type	type;
	int				quote;
	struct s_token	*next;
}	t_token;

typedef struct s_cmd
{
	char			**argv;
	char			*infile;
	char			*outfile;
	int				append;
	int				heredoc;
	char			*delimiter;
	int				heredoc_quoted;
	int				ambiguous_redir;
	char			*ambig_target;
	int				redir_error;
	int				redir_errno;
	char			*redir_error_file;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_shell
{
	char	**envp;
	int		last_exit_status;
}	t_shell;

// parser
t_token	*tokenize(char *input);
t_token	*new_token(char *value, t_token_type type, int quote);
void	add_token(t_token **list, t_token *new);
void	free_tokens(t_token *tokens);
void	process_token(t_cmd **cur, t_cmd **cmd, t_token **t, t_shell *sh);
char	*get_word(char *s, int *i, int *quote);
void	skip_word(char *str, int *i);
int		syntax_check(t_token *tokens);
int		is_quote(char c);
char	*remove_quotes(char *s);
int		has_unclosed_quote(char *s);
char	*get_env_value(char *str, t_shell *shell, int *i);
char	*expand_env(char *str, t_shell *shell);
int		env_len(char **env);
void	split_and_add_args(t_cmd *cmd, char *str);
void	handle_redir(t_cmd *cmd, t_token **tok, t_shell *shell);
t_cmd	*parse(t_token *tokens, t_shell *shell);
t_cmd	*new_cmd(void);
void	add_cmd(t_cmd **list, t_cmd *new);
void	free_cmds(t_cmd *cmds);
void	free_envp(char **envp);

// builtin
int		is_builtin(char *cmd);
int		exec_builtin(t_cmd *cmd, t_shell *shell, int is_single_cmd);
int		builtin_echo(char **argv);
int		builtin_pwd(void);
int		builtin_env(t_shell *shell);
int		builtin_cd(char **argv, t_shell *shell);
int		builtin_exit(char **argv, t_shell *shell, int is_single_cmd);
int		builtin_export(char **argv, char ***env);
int		builtin_unset(char **argv, t_shell *shell);
int		add_or_update_env(t_shell *shell, char *key, char *value);
char	*get_env_val(char **envp, char *key);
int		init_env(t_shell *shell, char **sys_envp);
int		is_valid_identifier(char *str);
int		find_env(char **env, char *key);
void	print_export(char **env);
void	sort_env(char **env);
char	**copy_env(char **env);
void	print_export_error(char *arg);
int		has_equal_sign(char *arg);

// execute
void	execute(t_cmd *cmds, t_shell *shell);
int		setup_redirection(t_cmd *cmd);
int		handle_heredoc(char *delimiter);
char	*get_cmd_path(char *cmd, char **envp);
void	execute_pipe(t_cmd *cmds, t_shell *shell);
void	print_err(t_cmd *cmd);

// signal
void	init_signals(void);

// utils
void	free_split(char **arr);
void	free_tokens(t_token *tokens);
void	free_cmds(t_cmd *cmds);
char	*join_and_free(char *s1, char *s2);
int		arr_len(char **arr);
char	**arr_add(char **arr, char *new_str);
void	free_arr(char **arr);
void	swap(char **a, char **b);
int		ft_strlen(char *s);
char	*ft_strdup(char *s);
int		ft_strcmp(char *s1, char *s2);
char	*ft_substr(char *s, int start, int len);
char	*ft_strjoin(char *s1, char *s2);
int		is_space(char c);
int		is_operator(char c);
int		is_alpha(char c);
int		is_digit(char c);
int		is_alnum(char c);
char	**ft_split(char *s, char c);
char	*word_dup(char *s, int start, int end);
char	*ft_itoa(int nbr);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		is_single_builtin(t_cmd *cmds);
char	*ft_strchr(char *str, char c);
void	ft_putstr_fd(char *str, int fd);
void	check_fd_error(t_cmd *cmd, int fd, char *val);
void	apply_file_redir(t_cmd *cmd, char *val, int type);
int		check_ambiguous(t_cmd *cmd, t_token *tok, t_token *next, char *val);
void	set_redir_target(t_cmd *cmd, t_token *tok, t_token *next, char *val);

#endif