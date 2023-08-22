/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_input_token.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongmiki <dongmiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 21:03:48 by dongmiki          #+#    #+#             */
/*   Updated: 2023/08/22 19:46:23 by dongmiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** minishell의 token에 redirection을 넣어주는 함수
** void
**
** @param		token	minishell의 token변수
** @param		str		token에 넣을 redirection의 이중 포인터
** @param		i		str('|'로 나누어진 후 ' '으로 나누어진 명령어)의 몇번째 인자인지
** @param		num		token의 몇번째 redirection인지
*/

static void	input_redirection(t_token *token, char **str, int *i, int *num)
{
	token->redirection[*num] = (char **)ft_malloc(sizeof(char *) * 3);
	token->redirection[*num][0] = str[*i];
	if (!str[(*i) + 1])
		error("bash: syntax error near unexpected token `newline'");
	token->redirection[*num][1] = str[(*i) + 1];
	token->redirection[*num][2] = NULL;
	(*num)++;
	(*i)++;
}

/*
** minishell의 token에 cmd을 넣어주는 함수
** void
**
** @param		token	minishell의 token변수
** @param		str		token에 넣을 cmd의 포인터
** @param		i		str('|'로 나누어진 후 ' '으로 나누어진 명령어)의 몇번째 인자인지
** @param		num		token의 몇번째 cmd인지
*/

static void	input_cmd(t_token *token, char **str, int i, int *num)
{
	token->cmd[*num] = str[i];
	(*num)++;
}

/*
** minishell의 token에 받은 이중 문자열 str('|'으로 나누어진)을 알맞게 분배해서 넣는 함수
** token의 cmd, redirection에 알맞게 넣는다.
** 길어서 2개로 나누어진 후반부
** void
**
** @param		token	minishell의 token변수
** @param		str		'|'으로 나누어진 명령어 목록
*/

static void	input_token_second(t_token *token, char **str, \
int num_cmd, int num_redirect)
{
	int	i;

	token->redirection = (char ***)ft_malloc(sizeof(char **) * \
	(num_redirect + 1));
	token->redirection[num_redirect] = NULL;
	token->cmd = (char **)ft_malloc(sizeof(char *) * (num_cmd + 1));
	token->cmd[num_cmd] = NULL;
	i = -1;
	num_redirect = 0;
	num_cmd = 0;
	while (str[++i])
	{
		if (!ft_strncmp(str[i], "<", 2))
			input_redirection(token, str, &i, &num_redirect);
		else if (!ft_strncmp(str[i], "<<", 3))
			input_redirection(token, str, &i, &num_redirect);
		else if (!ft_strncmp(str[i], ">", 2))
			input_redirection(token, str, &i, &num_redirect);
		else if (!ft_strncmp(str[i], ">>", 3))
			input_redirection(token, str, &i, &num_redirect);
		else
			input_cmd(token, str, i, &num_cmd);
	}
}

/*
** minishell의 token에 받은 이중 문자열 str('|'으로 나누어진)을 알맞게 분배해서 넣는 함수
** 각각의 token에 들어간 cmd, redirection의 갯수를 샌다.
** 길어서 2개로 나누어진 전반부
** void
**
** @param		token	minishell의 token변수
** @param		str		'|'으로 나누어진 명령어 목록
*/

static void	input_token(t_token *token, char **str)
{
	int	i;
	int	num_redirect;
	int	num_cmd;

	i = -1;
	num_redirect = 0;
	num_cmd = 0;
	while (str[++i])
	{
		if (!ft_strncmp(str[i], "<", 2))
			num_redirect++;
		else if (!ft_strncmp(str[i], "<<", 3))
			num_redirect++;
		else if (!ft_strncmp(str[i], ">", 2))
			num_redirect++;
		else if (!ft_strncmp(str[i], ">>", 3))
			num_redirect++;
		else
			num_cmd++;
	}
	num_cmd -= num_redirect;
	input_token_second(token, str, num_cmd, num_redirect);
}

/*
** minishell의 token에 받은 이중 문자열 str('|'으로 나누어진)을 알맞게 분배해서 넣는 함수
** 각 토큰 갯수('|'으로 나누어진 명령어)를 ' '으로 나눈후 $(env)처리 후 token화 해준다.
** void
**
** @param		minishell		minishell의 구조체
** @param		str_split_pipe	'|'으로 나누어진 명령어 목록 
** @param		envp			환경변수
*/

void	make_token(t_minishell *minishell, char **str_split_pipe, char **envp)
{
	int		i;
	int		j;
	char	**temp;

	i = -1;
	while (str_split_pipe[++i])
	{
	}
	minishell->token = (t_token *)ft_malloc(sizeof(t_token) * i);
	minishell->token_num = i;
	i = -1;
	while (str_split_pipe[++i])
	{
		temp = ft_split_quote(str_split_pipe[i], ' ', 0);
		if (!temp)
			error("bash: system error(malloc fail)");
		j = -1;
		while (temp[++j])
			temp[j] = quote_conversion(temp[j], envp);
		input_token(&(minishell->token[i]), temp);
		free(temp);
	}
}
