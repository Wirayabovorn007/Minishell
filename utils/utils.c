#include "minishell.h"

int	is_space(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

int	is_operator(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

int	is_alpha(char c)
{
	return ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'));
}

int	is_digit(char c)
{
	return (c >= '0' && c <= '9');
}

int	is_alnum(char c)
{
	return (is_alpha(c) || is_digit(c));
}
