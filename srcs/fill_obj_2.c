/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_obj_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngda-sil <ngda-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 03:02:18 by ngda-sil          #+#    #+#             */
/*   Updated: 2022/11/02 20:21:20 by ngda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

int	valid_char_size(char *s)
{
	int	i;

	i = -1;
	while (s[++i])
		if (!ft_isdigit(s[i]) && (s[i] != '.'))
			return (1);
	return (0);
}

float	get_size(char *size, t_main *m)
{
	if (valid_char_size(size))
		exit_error("DIAM / HEIGHT : Invalid input\n", m);
	return (ft_atof(size));
}

void	fill_obj_sp(char **info, t_main *m, int i)
{
	if (check_size_tab(info, 4))
		exit_error("sp wrong nb of info\n", m);
	m->scn.obj[i].id = SPHERE;
	get_pos(info[1], m, i);
	m->scn.obj[i].diameter = get_size(info[2], m);
	get_rgb(info[3], m, i);
}

void	fill_obj_pl(char **info, t_main *m, int i)
{
	if (check_size_tab(info, 4))
		exit_error("pl wrong nb of info\n", m);
	m->scn.obj[i].id = PLANE;
	get_pos(info[1], m, i);
	get_vec(info[2], m, i);
	get_rgb(info[3], m, i);
}

void	fill_obj_cy(char **info, t_main *m, int i)
{
	if (check_size_tab(info, 6))
		exit_error("cy wrong nb of info\n", m);
	m->scn.obj[i].id = CYLINDER;
	get_pos(info[1], m, i);
	get_vec(info[2], m, i);
	m->scn.obj[i].diameter = get_size(info[3], m);
	m->scn.obj[i].height = get_size(info[4], m);
	get_rgb(info[5], m, i);
}
