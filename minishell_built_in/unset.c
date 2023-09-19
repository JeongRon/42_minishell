/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongrol <jeongrol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 21:23:57 by dongmiki          #+#    #+#             */
/*   Updated: 2023/09/19 16:51:39 by jeongrol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	parsing_unset(char *cmd)
{
	int	i;

	i = -1;
	while (cmd[++i])
	{
		if (i == 0)
		{
			if (!((65 <= cmd[i] && cmd[i] <= 90) || cmd[i] == 95 \
			|| (97 <= cmd[i] && cmd[i] <= 122)))
				return (FAIL);
		}
		else
		{
			if (!((65 <= cmd[i] && cmd[i] <= 90) || cmd[i] == 95 \
			|| (97 <= cmd[i] && cmd[i] <= 122) || ('0' <= cmd[i] \
			&& cmd[i] <= '9')))
				return (FAIL);
		}
	}
	return (SUCCESS);
}

int	start_unset(char **cmd, t_env_var *env_var)
{
	int	status;
	int	i;

	status = 0;
	i = 0;
	if ((int)ft_two_strlen(cmd) - 1 >= 1)
	{
		infile_make(cmd);
		while (cmd[++i])
		{
			if (parsing_unset(cmd[i]) == FAIL)
			{
				ft_putstr_fd("bash: unset: `", 2);
				ft_putstr_fd(cmd[i], 2);
				ft_putstr_fd("': not a valid identifier\n", 2);
				status = 1;
				continue ;
			}
			del_env(cmd[i], env_var);
			del_exp(cmd[i], env_var);
		}
	}
	return (status);
}
