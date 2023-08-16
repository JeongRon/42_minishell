/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongmiki <dongmiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 21:40:03 by dongmiki          #+#    #+#             */
/*   Updated: 2023/01/02 19:29:07 by dongmiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *src)
{
	int		i;
	char	*add;

	i = ft_strlen(src);
	add = (char *)malloc(sizeof(char) * (i + 1));
	if (!add)
		return (0);
	i = 0;
	while (src[i])
	{
		add[i] = src[i];
		i++;
	}
	add[i] = '\0';
	return (add);
}
