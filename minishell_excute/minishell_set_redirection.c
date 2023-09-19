/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_set_redirection.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongmiki <dongmiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 19:35:05 by dongmiki          #+#    #+#             */
/*   Updated: 2023/09/19 14:56:48 by dongmiki         ###   ########.fr       */
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

static void	redirection_input_here_doc(void)
{
	int		infile;
	char	*tmp;
	char	*tmp2;

	g_minishell->here_doc_count++;
	tmp = ft_itoa(g_minishell->here_doc_count);
	tmp2 = ft_strjoin("/tmp/minishell_here_doc", tmp);
	free(tmp);
	tmp = ft_strjoin(tmp2, ".txt");
	free(tmp2);
	infile = open(tmp, O_RDONLY, 0600);
	if (infile == -1)
		ft_error("System error(here_doc open error)");
	ft_dup2(infile, STDIN_FILENO);
	close(infile);
	unlink(tmp);
	free(tmp);
}

static void	redirection_output_append(char **str)
{
	int	outfile;

	outfile = open(str[1], O_WRONLY | O_APPEND | O_CREAT, 0600);
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
		redirection_input_here_doc();
	else if (!ft_strncmp(str[0], ">", 2))
		redirection_output(str);
	else if (!ft_strncmp(str[0], ">>", 3))
		redirection_output_append(str);
}
