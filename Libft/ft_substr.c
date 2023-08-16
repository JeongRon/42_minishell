/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongmiki <dongmiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 14:45:29 by dongmiki          #+#    #+#             */
/*   Updated: 2022/12/29 22:26:59 by dongmiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	i;

	i = len;
	if (s == NULL)
		return (NULL);
	if (ft_strlen(s) < start)
	{
		substr = (char *)malloc(sizeof(char) * (1));
		substr[0] = '\0';
		return (substr);
	}
	if (ft_strlen(s) < len && ft_strlen(s) > start)
		i = ft_strlen(s) - start;
	substr = (char *)malloc(sizeof(char) * (i + 1));
	if (!(substr))
		return (NULL);
	i = 0;
	while (s[start + i] != '\0' && i < len)
	{
		substr[i] = s[start + i];
		i++;
	}
	substr[i] = '\0';
	return (substr);
}
