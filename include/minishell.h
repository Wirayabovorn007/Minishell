#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <signal.h>
# include <sys/wait.h>
# include <sys/types.h>

# include <readline/readline.h>
# include <readline/history.h>

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
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_shell
{
	char	**envp;
	int		last_exit_status;
}	t_shell;

// parser
t_token	*tokenize(char *input);
t_token	*new_token(char *value, t_token_type type);
void	add_token(t_token **list, t_token *new);
void	free_tokens(t_token *tokens);

t_cmd	*parse(t_token *tokens);
t_cmd	*new_cmd(void);
void	add_cmd(t_cmd **list, t_cmd *new);
void	free_cmds(t_cmd *cmds);

// builtin
int		is_builtin(char *cmd);
int		exec_builtin(t_cmd *cmd, t_shell *shell);

// execute
void	execute(t_cmd *cmds, t_shell *shell);

// signal
void	init_signals(void);

// utils
void	free_split(char **arr);
void	free_tokens(t_token *tokens);
void	free_cmds(t_cmd *cmds);
int		arr_len(char **arr);
char	**arr_add(char **arr, char *new_str);
int		ft_strlen(char *s);
char	*ft_strdup(char *s);
int		ft_strcmp(char *s1, char *s2);
int		is_space(char c);
int		is_operator(char c);
char	**ft_split(char *s, char c);

#endif