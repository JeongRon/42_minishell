/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongmiki <dongmiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 15:19:53 by dongmiki          #+#    #+#             */
/*   Updated: 2023/08/10 19:48:27 by dongmiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//전역변수는 signal예상

int	main(int ac, char **av, char **envp)
{	
	char		*input;
	t_minishell	*minishell;

	if (ac != 1 || !av || !envp)
		error(0);
	//exit나

	minishell = (t_minishell *)ft_malloc(sizeof(t_minishell));
	while (1)
	{
		//읽고(',"의 경우 quote>로 쭉 읽기)
		input = readline("minishell$> ");
		add_history(input);
		parse_input(minishell, input);

		int i = 0;
		while (i < minishell->token_num)
		{
			t_token temp = (minishell->token)[i];
			int j = -1;
			printf("token[%d]\ncmd:  ", i);
			while (temp.cmd[++j])
			{
				printf("%s, ", temp.cmd[j]);
			}
			printf("\nredirection\n");
			j = -1;
			while (temp.redirection[++j])
			{
				int k = -1;
				while (temp.redirection[j][++k])
					printf("%s, ", temp.redirection[j][k]);
				printf("\n");
			}
			i++;
		}

		printf("\nFinish Pasing\n");

		
		//나누고
		//처리하고
		//히스토리저장(add_history)
		//다시 받기
		//종료시그널시 종료(이 과정은 어디에나 있음)
		//free(token);//내부 구조체도 프리
	}
	return (0);
}
//해야할일 
// -1. cat<input 이런거 리더랙션 다 읽어야함
// 0. \, ; 처리->해석하지 않아야 합니다.... "안 닫히는 부분도 하지 않아야 합니다...
// 1. $처리하기
// 2. shell 만들고 연결..?