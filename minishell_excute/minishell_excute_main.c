/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_excute_main.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongrol <jeongrol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 18:01:27 by dongmiki          #+#    #+#             */
/*   Updated: 2023/09/19 16:37:46 by jeongrol         ###   ########.fr       */
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

static void	here_doc_read(int infile, char **str)
{
	char	*tmp;

	tmp = readline("here_doc> ");
	while (1)
	{
		if (!tmp || (!ft_strncmp(str[1], tmp, ft_strlen(str[1])) \
		&& !ft_strncmp(str[1], tmp, ft_strlen(tmp))))
			break ;
		write(infile, tmp, ft_strlen(tmp));
		write(infile, "\n", 1);
		free(tmp);
		tmp = readline("here_doc> ");
	}
	if (tmp)
		free(tmp);
}

static void	here_doc_count(char **str)
{
	int		infile;
	char	*tmp;
	char	*tmp2;

	if (!ft_strncmp(str[0], "<<", 3))
	{
		setting_signal(3, 2);
		g_minishell->here_doc_count++;
		tmp = ft_itoa(g_minishell->here_doc_count);
		tmp2 = ft_strjoin("/tmp/minishell_here_doc", tmp);
		free(tmp);
		tmp = ft_strjoin(tmp2, ".txt");
		free(tmp2);
		infile = open(tmp, O_WRONLY | O_TRUNC | O_CREAT, 0600);
		if (infile == -1)
			ft_error("System error(here_doc)");
		free(tmp);
		here_doc_read(infile, str);
		close(infile);
		setting_signal(2, 2);
	}
}

int	excute_token(char **envp)
{
	int	i;
	int	j;

	i = -1;
	g_minishell->here_doc_count = 0;
	while (++i < g_minishell->token_num)
	{
		j = -1;
		while (g_minishell->token[i].redirection[++j])
			here_doc_count(g_minishell->token[i].redirection[j]);
	}
	g_minishell->here_doc_count = 0;
	update_path();
	if (g_minishell->token_num == 1)
		one_pipe_exec(envp);
	else
		multi_pipe_exec(envp, -1);
	return (0);
}
