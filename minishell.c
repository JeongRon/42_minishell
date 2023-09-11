/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongmiki <dongmiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 15:19:53 by dongmiki          #+#    #+#             */
/*   Updated: 2023/09/11 12:50:31 by dongmiki         ###   ########.fr       */
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

static void	main_progress(char **envp)//envp는 구조체가 만들어지기 전까지 임시 void로 바꾸ㅡ면됨
{
	char		*input;
	pid_t		pid;

	while (1)
	{
		input = readline("minishell$> ");
		if (!input)
		{
			printf("exit\n");//이거 붙여서 처리해야하는데..진짜 시발모르겠어
			break ;
		}
		if (*input != '\0')
			add_history(input);
		pid = ft_fork();
		setting_signal(2, 2);
		if (pid == 0)
		{
			if (*input != '\0' && !is_whitespace(input))
			{
				parse_input(g_minishell, input, envp);
				excute_token(envp);
				free_token();
			}
			exit(EXIT_SUCCESS);
		}
		wait(NULL);
		setting_signal(0, 0);
		free(input);
	}
}

void f1()
{
	system("leaks --list -- minishell");
}

static char	**get_cmd_path(char **env)
{
	int	index;

	index = -1;
	while (env[++index] != NULL)
	{
		if (ft_strncmp(env[index], "PATH=", 5) == 0)
			return (ft_split(&env[index][5], ':'));
	}
	return (0);
}	

static void term_setting(void)
{
	struct termios	term;

	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~(NOFLSH | ECHOCTL);
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

int	main(int ac, char **av, char **envp)
{	
	struct termios	main_term;

	//atexit(f1);
	if (ac != 1 || !av || !envp)
		error(0);
	tcgetattr(STDIN_FILENO, &main_term);
	g_minishell = (t_minishell *)ft_malloc(sizeof(t_minishell));
	print_shell();
	term_setting();
	setting_signal(0, 0);
	/*임시로 만든것*/
	g_minishell->temp_path = get_cmd_path(envp);
	main_progress(envp);
	tcsetattr(STDIN_FILENO, TCSANOW, &main_term);
	return (0);
}

//$?cjfl