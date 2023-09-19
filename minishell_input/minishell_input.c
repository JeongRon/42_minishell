/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_input.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongmiki <dongmiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 16:32:20 by dongmiki          #+#    #+#             */
/*   Updated: 2023/09/18 19:29:18 by dongmiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

char	*quote_conversion(char *s, char**envp, int i)
{
	int		j;
	int		quote;
	char	*needle;
	char	*temp;

	quote = 0;
	while (s[++i])
	{
		if (f_q(s[i], &quote) && quote == -1)
			continue ;
		if (s[i] == '$' && !(!(s[i + 1]) || \
		s[i + 1] == ' ' || s[i + 1] == '$' || s[i + 1] == '\"'))
		{
			j = i + 1;
			while (!(!(s[j]) || s[j] == ' ' || s[j] == '$' \
			|| s[j] == '\"' || s[j] == '\''))
				j++;
			needle = ft_strdup_path(&s[i + 1], j - i - 1);
			needle = find_path(needle, envp);
			temp = s;
			s = add_str(temp, needle, i, j);
		}
	}
	return (del_quote(s));
}

void	parse_input(t_minishell *minishell, char *str, char **envp)
{
	char	**temp2;

	temp2 = continue_quote(str);
	make_token(minishell, temp2, envp);
	free(temp2);
}
