#include "minishell.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	if (n == 0)
		return (0);
	while (n > 0 && *s1 != '\0' && *s1 == *s2)
	{
		s1++;
		s2++;
		n--;
	}
	if (n == 0)
		return (0);
	return ((unsigned char)*s1 - (unsigned char)*s2);
}

void	ft_putstr_fd(char *str, int fd)
{
	if (!str || fd < 0)
		return ;
	write(fd, str, ft_strlen(str));
}

int	check_unsupported_meta_char(t_token *tok)
{
	if (tok->type == WORD && tok->quote == NO_QUOTE)
	{
		if (ft_strchr(tok->value, '('))
		{
			ft_putstr_fd("minishell: syntax error near unexpected token `('\n", 2);
			return (0);
		}
		if (ft_strchr(tok->value, ')'))
		{
			ft_putstr_fd("minishell: syntax error near unexpected token `)'\n", 2);
			return (0);
		}
		if (ft_strchr(tok->value, ';'))
		{
			ft_putstr_fd("minishell: syntax error near unexpected token `;'\n", 2);
			return (0);
		}
		if (ft_strchr(tok->value, '&'))
		{
			ft_putstr_fd("minishell: syntax error near unexpected token `&'\n", 2);
			return (0);
		}
	}
	return (1);
}
