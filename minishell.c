/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongmiki <dongmiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 15:19:53 by dongmiki          #+#    #+#             */
/*   Updated: 2023/09/05 18:44:39 by dongmiki         ###   ########.fr       */
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
		if (*input != '\0' && !is_whitespace(input))
		{
			parse_input(g_minishell, input, envp);
			excute_token(envp);
			//free_token
			setting_signal(0, 0);
		}
		if (is_whitespace(input))
			free(input);
	}
}

int	main(int ac, char **av, char **envp)
{	
	struct termios	term;

	if (ac != 1 || !av || !envp)
		error(0);
	g_minishell = (t_minishell *)ft_malloc(sizeof(t_minishell));
	print_shell();
	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~(ICANON | NOFLSH | ECHOCTL);
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
	setting_signal(0, 0);
	main_progress(envp);
	return (0);
}

//현제 시그널 동작중 자식안에서 ^c ,^\ 보이게 하기
//		->(를 치면 추가 출력 Quit: 3)2개가 보여야 하고 출력은 redirection과 관련없이 메인창에 출력
//free(token)
//here_doc
//$? 처리