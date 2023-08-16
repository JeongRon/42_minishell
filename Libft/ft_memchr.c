/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongmiki <dongmiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 21:20:48 by dongmiki          #+#    #+#             */
/*   Updated: 2022/12/20 20:11:29 by dongmiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*nsrc;
	size_t			i;

	nsrc = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		if (nsrc[i] == (unsigned char)c)
			return (&nsrc[i]);
		i++;
	}
	return (0);
}
