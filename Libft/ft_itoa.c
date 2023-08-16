/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongmiki <dongmiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 15:47:14 by dongmiki          #+#    #+#             */
/*   Updated: 2022/12/27 15:35:43 by dongmiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	get_length(int nbr)
{
	int	length;

	length = 0;
	if (nbr == 0)
		return (length + 1);
	if (nbr < 0)
		length = 1;
	while (nbr != 0)
	{
		nbr = nbr / 10;
		length++;
	}
	return (length);
}

char	*ft_itoa(int n)
{
	int		length;
	long	temp;
	char	*res;

	length = get_length(n);
	res = (char *)malloc(sizeof(char) * (length + 1));
	if (res == NULL)
		return (0);
	res[length] = '\0';
	length--;
	temp = n;
	if (temp < 0)
	{
		res[0] = '-';
		temp = -temp;
	}
	if (temp == 0)
		res[0] = '0';
	while (temp > 0)
	{
		res[length] = '0' + (temp % 10);
		temp = temp / 10;
		length--;
	}
	return (res);
}
