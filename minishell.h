/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongmiki <dongmiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 17:35:51 by dongmiki          #+#    #+#             */
/*   Updated: 2023/09/11 17:36:53 by dongmiki         ###   ########.fr       */
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
# define FAIL 0
# define SUCCESS 1

typedef struct s_env_var
{
	char	**path;
	char	*home;
	char	**env;
	char	**exp;
	int		env_cnt;
	int		exp_cnt;
	int		status;
}	t_env_var;

typedef struct s_token
{
	char	**cmd;
	char	***redirection;
}	t_token;

typedef struct s_minishell
{
	char		*path;
	char		**history;
	int			token_num;
	int			exit_code;
	t_token		*token;
	pid_t		*pid;
	t_env_var	env_var;
}	t_minishell;

t_minishell	*g_minishell;

int		main(int ac, char *av[], char **envp);
int		check_null(char **str, int count);
int		f_q(char str, int *quote);
int		excute_token(char **envp);
int		filepath_search(char **cmd2, char *cmd, char *filepath);
char	*del_quote(char *str);
char	*find_path(char *str, char **envp);
char	*quote_conversion(char *str, char**envp);
char	**continue_quote(char *str);
char	**ft_split_quote(char const *str, char c, int quote);
pid_t	ft_fork(void);
void	error(char *str);
void	free_token(void);
void	wait_child(void);
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
void	switch_exit_code(void);
// built_in Folder
// set_env_var.c
int		set_env_var(t_env_var *env_var, char **envp);
int		check_home(char *envp);
// sort_exp.c
void	sort_exp(t_env_var *env_var);
// check_cmd.c
void	check_cmd(char **cmd, t_env_var *env_var);
// env.c
int		start_env(char **cmd, t_env_var *env_var);
void	print_env(t_env_var *env_var);
// pwd.c
int		print_pwd(void);
char	*get_pwd_value(void);
// export.c
int		start_export(char **cmd, t_env_var *env_var);
void	print_exp(t_env_var *env_var);
// unset.c
int		start_unset(char **cmd, t_env_var *env_var);
// echo.c
int		start_echo(char **cmd);
// exit.c
int		start_exit(char **cmd);
// cd.c
int		start_cd(char **cmd, t_env_var *env_var);
// utils Folder
// utils_add.c
void	add_exp(char *cmd, t_env_var *env_var);
void	add_env(char *cmd, t_env_var *env_var);
// utils_del.c
void	del_env(char *cmd, t_env_var *env_var);
void	del_exp(char *cmd, t_env_var *env_var);
// utils_check.c
int		check_num(char *str);
int		check_duplicate(char **arr, char *cmd, int flag);
// utils_malloc.c
char	*key_strdup(char *str);
char	*ft_exp_strdup(char *src);
char	*ftj_strdup(const char *src);
// utils_lib.c
size_t	ftj_strlen(const char *str);
int		ftj_strcmp(const char *s1, const char *s2);
int		ftj_strncmp(const char *s1, const char *s2, size_t n);
size_t	ftj_strlcpy(char *dst, const char *src, size_t dstsize);
char	*ftj_strjoin(char const *s1, char const *s2);
// utils_mini.c
void	ft_free(char **str);
int		ft_two_strlen(char **str);
// split.c
char	**ftj_split(char const *s, char c);
#endif