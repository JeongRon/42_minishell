/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_split_quote2.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongmiki <dongmiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 16:07:26 by dongmiki          #+#    #+#             */
/*   Updated: 2023/08/04 16:48:10 by dongmiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_null(char **str, int count)
{
	int	index;

	if (str[count] != NULL)
		return (0);
	index = 0;
	while (index < count)
		free(str[index++]);
	free(str);
	return (1);
}
