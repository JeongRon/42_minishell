/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_set_redirection.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongmiki <dongmiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 19:35:05 by dongmiki          #+#    #+#             */
/*   Updated: 2023/09/08 16:41:17 by dongmiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	redirection_input(char **str)
{
	int	infile;

	infile = open(str[1], O_RDONLY, 0600);
	if (infile == -1)
		ft_error("Infile Open Error");
	ft_dup2(infile, STDIN_FILENO);
	close(infile);
}

static void	redirection_output(char **str)
{
	int	outfile;

	outfile = open(str[1], O_WRONLY | O_TRUNC | O_CREAT, 0600);
	if (outfile == -1)
		ft_error("Outfile Open Error");
	ft_dup2(outfile, STDOUT_FILENO);
	close(outfile);
}

static void	redirection_input_here_doc(char **str)
{
	pid_t	pid;
	int		fd[2];
	char	*line;

	ft_pipe(fd);
	pid = ft_fork();
	if (pid == 0)
	{
		close(fd[0]);
		line = readline("> ");
		while (line)
		{
			if (!ft_strncmp(str[1], line, ft_strlen(str[1])) \
			&& (!ft_strncmp(str[1], line, ft_strlen(line) - 1)))
				exit(EXIT_SUCCESS);
			write(fd[1], line, ft_strlen(line));
			write(fd[1], "\n", 2);
			free(line);
			line = readline("> ");
		}
	}
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	waitpid(pid, NULL, 0);
}

static void	redirection_output_append(char **str)
{
	int	outfile;

	outfile = open(str[1], O_WRONLY | O_TRUNC | O_CREAT, 0600);
	if (outfile == -1)
		ft_error("Outfile Open Error");
	ft_dup2(outfile, STDOUT_FILENO);
	close(outfile);
}

void	set_redirection(char **str)
{
	if (!ft_strncmp(str[0], "<", 2))
		redirection_input(str);
	else if (!ft_strncmp(str[0], "<<", 3))
		redirection_input_here_doc(str);
	else if (!ft_strncmp(str[0], ">", 2))
		redirection_output(str);
	else if (!ft_strncmp(str[0], ">>", 3))
		redirection_output_append(str);
}
