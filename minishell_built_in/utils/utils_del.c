/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_del.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongmiki <dongmiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 13:30:03 by jeongrol          #+#    #+#             */
/*   Updated: 2023/09/11 15:53:54 by dongmiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	del_env_key(int del_index, t_env_var *env_var)
{
	char	**tmp;
	int		x;
	int		y;

	env_var->env_cnt -= 1;
	tmp = (char **)malloc((sizeof(char *)) * (env_var->env_cnt + 1));
	if (!tmp)
		perror("MALLOC");
	x = 0;
	y = 0;
	while (y < env_var->env_cnt)
	{
		if (x == del_index)
		{
			x++;
			continue ;
		}
		tmp[y] = ft_strdup(env_var->env[x]);
		x++;
		y++;
	}
	tmp[y] = NULL;
	ft_free(env_var->env);
	env_var->env = tmp;
}

void	del_env(char *cmd, t_env_var *env_var)
{
	char	*cmd_key;
	char	*env_key;
	int		i;

	cmd_key = key_strdup(cmd);
	i = -1;
	while (env_var->env[++i])
	{
		env_key = key_strdup(env_var->env[i]);
		if (ftj_strcmp(cmd_key, env_key) == 0)
		{
			del_env_key(i, env_var);
			free(env_key);
			break ;
		}
		free(env_key);
	}
	free(cmd_key);
}

static void	del_exp_key(int del_index, t_env_var *env_var)
{
	char	**tmp;
	int		x;
	int		y;

	env_var->exp_cnt -= 1;
	tmp = (char **)malloc((sizeof(char *)) * (env_var->exp_cnt + 1));
	if (!tmp)
		perror("MALLOC");
	x = 0;
	y = 0;
	while (y < env_var->exp_cnt)
	{
		if (x == del_index)
		{
			x++;
			continue ;
		}
		tmp[y] = ft_strdup(env_var->exp[x]);
		x++;
		y++;
	}
	tmp[y] = NULL;
	ft_free(env_var->exp);
	env_var->exp = tmp;
}

void	del_exp(char *cmd, t_env_var *env_var)
{
	char	*cmd_key;
	char	*exp_key;
	int		i;

	cmd_key = key_strdup(cmd);
	i = -1;
	while (env_var->exp[++i])
	{
		exp_key = key_strdup(&env_var->exp[i][11]);
		if (ftj_strcmp(cmd_key, exp_key) == 0)
		{
			del_exp_key(i, env_var);
			sort_exp(env_var);
			free(exp_key);
			break ;
		}
		free(exp_key);
	}
	free(cmd_key);
}
