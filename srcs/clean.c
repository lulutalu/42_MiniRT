/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngda-sil <ngda-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 19:05:59 by ngda-sil          #+#    #+#             */
/*   Updated: 2022/11/25 21:38:23 by ngda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

void	exit_error_free(char *str, char **ptr, t_main *m)
{
	ft_tab_free((**void)ptr);
	exit_error(str, m);
}

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
