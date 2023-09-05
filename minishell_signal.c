/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_signal.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongmiki <dongmiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 20:11:51 by dongmiki          #+#    #+#             */
/*   Updated: 2023/09/04 21:58:22 by dongmiki         ###   ########.fr       */
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

void	setting_signal(int sig_int, int sig_quit)
{
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


//0.ctrl+c의 경우 부모(메인프로세스와)포크 된 명령어 처리중 인 놈의 signal처리를 다르게 해야함

//1.ctrl+D (15, SIGTERM)
//if (sig == SIGINT)//ctrl+d
// ctrl+d
// EOF를 의미
// 시그널이 아니다.
// stdin pipe를 닫는다. (read(STDIN) return 0)