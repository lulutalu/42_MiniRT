/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngda-sil <ngda-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/17 18:07:14 by lduboulo          #+#    #+#             */
/*   Updated: 2022/11/02 21:15:19 by ngda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/utils.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	int	idx;

	if (s1 == NULL || s2 == NULL)
		return (1);
	idx = 0;
	if (n == 0)
		return (0);
	while (n > 0 && s1[idx] != '\0' && s2[idx] != '\0')
	{
		if (s1[idx] != s2[idx])
			return ((unsigned char)s1[idx] - (unsigned char)s2[idx]);
		idx++;
		n--;
	}
	if ((s1[idx] == '\0' || s2[idx] == '\0') && n > 0)
		return ((unsigned char)s1[idx] - (unsigned char)s2[idx]);
	return (0);
}
