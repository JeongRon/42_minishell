/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_signal.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongmiki <dongmiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 20:11:51 by dongmiki          #+#    #+#             */
/*   Updated: 2023/09/19 15:09:23 by dongmiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	minishell_signal(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	if (sig == SIGQUIT)
	{
		rl_on_new_line();
		rl_redisplay();
	}
}

static void	minishell_signal_here_doc(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		exit(1);
	}
}

void	setting_signal(int sig_int, int sig_quit)
{
	if (sig_int == 3)
		signal(SIGINT, minishell_signal_here_doc);
	if (sig_int == 2)
		signal(SIGINT, SIG_IGN);
	if (sig_int == 1)
		signal(SIGINT, SIG_DFL);
	if (sig_int == 0)
		signal(SIGINT, minishell_signal);
	if (sig_quit == 2)
		signal(SIGQUIT, SIG_IGN);
	if (sig_quit == 1)
		signal(SIGQUIT, SIG_DFL);
	if (sig_quit == 0)
		signal(SIGQUIT, minishell_signal);
}
