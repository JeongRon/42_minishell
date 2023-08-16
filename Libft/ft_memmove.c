/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongmiki <dongmiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 18:57:30 by dongmiki          #+#    #+#             */
/*   Updated: 2022/12/20 20:10:48 by dongmiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char		*ndst;
	unsigned char		*nsrc;
	size_t				n;

	ndst = (unsigned char *)dst;
	nsrc = (unsigned char *)src;
	if (ndst == nsrc || len == 0)
		return (dst);
	if (dst < src)
	{
		n = -1;
		while (++n < len)
			ndst[n] = nsrc[n];
	}
	else
	{
		n = len;
		while (--n > 0)
			ndst[n] = nsrc[n];
		ndst[0] = nsrc[0];
	}
	return (dst);
}
