/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongmiki <dongmiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 21:07:35 by dongmiki          #+#    #+#             */
/*   Updated: 2023/02/17 18:41:35 by dongmiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned int	count;

	count = 0;
	if (n == 0)
		return (0);
	while (s1[count] && s2[count] && s1[count] == s2[count] && count < n)
		count++;
	if (count == n)
		return ((unsigned char)s1[count - 1] - (unsigned char)s2[count - 1]);
	return ((unsigned char)s1[count] - (unsigned char)s2[count]);
}
