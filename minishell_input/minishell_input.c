/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_input.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongmiki <dongmiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 16:32:20 by dongmiki          #+#    #+#             */
/*   Updated: 2023/09/18 14:07:35 by dongmiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** str을 받아 n만큼 복사해주는 함수
** envp의 path를 찾기 위해 '='을 뒤에 추가해서 복사해준다.
** char *
**
** @param		src	복사할 문자열의 주소
** @param		n	복사할 양
*/

static char	*ft_strdup_path(char *src, int n)
{
	int		i;
	char	*add;

	add = (char *)malloc(sizeof(char) * (n + 2));
	if (!add)
		error ("bash: system error(malloc fail)", 1);
	i = 0;
	while (src[i] && i < n)
	{
		add[i] = src[i];
		i++;
	}
	add[i] = '=';
	add[++i] = '\0';
	return (add);
}

/*
** 원본 문자열에서 환경변수를 바꾸어서 출력해주는 함수
** char *
**
** @param		str			받은 명령어
** @param		needele		환경 변수의 원본
** @param		i			원본 문자열의 환경변수 부분의 시작 지점
** @param		j			원본 문자열의 환경변수 부분의 끝 지점
*/

static char	*add_str(char *str, char *needle, int i, int j)
{
	int		temp_num;
	int		needle_num;
	int		str_num;
	char	*temp;

	temp = (char *)ft_malloc(sizeof(char) * (ft_strlen(needle) + \
			ft_strlen(str) - j + i + 1));
	temp_num = -1;
	str_num = -1;
	while (str[++str_num] && str_num < i)
		temp[++temp_num] = str[str_num];
	needle_num = -1;
	while (needle != NULL && needle[++needle_num])
		temp[++temp_num] = needle[needle_num];
	j--;
	while (str[++j])
		temp[++temp_num] = str[j];
	temp[++temp_num] = '\0';
	free(str);
	if (needle != NULL)
		free(needle);
	return (temp);
}

/*
** 환경변수가 있는지 확인 하는 함수
** char *
** 없으면 NULL을 반환
**
** @param		str			받은 환경변수 이름
** @param		envp		환경변수
*/

char	*find_path(char *str, char **envp)
{
	char	*env;
	int		i;

	if (!str)
		return (NULL);
	i = 0;
	while (envp[i] && ft_strnstr(envp[i], str, ft_strlen(str)) == 0)
		i++;
	free(str);
	if (!envp[i])
		return (NULL);
	env = ft_strdup(envp[i] + ft_strlen(str));
	if (!env)
		error("bash: system error(malloc fail)", 1);
	return (env);
}

/*
** 받은 문자열(명령어)에서 $(환경변수)가 있으면 해석하고 quote를 제거해서 반환하는 함수
** char *
**
** @param		str			받은 명령어
** @param		envp		환경변수
*/

char	*quote_conversion(char *s, char**envp)
{
	int		i;
	int		j;
	int		quote;
	char	*needle;
	char	*temp;

	i = -1;
	quote = 0;
	while (s[++i])
	{
		if (f_q(s[i], &quote) && quote == -1)
			continue ;
		if (s[i] == '$' && !(!(s[i + 1]) || \
		s[i + 1] == ' ' || s[i + 1] == '$' || s[i + 1] == '\"'))
		{
			j = i + 1;
			while (!(!(s[j]) || s[j] == ' ' || s[j] == '$' || s[j] == '\"'))
				j++;
			needle = ft_strdup_path(&s[i + 1], j - i - 1);
			needle = find_path(needle, envp);
			temp = s;
			s = add_str(temp, needle, i, j);
		}
	}
	return (del_quote(s));
}

/*
** 받은 문자열(명령어)을 token으로 바꾸어서 t_minishell의 token에 할당해주는 함수
** void
**
** @param		minishell	minishell을 구성하는 구조체
							token의 정보를 저장하는 곳.
** @param		str			받은 명령어
** @param		envp		환경변수
*/

void	parse_input(t_minishell *minishell, char *str, char **envp)
{
	char	**temp2;

	temp2 = continue_quote(str);
	make_token(minishell, temp2, envp);
	free(temp2);
}
