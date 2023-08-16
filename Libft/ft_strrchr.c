/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongmiki <dongmiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 21:02:34 by dongmiki          #+#    #+#             */
/*   Updated: 2022/11/18 21:05:37 by dongmiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	char	*ret;
	size_t	i;

	ret = (char *)str;
	i = ft_strlen(str);
	while (i > 0)
	{
		if (ret[i] == (char)c)
			return (ret + i);
		i--;
	}
	if (ret[i] == (char)c)
		return (ret);
	return (0);
}
