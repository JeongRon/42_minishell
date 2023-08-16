/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongmiki <dongmiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 19:20:22 by dongmiki          #+#    #+#             */
/*   Updated: 2022/12/27 17:28:02 by dongmiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	count;

	count = 0;
	if (size != 0 && dest != NULL)
	{
		while (count < size - 1 && src[count])
		{
			dest[count] = src[count];
			count++;
		}
		dest[count] = '\0';
		count++;
	}
	count = 0;
	while (src[count])
	{
		count++;
	}
	return (count);
}
