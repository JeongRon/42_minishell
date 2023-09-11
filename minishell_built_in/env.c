/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongmiki <dongmiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 16:08:27 by jeongrol          #+#    #+#             */
/*   Updated: 2023/09/11 14:50:22 by dongmiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_env(t_env_var *env_var)
{
	int	i;

	i = 1;
	while (env_var->env[i])
	{
		printf("%s\n", env_var->env[i]);
		i++;
	}
}

// env ->> 에러 코드 리턴
int	start_env(char **cmd, t_env_var *env_var)
{
	int	cmd_cnt;

	cmd_cnt = ft_two_strlen(cmd);
	if (cmd_cnt >= 2)
	{
		printf("env: %s: No such file or directory\n", cmd[1]);
		return (127);
	}
	print_env(env_var);
	return (0);
}
