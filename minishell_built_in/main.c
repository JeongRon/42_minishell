/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongmiki <dongmiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 14:05:15 by jeongrol          #+#    #+#             */
/*   Updated: 2023/09/11 14:31:06 by dongmiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	main(int ac, char **av, char **envp)
{
	t_env_var	env_var;

	if (set_env_var(&env_var, envp) == 0)
		return (0);
	// 파싱 임시 처리
	char *cmd[] = {"cd", "erroror", "asd" NULL};
	check_cmd(cmd, &env_var);
	// <====================TEST=====================>
	// printf("-------------exp-------------------\n");
	// print_exp(&env_var);
	// printf("-------------env----------------\n");
	// print_env(&env_var);
	return (0);
}

// 실행 파트 만들기 