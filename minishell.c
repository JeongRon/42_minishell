/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongmiki <dongmiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 15:19:53 by dongmiki          #+#    #+#             */
/*   Updated: 2023/08/21 22:46:12 by dongmiki         ###   ########.fr       */
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
	minishell = (t_minishell *)ft_malloc(sizeof(t_minishell));
	while (1)
	{
		input = readline("minishell$> ");
		if (!input)
			continue;
		add_history(input);
		//여기서 포크???
		parse_input(minishell, input, envp);

		//여기서 부터 실행 부
		
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
// 1. $처리하기->끝??->token에 '\0'으로 남기는 하는데 사소해..?
// 2. shell 만들고 연결..?
// 3. signal