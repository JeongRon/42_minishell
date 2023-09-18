/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_excute_main.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongmiki <dongmiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 18:01:27 by dongmiki          #+#    #+#             */
/*   Updated: 2023/09/18 16:21:45 by dongmiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	one_process(char **env)
{
	char	file_path[BUFFER_SIZE];
	int		file_flag;
	int		i;

	i = -1;
	while (g_minishell->token[0].redirection[++i])
		set_redirection(g_minishell->token[0].redirection[i]);
	if (!g_minishell->token[0].cmd[0])
		exit(0);
	file_flag = filepath_search(g_minishell->token[0].cmd, \
	g_minishell->token[0].cmd[0], file_path);
	if (file_flag == 0)
		ft_execve(g_minishell->token[0].cmd[0], g_minishell->token[0].cmd, env);
	else
		ft_execve(file_path, g_minishell->token[0].cmd, env);
}

static void	one_pipe_exec(char **env)
{
	pid_t	pid;

	setting_signal(1, 1);
	pid = ft_fork();
	if (pid == 0)
	{
		one_process(env);
	}
	setting_signal(2, 2);
	wait_child();
}

int	excute_token(char **envp)
{
	if (g_minishell->token_num == 1)
		one_pipe_exec(envp);
	else
		multi_pipe_exec(envp, -1);
	return (0);
}
