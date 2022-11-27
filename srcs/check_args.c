/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngda-sil <ngda-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 19:02:59 by ngda-sil          #+#    #+#             */
/*   Updated: 2022/11/27 16:46:06 by ngda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

int	check_type(char *name, char *type )
{
	int	n_len;
	int	t_len;
	int	start;
	int	i;

	n_len = ft_strlen(name);
	t_len = ft_strlen(type);
	start = n_len - t_len;
	i = -1;
	while (name[start] == type[++i] && name[start])
		start++;
	if (i == t_len)
		return (0);
	return (1);
}

void	check_args(int ac, char **av)
{
	if (ac != 2)
		exit_error("Wrong number of args\n");
	if (check_type(av[1], ".rt") == 1)
		exit_error("Wrong file type\n");
}
