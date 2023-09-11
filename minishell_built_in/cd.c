/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongmiki <dongmiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 14:44:05 by jeongrol          #+#    #+#             */
/*   Updated: 2023/09/11 21:18:02 by dongmiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_home(t_env_var *env_var)
{
	char	*value;
	int		i;
	int		index;
	int		x;

	value = NULL;
	i = -1;
	index = -1;
	x = 4;
	while (1)
	{
		if (check_home(env_var->env[++i]) == SUCCESS)
		{
			if (ft_strlen(env_var->env[i]) == 5)
				return (NULL);
			value = malloc(sizeof(char) * (ft_strlen(env_var->env[i]) - 4));
			if (!value)
				perror("MALLOC");
			while (env_var->env[i][++x])
				value[++index] = env_var->env[i][x];
			value[index + 1] = '\0';
			break ;
		}
	}
	return (value);
}

static char	*get_pwd_line(int flag)
{
	char	*line;
	char	*value;

	value = get_pwd_value();
	line = NULL;
	if (flag == 0)
		line = ft_strjoin("OLDPWD=", value);
	else if (flag == 1)
		line = ft_strjoin("PWD=", value);
	if (!line)
		perror("MALLOC");
	return (line);
}

static int	change_dir_msg(char *path, t_env_var *env_var)
{
	char	*pwd;
	char	*old_pwd;

	old_pwd = get_pwd_line(0);
	pwd = NULL;
	if (chdir(path) != 0)
	{
		ft_putstr_fd("bash: cd: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		free(old_pwd);
		return (1);
	}
	pwd = get_pwd_line(1);
	del_env("PWD", env_var);
	del_env("OLDPWD", env_var);
	del_exp("PWD", env_var);
	del_exp("OLDPWD", env_var);
	add_env(pwd, env_var);
	add_env(old_pwd, env_var);
	add_exp(pwd, env_var);
	add_exp(old_pwd, env_var);
	free(pwd);
	free(old_pwd);
	return (0);
}

static int	change_dir(char *path, t_env_var *env_var)
{
	int		status;
	char	*tmp_path;

	status = 0;
	tmp_path = NULL;
	if (path[0] == '$')
	{
		tmp_path = get_home(env_var);
		if (!tmp_path)
			return (status);
		status = change_dir_msg(tmp_path, env_var);
	}
	else
		status = change_dir_msg(path, env_var);
	free(tmp_path);
	return (status);
}

int	start_cd(char **cmd, t_env_var *env_var)
{
	int	cnt;
	int	status;
	int	home_flag;

	infile_make(cmd);
	cnt = ft_two_strlen(cmd);
	status = 1;
	home_flag = check_duplicate(env_var->env, "HOME", 1);
	if (cnt == 1 && home_flag == 0)
		ft_putstr_fd("bash: cd: HOME not set\n", 2);
	else if (cnt == 1 && home_flag == 1)
		status = change_dir("$HOME", env_var);
	else
	{
		if (ftj_strcmp(cmd[1], "~") == 0 && home_flag == 0)
			status = change_dir(env_var->home, env_var);
		else if (ftj_strcmp(cmd[1], "~") == 0 && home_flag == 1)
			status = change_dir("$HOME", env_var);
		else
			status = change_dir(cmd[1], env_var);
	}
	return (status);
}
