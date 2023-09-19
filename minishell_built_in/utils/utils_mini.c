/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_mini.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongrol <jeongrol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 18:42:51 by jeongrol          #+#    #+#             */
/*   Updated: 2023/09/19 16:38:24 by jeongrol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free(char **str)
{
	int	i;

	i = -1;
	while (str[++i])
		free(str[i]);
	free(str);
}

int	ft_two_strlen(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	update_path(void)
{
	int	i;

	ft_free(g_minishell->env_var.path);
	g_minishell->env_var.path = NULL;
	i = -1;
	while (g_minishell->env_var.env[++i])
	{
		if (check_path(g_minishell->env_var.env[i]))
		{
			g_minishell->env_var.path = \
			ft_split(&g_minishell->env_var.env[i][5], ':');
			if (!g_minishell->env_var.path)
				perror("MALLOC");
		}
	}
}
