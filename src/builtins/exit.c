#include "minishell.h"

static int	is_numeric(char *str)
{
	int	i;

	i = 0;
	if (!str || !str[0])
		return (0);
	while (str[i] == ' ' || (str[i] >= '\t' && str[i] <= '\r'))
		i++;
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (!str[i])
		return (0);
	while (str[i] && is_digit(str[i]))
		i++;
	while (str[i] == ' ' || (str[i] >= '\t' && str[i] <= '\r'))
		i++;
	return (str[i] == '\0');
}

static int	check_overflow(char *str)
{
	unsigned long long	num;
	unsigned long long	limit;
	int					sign;

	num = 0;
	sign = 1;
	while (*str == ' ' || (*str >= '\t' && *str <= '\r'))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	limit = 9223372036854775807ULL + (sign == -1);
	while (is_digit(*str))
	{
		if (num > limit / 10
			|| (num == limit / 10
				&& (unsigned long long)(*str - '0') > limit % 10))
			return (1);
		num = num * 10 + (*str++ - '0');
	}
	return (0);
}

static long long	ft_atoll_exit(char *str)
{
	unsigned long long	result;
	int					sign;

	result = 0;
	sign = 1;
	while (*str == ' ' || (*str >= '\t' && *str <= '\r'))
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (is_digit(*str))
	{
		result = result * 10 + (*str - '0');
		str++;
	}
	if (sign == -1)
	{
		if (result == 9223372036854775808ULL)
			return (LLONG_MIN);
		return (-((long long)result));
	}
	return ((long long)result);
}

int	builtin_exit(char **argv, t_shell *shell, int is_single_cmd)
{
	long long	exit_code;

	if (is_single_cmd)
		write(2, "exit\n", 5);
	if (!argv[1])
		free_and_exit(shell, shell->last_exit_status);
	if (!is_numeric(argv[1]) || check_overflow(argv[1]))
	{
		write(2, "minishell: exit: ", 17);
		write(2, argv[1], ft_strlen(argv[1]));
		write(2, ": numeric argument required\n", 28);
		free_and_exit(shell, 2);
	}
	if (argv[2])
	{
		write(2, "minishell: exit: too many arguments\n", 36);
		shell->last_exit_status = 1;
		return (1);
	}
	exit_code = ft_atoll_exit(argv[1]);
	shell->last_exit_status = (unsigned char)exit_code;
	free_and_exit(shell, (unsigned char)exit_code);
	return (0);
}
