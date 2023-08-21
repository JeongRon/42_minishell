/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_error.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongmiki <dongmiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 15:56:16 by dongmiki          #+#    #+#             */
/*   Updated: 2023/08/21 22:45:25 by dongmiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error(char *str)
{
	if (!str)
		ft_putstr_fd("bash: bad argument", 2);
	else
		ft_putstr_fd(str, 2);
	exit(EXIT_FAILURE);
}
