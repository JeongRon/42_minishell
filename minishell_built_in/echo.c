/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongmiki <dongmiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 18:02:40 by jeongrol          #+#    #+#             */
/*   Updated: 2023/09/18 16:56:27 by dongmiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_echo(char **cmd, int opt, int index)
{
	int	last_index;

	last_index = ft_two_strlen(cmd) - 1;
	while (cmd[index])
	{
		printf("%s", cmd[index]);
		if (last_index != index)
			printf(" ");
		index++;
	}
	if (opt == 0)
		printf("\n");
}

static int	search_option(char *cmd)
{
	int	i;
	int	return_flag;

	i = 1;
	return_flag = 0;
	if (ft_strlen(cmd) < 2)
		return (return_flag);
	if (cmd[0] == '-' && cmd[1] == 'n')
	{
		return_flag = 1;
		while (cmd[++i])
		{
			if (cmd[i] == 'n')
				continue ;
			else
			{
				return_flag = 0;
				break ;
			}
		}
		return (return_flag);
	}
	return (return_flag);
}

static void	search_echo_flag(char **cmd, int *opt, int *start)
{
	int	i;

	i = 0;
	while (cmd[++i])
	{
		if (*start == 0)
		{
			if (search_option(cmd[i]) == 0)
				*start = i;
			else
				*opt += 1;
		}
		else
			return ;
	}
}

int	start_echo(char **cmd)
{
	int		option_flag;
	int		start_flag;
	int		status;

	option_flag = 0;
	start_flag = 0;
	status = 0;
	search_echo_flag(cmd, &option_flag, &start_flag);
	if (start_flag == 0)
	{
		if (option_flag == 0)
			printf("\n");
	}
	else
		print_echo(cmd, option_flag, start_flag);
	return (status);
}
