/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_exp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongmiki <dongmiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 14:15:21 by jeongrol          #+#    #+#             */
/*   Updated: 2023/09/11 15:51:47 by dongmiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// 정렬 안된 맨 왼쪽 인덱스 catch해서 리턴
static int	catch_exp_index(t_env_var *env_var)
{
	int	catch;
	int	next;

	catch = 0;
	while (catch < env_var->exp_cnt)
	{
		if (!env_var->exp[catch])
			catch++;
		else
			break ;
	}
	next = catch;
	while (++next < env_var->exp_cnt)
	{
		if (!env_var->exp[next])
			continue ;
		else if (ftj_strcmp(env_var->exp[catch], env_var->exp[next]) > 0)
			catch = next;
	}
	return (catch);
}

// 선택 정렬
void	sort_exp(t_env_var *env_var)
{
	char	**exp_tmp;
	int		i;
	int		catch;

	exp_tmp = (char **)malloc(sizeof(char *) * (env_var->exp_cnt + 1));
	if (!exp_tmp)
		perror("MALLOC");
	i = 0;
	while (1)
	{
		catch = catch_exp_index(env_var);
		if (i == env_var->exp_cnt - 1)
		{
			exp_tmp[i] = ftj_strdup(env_var->exp[catch]);
			break ;
		}
		exp_tmp[i] = ftj_strdup(env_var->exp[catch]);
		free(env_var->exp[catch]);
		env_var->exp[catch] = NULL;
		i++;
	}
	exp_tmp[i + 1] = NULL;
	ft_free(env_var->exp);
	env_var->exp = exp_tmp;
}
