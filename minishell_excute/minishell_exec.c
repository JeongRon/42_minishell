/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_exec.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongmiki <dongmiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 20:29:18 by jeongrol          #+#    #+#             */
/*   Updated: 2023/09/08 20:05:59 by dongmiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	wait_child(void)
{
	int		status;
	int		signo;
	int		i;

	i = 0;
	while (wait(&status) != -1)
	{
		if (WIFSIGNALED(status))
		{
			signo = WTERMSIG(status);
			if (signo == SIGINT && i++ == 0)
				ft_putstr_fd("^C\n", STDERR_FILENO);
			else if (signo == SIGQUIT && i++ == 0)
				ft_putstr_fd("^\\Quit: 3\n", STDERR_FILENO);
			g_minishell->exit_code = 128 + signo;
		}
		else
			g_minishell->exit_code = WEXITSTATUS(status);
	}
}

static pid_t	*pid_set(int cmd_cnt)
{
	pid_t	*pid;

	pid = (pid_t *)malloc(sizeof(pid_t) * cmd_cnt);
	if (!pid)
		ft_error("PID Allocation Error");
	return (pid);
}

static void	close_pre_pipe(int pre_pipe[])
{
	close(pre_pipe[0]);
	close(pre_pipe[1]);
}

void	multi_pipe_exec(char **env, int index)
{
	int		pre_pipe[2];
	int		fd[2];

	g_minishell->pid = pid_set(g_minishell->token_num);
	while (++index < g_minishell->token_num)
	{
		if (index > 1)
			close_pre_pipe(pre_pipe);
		pre_pipe[0] = fd[0];
		pre_pipe[1] = fd[1];
		if (index != g_minishell->token_num)
			ft_pipe(fd);
		setting_signal(1, 1);
		g_minishell->pid[index] = ft_fork();
		if (g_minishell->pid[index] == 0)
			child_process(index, env, fd, pre_pipe);
		setting_signal(2, 2);
	}
	close_pre_pipe(fd);
	close_pre_pipe(pre_pipe);
	wait_child();
	free(g_minishell->pid);
}
