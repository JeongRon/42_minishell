/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongmiki <dongmiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 18:09:21 by jeongrol          #+#    #+#             */
/*   Updated: 2023/09/11 21:11:38 by dongmiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// long long 범위 넘으면 리턴 1, 범위 안이면 리턴 0
static int	is_out_of_range(char *cmd, int ch_flag)
{
	int			ch_len;
	long long	res;

	ch_len = 0;
	res = 0;
	if (ch_flag)
		ch_len = 1;
	if ((int)ftj_strlen(cmd) >= ch_len + 20)
		return (1);
	else if ((int)ftj_strlen(cmd) == ch_len + 19)
	{
		if (ch_flag == 0)
			res = ftj_strcmp(cmd, "9223372036854775807");
		else if (ch_flag == 1)
			res = ftj_strcmp(&cmd[1], "9223372036854775807");
		else if (ch_flag == 2)
			res = ftj_strcmp(&cmd[1], "9223372036854775808");
		if (res > 0)
			return (1);
	}
	return (0);
}

static long long	ftj_atoi(const char *str)
{
	int				sign;
	long long		value;
	int				i;

	sign = 1;
	value = 0;
	i = 0;
	if (str[0] == '+')
		i++;
	else if (str[0] == '-')
	{
		i++;
		sign = -1;
	}
	while ('0' <= str[i] && str[i] <= '9')
	{
		value = value * 10;
		value = value + str[i] - 48;
		i++;
	}
	return (sign * value);
}

// 숫자가 long long 범위 밖일 시 256 리턴, 아니면 exit 인자에 맞게 리턴
static int	get_exit_status(char *cmd)
{
	int			status;
	int			ch_flag;
	long long	num;

	status = 0;
	ch_flag = 0;
	if (cmd[0] == '+')
		ch_flag = 1;
	else if (cmd[0] == '-')
		ch_flag = 2;
	if (is_out_of_range(cmd, ch_flag) == 1)
		status = 256;
	else
	{
		num = ftj_atoi(cmd);
		status = num % 256;
		if (ch_flag == 2)
		{
			status = status + 256;
			if (status == 256)
				status = 0;
		}
	}
	return (status);
}

static int	print_exit_code(int status, char **cmd)
{
	if (g_minishell->token_num == 0)
		printf("exit\n");
	if (status == 1)
	{
		ft_putstr_fd("bash: exit: too many arguments\n", 2);
		return (256);
	}
	else if (status == 255)
	{
		ft_putstr_fd("bash: exit: ", 2);
		ft_putstr_fd(cmd[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
	}
	else if (status == -1)
	{
		status = get_exit_status(cmd[1]);
		if (status == 256)
		{
			ft_putstr_fd("bash: exit: ", 2);
			ft_putstr_fd(cmd[1], 2);
			ft_putstr_fd(": numeric argument required\n", 2);
			status = 255;
		}
	}
	return (status);
}

int	start_exit(char **cmd)
{
	int	cnt;

	infile_make(cmd);
	cnt = ft_two_strlen(cmd);
	if (cnt == 1)
		return (print_exit_code(0, cmd));
	else
	{
		if (check_num(cmd[1]) == SUCCESS)
		{
			if (get_exit_status(cmd[1]) == 256)
				return (print_exit_code(-1, cmd));
			if (cnt == 2)
				return (print_exit_code(-1, cmd));
			else
				return (print_exit_code(1, cmd));
		}
		else
			return (print_exit_code(255, cmd));
	}
}
