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
	int					sign;
	int					i;

	num = 0;
	sign = 1;
	i = 0;
	while (str[i] == ' ' || (str[i] >= '\t' && str[i] <= '\r'))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] && is_digit(str[i]))
	{
		if (num > LLONG_MAX / 10)
			return (1);
		if (num == LLONG_MAX / 10)
		{
			if (sign == 1 && (str[i] - '0') > 7)
				return (1);
			if (sign == -1 && (str[i] - '0') > 8)
				return (1);
		}
		num = num * 10 + (str[i] - '0');
		i++;
	}
	return (0);
}

static long long	ft_atoll_exit(char *str)
{
	long long	result;
	int			sign;
	int			i;

	result = 0;
	sign = 1;
	i = 0;
	while (str[i] == ' ' || (str[i] >= '\t' && str[i] <= '\r'))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i])
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (result * sign);
}

int	builtin_exit(char **argv, t_shell *shell, int is_single_cmd)
{
	long long	exit_code;

	if (is_single_cmd)
		write(2, "exit\n", 5);
	if (!argv[1])
		exit(shell->last_exit_status);
	if (!is_numeric(argv[1]) || check_overflow(argv[1]))
	{
		write(2, "minishell: exit: ", 17);
		write(2, argv[1], ft_strlen(argv[1]));
		write(2, ": numeric argument required\n", 28);
		shell->last_exit_status = 2;
		exit(2);
	}
	if (argv[2])
	{
		write(2, "minishell: exit: too many arguments\n", 36);
		shell->last_exit_status = 1;
		return (1);
	}
	exit_code = ft_atoll_exit(argv[1]);
	shell->last_exit_status = (unsigned char)exit_code;
	exit((unsigned char)exit_code);
}
