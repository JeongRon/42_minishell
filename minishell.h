/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongmiki <dongmiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 17:35:51 by dongmiki          #+#    #+#             */
/*   Updated: 2023/09/05 18:19:21 by dongmiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <unistd.h>
# include <termios.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <signal.h>
# include <dirent.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "./Libft/libft.h"

# define BUFFER_SIZE 5000

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
	int		token_num;
	int		exit_code;
	t_token	*token;
	pid_t	*pid;
	char	**temp_path;
}	t_minishell;

t_minishell	*g_minishell;

int		main(int ac, char *av[], char **envp);
int		check_null(char **str, int count);
int		f_q(char str, int *quote);
int		excute_token(char **envp);
int		filepath_search(char *cmd, char *filepath);
char	*del_quote(char *str);
char	*find_path(char *str, char **envp);
char	*quote_conversion(char *str, char**envp);
char	**continue_quote(char *str);
char	**ft_split_quote(char const *str, char c, int quote);
pid_t	ft_fork(void);
void	error(char *str);
void	make_token(t_minishell *minishell, char **str_split_pipe, char **envp);
void	parse_input(t_minishell *minishell, char *str, char **envp);
void	setting_signal(int sig_int, int sig_quit);
void	child_signal(int sig);
void	*ft_malloc(size_t size);
void	multi_pipe_exec(char **env, int index);
void	ft_error(char *str);
void	ft_pipe(int *fd);
void	ft_execve(char *filepath, char **av, char **envp);
void	ft_dup2(int old_fd, int new_fd);
void	set_redirection(char **str);
void	child_process(int i, char **env, int fd[], int pre_pipe[]);
#endif