/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongmiki <dongmiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 16:40:13 by dongmiki          #+#    #+#             */
/*   Updated: 2023/09/12 15:28:21 by dongmiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** 말록 선언을 하는 함수 / 실패시 에러로 종료된다.
** void
**
** @param		size	할당할 크기
*/

void	*ft_malloc(size_t size)
{
	void	*temp;

	temp = malloc(size);
	if (!temp)
		error("bash: system error(malloc fail)", 1);
	return (temp);
}

static void	free_token2(int i)
{
	int	j;
	int	k;

	j = -1;
	if (g_minishell->token[i].cmd)
	{
		while (g_minishell->token[i].cmd[++j] != NULL)
			free(g_minishell->token[i].cmd[j]);
		j = -1;
		free(g_minishell->token[i].cmd);
	}
	if (g_minishell->token[i].redirection)
	{
		while (g_minishell->token[i].redirection[++j] != NULL)
		{
			k = -1;
			while (g_minishell->token[i].redirection[j][++k] != NULL)
				free(g_minishell->token[i].redirection[j][k]);
			free(g_minishell->token[i].redirection[j]);
		}
		free(g_minishell->token[i].redirection);
	}
}

void	free_token(void)
{
	int	i;

	i = -1;
	if (g_minishell->token)
	{
		while (++i < g_minishell->token_num)
			free_token2(i);
		free(g_minishell->token);
	}
	g_minishell->token = NULL;
}

void	switch_exit_code(void)
{
	char	*temp;
	char	**temp2;
	int		infile;

	infile = open("builtin_file.txt", O_RDONLY, 0600);
	if (infile != -1)
	{
		temp = get_next_line(infile);
		temp2 = ft_split(temp, ' ');
		free(temp);
		close(infile);
		unlink("builtin_file.txt");
		g_minishell->exit_code = check_cmd2(temp2, &g_minishell->env_var);
		free(temp2);
	}
	temp = g_minishell->env_var.env[0];
	g_minishell->env_var.env[0] = ft_strjoin("?=", \
	ft_itoa(g_minishell->exit_code));
	free(temp);
}
