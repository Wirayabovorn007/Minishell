#include "minishell.h"

int	arr_len(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return (0);
	while (arr[i])
		i++;
	return (i);
}

char	**arr_add(char **arr, char *new_str)
{
	char	**new_arr;
	int		i;

	new_arr = malloc(sizeof(char *) * (arr_len(arr) + 2));
	if (!new_arr)
		return (NULL);
	i = 0;
	while (arr && arr[i])
	{
		new_arr[i] = arr[i];
		i++;
	}
	new_arr[i] = ft_strdup(new_str);
	new_arr[i + 1] = NULL;
	free(arr);
	return (new_arr);
}
