/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_makeinfile.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongmiki <dongmiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 18:04:29 by dongmiki          #+#    #+#             */
/*   Updated: 2023/09/11 19:09:32 by dongmiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	infile_make(char **cmd)
{
	int	infile;
	int	i;

	if (g_minishell->token_num != 1)
		return ;
	infile = open("builtin_file.txt", O_WRONLY | O_TRUNC | O_CREAT, 0600);
	if (infile == -1)
		ft_error("Infile Open Error");
	i = -1;
	while (cmd[++i])
	{
		write(infile, cmd[i], ftj_strlen(cmd[i]));
		write(infile, " ", 1);
	}
	close(infile);
	exit(0);
}
