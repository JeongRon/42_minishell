/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongmiki <dongmiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 19:22:17 by dongmiki          #+#    #+#             */
/*   Updated: 2023/01/02 19:30:01 by dongmiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	unsigned int	count;
	unsigned int	count2;
	unsigned int	result;

	count = ft_strlen(dest);
	count2 = ft_strlen(src);
	result = count + count2;
	if (count >= size)
		return (count2 + size);
	count2 = 0;
	while (src[count2] && count + 1 < size)
	{
		dest[count] = src[count2];
		count++;
		count2++;
	}
	dest[count] = '\0';
	return (result);
}
