/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_util.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongmiki <dongmiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 14:23:55 by jeongrol          #+#    #+#             */
/*   Updated: 2023/09/18 16:23:19 by dongmiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_execve(char *filepath, char **av, char **envp)
{
	if (access(filepath, X_OK) == 0)
	{
		if (execve(filepath, av, envp) == -1)
		{
			write(2, "is a directory", 15);
			write(2, "\n", 1);
			exit(126);
		}
	}
	write(2, "Permission denied", 18);
	write(2, "\n", 1);
	exit(126);
}

void	ft_dup2(int old_fd, int new_fd)
{
	if (dup2(old_fd, new_fd) == -1)
		ft_error("dup2 Error");
}

pid_t	ft_fork(void)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		ft_error("fork Error");
	return (pid);
}

void	ft_pipe(int *fd)
{
	if (pipe(fd) == -1)
		ft_error("pipe Error");
}

void	ft_error(char *str)
{
	write(2, str, ft_strlen(str));
	write(2, "\n", 1);
	exit(EXIT_FAILURE);
}
