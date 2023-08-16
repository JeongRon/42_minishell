/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongmiki <dongmiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 20:52:10 by dongmiki          #+#    #+#             */
/*   Updated: 2023/01/02 19:35:51 by dongmiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	void	calculate(long num, int fd)
{
	char	s[10];
	char	i;
	int		j;

	i = '0';
	j = 0;
	while (j <= 9)
	{
		s[j] = i;
		i++;
		j++;
	}
	if (num >= 10)
		calculate(num / 10, fd);
	write(fd, &s[num % 10], 1);
}

void	ft_putnbr_fd(int n, int fd)
{
	long	num;

	if (fd < 0)
		return ;
	num = n;
	if (n < 0)
	{
		write(fd, "-", 1);
		num = -num;
	}
	calculate(num, fd);
}
