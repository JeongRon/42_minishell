/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_input.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongmiki <dongmiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 16:32:20 by dongmiki          #+#    #+#             */
/*   Updated: 2023/08/05 16:03:45 by dongmiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse_input(t_minishell *minishell, char *str)
{
	char	**temp2;

	temp2 = continue_quote(str);
	make_token(minishell, temp2);
	free(temp2);
}
