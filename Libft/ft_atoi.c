/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongmiki <dongmiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 18:09:57 by dongmiki          #+#    #+#             */
/*   Updated: 2023/02/25 19:24:50 by dongmiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str, int *check)
{
	int				sign_count;
	unsigned int	value;

	sign_count = 1;
	value = 0;
	if (*str == '\0')
		(*check) = 0;
	while (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign_count *= -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		value = value * 10;
		value = value + *str - 48;
		if (value < 0 || value > 2147483647)
			if (!(value == 2147483648 && sign_count == -1))
				(*check) = 0;
		str++;
	}
	if (*str != '\0')
		(*check) = 0;
	return (sign_count * value);
}
