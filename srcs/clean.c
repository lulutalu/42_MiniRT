/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngda-sil <ngda-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 19:05:59 by ngda-sil          #+#    #+#             */
/*   Updated: 2022/11/27 16:46:09 by ngda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

void	exit_error(char *str)
{
	printf("\033[31m%s", str);
	exit(EXIT_FAILURE);
}

void	exit_error_free(char *str, t_obj *ptr)
{
	if (ptr)
		free(ptr);
	exit_error(str);
}

void	perror_exit(char *s)
{
	perror(s);
	exit(EXIT_FAILURE);
}
