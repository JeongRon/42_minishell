/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_child.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongmiki <dongmiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 18:12:56 by jeongrol          #+#    #+#             */
/*   Updated: 2023/09/19 14:56:41 by dongmiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	filepath_search(char **cmd2, char *cmd, char *filepath)
{
	int	i;
	int	j;
	int	length;

	check_cmd(cmd2, &g_minishell->env_var);
	if (access(cmd, F_OK) == 0)
		return (0);
	i = -1;
	while (g_minishell->env_var.path != 0 && \
	g_minishell->env_var.path[++i] != NULL)
	{
		j = -1;
		while (++j < BUFFER_SIZE)
			filepath[j] = 0;
		length = ft_strlen(g_minishell->env_var.path[i]) + 1;
		ft_strlcat(filepath, g_minishell->env_var.path[i], length);
		ft_strlcat(filepath, "/", ft_strlen(filepath) + 2);
		ft_strlcat(filepath, cmd, ft_strlen(filepath) + ft_strlen(cmd) + 1);
		if (access(filepath, F_OK) == 0)
			return (1);
	}
	write(2, cmd, ft_strlen(cmd));
	write(2, ": command not found\n", 21);
	exit(127);
}

static void	first_child_process(char **env, int *fd)
{
	char	file_path[BUFFER_SIZE];
	int		file_flag;
	int		i;

	i = -1;
	close(fd[0]);
	ft_dup2(fd[1], STDOUT_FILENO);
	close(fd[1]);
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

static void	middle_child_process(char **env, int i, int *fd, int *pre_pipe)
{
	char	file_path[BUFFER_SIZE];
	int		file_flag;
	int		j;

	j = -1;
	close(fd[0]);
	ft_dup2(fd[1], STDOUT_FILENO);
	close(fd[1]);
	ft_dup2(pre_pipe[0], STDIN_FILENO);
	close(pre_pipe[0]);
	close(pre_pipe[1]);
	while (g_minishell->token[i].redirection[++j])
		set_redirection(g_minishell->token[i].redirection[j]);
	if (!g_minishell->token[0].cmd[0])
		exit(0);
	file_flag = filepath_search(g_minishell->token[i].cmd, \
	g_minishell->token[i].cmd[0], file_path);
	if (file_flag == 0)
		ft_execve(g_minishell->token[i].cmd[0], g_minishell->token[i].cmd, env);
	else
		ft_execve(file_path, g_minishell->token[i].cmd, env);
}

static void	last_child_process(char **env, int i, int *fd, int *pre_pipe)
{
	char	file_path[BUFFER_SIZE];
	int		file_flag;
	int		j;

	j = -1;
	ft_dup2(pre_pipe[0], STDIN_FILENO);
	close(pre_pipe[0]);
	close(pre_pipe[1]);
	close(fd[0]);
	close(fd[1]);
	while (g_minishell->token[i].redirection[++j])
		set_redirection(g_minishell->token[i].redirection[j]);
	if (!g_minishell->token[0].cmd[0])
		exit(0);
	file_flag = filepath_search(g_minishell->token[i].cmd, \
	g_minishell->token[i].cmd[0], file_path);
	if (file_flag == 0)
		ft_execve(g_minishell->token[i].cmd[0], g_minishell->token[i].cmd, env);
	else
		ft_execve(file_path, g_minishell->token[i].cmd, env);
}

void	child_process(int i, char **env, int fd[], int pre_pipe[])
{
	int	k;
	int	j;

	k = -1;
	while (++k < i)
	{
		j = -1;
		while (g_minishell->token[k].redirection[++j])
		{
			if (!ft_strncmp(g_minishell->token[k].redirection[j][0], "<<", 3))
				g_minishell->here_doc_count++;
		}
	}
	if (i == 0)
		first_child_process(env, fd);
	else if (i == g_minishell->token_num - 1)
		last_child_process(env, i, fd, pre_pipe);
	else
		middle_child_process(env, i, fd, pre_pipe);
}
