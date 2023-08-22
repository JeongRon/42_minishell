/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_error.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongmiki <dongmiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 15:56:16 by dongmiki          #+#    #+#             */
/*   Updated: 2023/08/22 16:24:09 by dongmiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** 에러시 실행되는 코드 및 종료
** void
**
** @param		str	실패시 종료에 출력할 문자열
*/

void	error(char *str)
{
	if (!str)
		ft_putstr_fd("bash: bad argument", 2);
	else
		ft_putstr_fd(str, 2);
	exit(EXIT_FAILURE);
}
