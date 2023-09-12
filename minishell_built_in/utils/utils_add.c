/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_add.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongmiki <dongmiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 13:39:22 by jeongrol          #+#    #+#             */
/*   Updated: 2023/09/11 21:23:44 by dongmiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_exp(char *cmd, t_env_var *env_var)
{
	char	**tmp;
	int		i;

	env_var->exp_cnt += 1;
	tmp = (char **)malloc(sizeof(char *) * (env_var->exp_cnt + 1));
	if (!tmp)
		perror("MALLOC");
	i = -1;
	while (env_var->exp[++i])
	{
		tmp[i] = ft_strdup(env_var->exp[i]);
		if (!tmp[i])
			perror("MALLOC");
	}
	tmp[i] = ft_exp_strdup(cmd);
	tmp[i + 1] = NULL;
	ft_free(env_var->exp);
	env_var->exp = tmp;
	sort_exp(env_var);
}

void	add_env(char *cmd, t_env_var *env_var)
{
	char	**tmp;
	int		i;

	env_var->env_cnt += 1;
	tmp = (char **)malloc(sizeof(char *) * (env_var->env_cnt + 1));
	if (!tmp)
		perror("MALLOC");
	i = -1;
	while (env_var->env[++i])
	{
		tmp[i] = ft_strdup(env_var->env[i]);
		if (!tmp[i])
			perror("MALLOC");
	}
	tmp[i] = ft_strdup(cmd);
	tmp[i + 1] = NULL;
	ft_free(env_var->env);
	env_var->env = tmp;
}
