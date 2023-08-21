/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongmiki <dongmiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 17:35:51 by dongmiki          #+#    #+#             */
/*   Updated: 2023/08/21 22:45:27 by dongmiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H


# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <unistd.h>
# include <stdlib.h>
# include <signal.h>
# include <dirent.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "./Libft/libft.h"

typedef struct s_redirection
{
	char	**cmd;
	char	***redirection;
}	t_redirection;

//배열로 만들어서 파이프별로 구성
typedef struct s_token
{
	char	**cmd;
	char	***redirection;
}	t_token;

typedef struct s_minishell
{
	char	*path;
	char	**history;
	///exit를 좀 더 편하게 하기 위해서?main에 넣어두기
	t_token	*token;
	int		token_num;
}	t_minishell;

int		main(int ac, char *av[], char **envp);
int		check_null(char **str, int count);
int		f_q(char str, int *quote);
char	*del_quote(char *str);
char	*find_path(char *str, char **envp);
char	*quote_conversion(char *str, char**envp);
char	**continue_quote(char *str);
char	**ft_split_quote(char const *str, char c, int quote);
void	error(char *str);
void	make_token(t_minishell *minishell, char **str_split_pipe, char **envp);
void	parse_input(t_minishell *minishell, char *str, char **envp);
void	*ft_malloc(size_t size);
#endif