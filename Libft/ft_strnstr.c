/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongmiki <dongmiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 21:27:42 by dongmiki          #+#    #+#             */
/*   Updated: 2023/01/02 19:38:05 by dongmiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str, const char *to_find, size_t len)
{
	size_t	count;
	size_t	count2;
	char	*temp;

	temp = (char *)str;
	count = 0;
	if (to_find[0] == '\0')
		return ((char *)str);
	count2 = ft_strlen(to_find);
	if (len == 0)
		return (0);
	while (temp[count] && count + count2 <= len)
	{
		if (ft_strncmp(&temp[count], (char *)to_find, count2) == 0)
			return (&temp[count]);
		count++;
	}
	return (0);
}
