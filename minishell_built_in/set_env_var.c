/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env_var.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongmiki <dongmiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 14:06:30 by jeongrol          #+#    #+#             */
/*   Updated: 2023/09/11 15:53:54 by dongmiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_home(char *envp)
{
	if (envp[0] == 'H' && envp[1] == 'O'
		&& envp[2] == 'M' && envp[3] == 'E'
		&& envp[4] == '=')
		return (SUCCESS);
	return (FAIL);
}

static int	check_path(char *envp)
{
	if (envp[0] == 'P' && envp[1] == 'A'
		&& envp[2] == 'T' && envp[3] == 'H'
		&& envp[4] == '=')
		return (SUCCESS);
	return (FAIL);
}

static int	allocate_env_exp(t_env_var *env_var, int cnt)
{
	env_var->env = (char **)malloc(sizeof(char *) * (cnt + 1));
	if (!env_var->env)
		return (FAIL);
	env_var->exp = (char **)malloc(sizeof(char *) * (cnt + 1));
	if (!env_var->exp)
		return (FAIL);
	return (SUCCESS);
}

static int	fill_env_exp(t_env_var *env_var, char **envp, int i)
{
	env_var->env[i] = ft_strdup(envp[i - 1]);
	if (!env_var->env[i])
		return (FAIL);
	env_var->exp[i] = ft_exp_strdup(envp[i - 1]);
	if (!env_var->exp[i])
		return (FAIL);
	if (check_path(envp[i - 1]))
	{
		env_var->path = ft_split(&envp[i - 1][5], ':');
		if (!env_var->path)
			return (FAIL);
	}
	if (check_home(envp[i - 1]))
	{
		env_var->home = ft_strdup(&envp[i - 1][5]);
		if (!env_var->home)
			return (FAIL);
	}
	return (SUCCESS);
}

int	set_env_var(t_env_var *env_var, char **envp)
{
	int	i;
	int	env_cnt;

	env_cnt = 0;
	while (envp[env_cnt])
		env_cnt++;
	env_cnt++;
	if (allocate_env_exp(env_var, env_cnt) == FAIL)
		perror("MALLOC");
	env_var->env[0] = ft_strdup("$?=0");
	env_var->exp[0] = ft_exp_strdup("$?=0");
	i = 0;
	while (++i < env_cnt)
		if (fill_env_exp(env_var, envp, i) == FAIL)
			perror("MALLOC");
	env_var->env[i] = NULL;
	env_var->exp[i] = NULL;
	env_var->env_cnt = env_cnt;
	env_var->exp_cnt = env_cnt;
	env_var->status = 0;
	del_exp("$?", env_var);
	sort_exp(env_var);
	add_exp("OLDPWD", env_var);
	return (1);
}
