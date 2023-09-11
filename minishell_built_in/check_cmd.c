/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongmiki <dongmiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 16:21:25 by jeongrol          #+#    #+#             */
/*   Updated: 2023/09/11 20:48:03 by dongmiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_cmd(char **cmd, t_env_var *env_var)
{
	if (ftj_strcmp(cmd[0], "env") == 0)
		exit(start_env(cmd, env_var));
	else if (ftj_strcmp(cmd[0], "pwd") == 0)
		exit(print_pwd());
	else if (ftj_strcmp(cmd[0], "export") == 0)
		exit(start_export(cmd, env_var));
	else if (ftj_strcmp(cmd[0], "unset") == 0)
		exit(start_unset(cmd, env_var));
	else if (ftj_strcmp(cmd[0], "echo") == 0)
		exit(start_echo(cmd));
	else if (ftj_strcmp(cmd[0], "exit") == 0)
		exit(start_exit(cmd));
	else if (ftj_strcmp(cmd[0], "cd") == 0)
		exit(start_cd(cmd, env_var));
}

int	check_cmd2(char **cmd, t_env_var *env_var)
{
	int	tmp_num;

	if (ftj_strcmp(cmd[0], "env") == 0)
		return (start_env(cmd, env_var));
	else if (ftj_strcmp(cmd[0], "pwd") == 0)
		return (print_pwd());
	else if (ftj_strcmp(cmd[0], "export") == 0)
		return (start_export(cmd, env_var));
	else if (ftj_strcmp(cmd[0], "unset") == 0)
		return (start_unset(cmd, env_var));
	else if (ftj_strcmp(cmd[0], "echo") == 0)
		return (start_echo(cmd));
	else if (ftj_strcmp(cmd[0], "exit") == 0)
	{
		tmp_num = start_exit(cmd);
		if (tmp_num == 256)
			return (tmp_num);
		exit(tmp_num);
	}
	else if (ftj_strcmp(cmd[0], "cd") == 0)
		return (start_cd(cmd, env_var));
	return (2);
}
