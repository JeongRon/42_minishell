/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongrol <jeongrol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 13:32:57 by jeongrol          #+#    #+#             */
/*   Updated: 2023/09/19 16:37:32 by jeongrol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_num(char *str)
{
	int	i;

	i = 0;
	if (str[0] == '+' || str[0] == '-')
		i++;
	while (str[i])
	{
		if (!('0' <= str[i] && str[i] <= '9'))
			return (0);
		i++;
	}
	return (1);
}

int	check_home(char *envp)
{
	if (envp[0] == 'H' && envp[1] == 'O'
		&& envp[2] == 'M' && envp[3] == 'E'
		&& envp[4] == '=')
		return (SUCCESS);
	return (FAIL);
}

int	check_path(char *envp)
{
	if (envp[0] == 'P' && envp[1] == 'A'
		&& envp[2] == 'T' && envp[3] == 'H'
		&& envp[4] == '=' && ft_strlen(envp) != 5)
		return (SUCCESS);
	return (FAIL);
}

int	check_duplicate(char **arr, char *cmd, int flag)
{
	char	*cmd_key;
	char	*arr_key;
	int		dup_flag;
	int		i;

	cmd_key = key_strdup(cmd);
	dup_flag = 0;
	i = -1;
	while (arr[++i])
	{
		if (flag == 0)
			arr_key = key_strdup(&arr[i][11]);
		else
			arr_key = key_strdup(arr[i]);
		if (ftj_strcmp(cmd_key, arr_key) == 0)
		{
			dup_flag = 1;
			free(arr_key);
			break ;
		}
		free(arr_key);
	}
	free(cmd_key);
	return (dup_flag);
}
