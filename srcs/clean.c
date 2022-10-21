/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngda-sil <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 19:05:59 by ngda-sil          #+#    #+#             */
/*   Updated: 2022/10/21 19:31:00 by ngda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

void	exit_error(char *str, t_main *m)
{
	(void)m;
	printf("\033[31m%s", str);
	exit(EXIT_FAILURE);
}

void	perror_exit(char *s)
{
	perror(s);
	exit(EXIT_FAILURE);
}
