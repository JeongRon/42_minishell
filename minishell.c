/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongmiki <dongmiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 15:19:53 by dongmiki          #+#    #+#             */
/*   Updated: 2023/09/12 18:11:37 by dongmiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** shell 시작시 모양 출력
** void
**
*/

static void	print_shell(void)
{
	printf("#########################################################\n\
#                                                       #\n\
# MM    MM iii         iii       hh             lll lll #\n\
# MMM  MMM     nn nnn       sss  hh        eee  lll lll #\n\
# MM MM MM iii nnn  nn iii s     hhhhhh  ee   e lll lll #\n\
# MM    MM iii nn   nn iii  sss  hh   hh eeeee  lll lll #\n\
# MM    MM iii nn   nn iii     s hh   hh  eeeee lll lll #\n\
#                           sss                         #\n\
#                                                       #\n\
#########################################################\n\
########################### made by. jeongrol, dongmiki #\n\
#########################################################\n\n");
}

int	is_whitespace(char *line)
{
	while (*line)
	{
		if (*line != 32 && !(*line >= 9 && *line <= 13))
		{
			return (0);
		}
		line++;
	}
	return (1);
}

static void	main_progress(int status, char *input, pid_t pid)
{
	while (1)
	{
		input = readline("minishell$> ");
		if (!input)
			break ;
		if (*input != '\0')
			add_history(input);
		pid = ft_fork();
		setting_signal(2, 2);
		if (pid == 0)
		{
			if (*input != '\0' && !is_whitespace(input))
			{
				parse_input(g_minishell, input, g_minishell->env_var.env);
				excute_token(g_minishell->env_var.env);
				free_token();
			}
			exit(g_minishell->exit_code);
		}
		wait(&status);
		g_minishell->exit_code = WEXITSTATUS(status);
		switch_exit_code();
		setting_signal(0, 0);
		free(input);
	}
}

static void	term_setting(void)
{
	struct termios	term;

	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~(NOFLSH | ECHOCTL);
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

int	main(int ac, char **av, char **envp)
{	
	struct termios	main_term;

	if (ac != 1 || !av || !envp)
		error(0, 1);
	tcgetattr(STDIN_FILENO, &main_term);
	g_minishell = (t_minishell *)ft_malloc(sizeof(t_minishell));
	if (set_env_var(&g_minishell->env_var, envp) == 0)
		return (0);
	g_minishell->exit_code = 0;
	g_minishell->token_num = 0;
	print_shell();
	term_setting();
	setting_signal(0, 0);
	main_progress(0, NULL, 0);
	printf("exit\n");
	tcsetattr(STDIN_FILENO, TCSANOW, &main_term);
	return (0);
}
