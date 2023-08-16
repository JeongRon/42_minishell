/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongmiki <dongmiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 19:26:24 by dongmiki          #+#    #+#             */
/*   Updated: 2022/12/20 20:56:27 by dongmiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	*nstr;

	i = 0;
	nstr = (char *)s;
	c = (unsigned char)c;
	while (nstr[i])
	{
		if (nstr[i] == c)
			return (nstr + i);
		i++;
	}
	if (nstr[i] == c)
		return (nstr + i);
	return (0);
}
