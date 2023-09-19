/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_error.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongmiki <dongmiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 15:56:16 by dongmiki          #+#    #+#             */
/*   Updated: 2023/09/18 16:53:51 by dongmiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error(char *str, int flag)
{
	if (!str)
		ft_putstr_fd("bash: bad argument\n", 2);
	else
		ft_putendl_fd(str, 2);
	exit(flag);
}
