/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongmiki <dongmiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 18:31:07 by dongmiki          #+#    #+#             */
/*   Updated: 2022/12/27 17:14:50 by dongmiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	size_t			i;
	unsigned char	*temp;
	unsigned char	val;

	temp = (unsigned char *)b;
	i = 0;
	val = (unsigned char)c;
	while (i < len)
	{
		temp[i] = val;
		i++;
	}
	return (temp);
}
