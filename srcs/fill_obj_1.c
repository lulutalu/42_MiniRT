/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_obj_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngda-sil <ngda-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 21:24:36 by ngda-sil          #+#    #+#             */
/*   Updated: 2022/11/27 16:46:09 by ngda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

void	fill_obj_a(char **info, t_main *m, int i)
{
	if (check_size_tab(info, 3))
		exit_error_free("A wrong nb of info\n", m->scn.obj);
	if (m->scn.a)
		exit_error_free("A already appeared in file\n", m->scn.obj);
	m->scn.obj[i].id = 'A';
	get_l_r(info[1], m, i);
	get_rgb(info[2], m, i);
	m->scn.a++;
}

void	fill_obj_c(char **info, t_main *m, int i)
{
	if (check_size_tab(info, 4))
		exit_error_free("C wrong nb of info\n", m->scn.obj);
	if (m->scn.c)
		exit_error_free("C already appeared in file\n", m->scn.obj);
	m->scn.obj[i].id = 'C';
	get_pos(info[1], m, i);
	get_vec(info[2], m, i);
	get_fov(info[3], m, i);
	m->scn.c++;
}

void	fill_obj_l(char **info, t_main *m, int i)
{
	if (check_size_tab(info, 3))
		exit_error_free("L wrong nb of info\n", m->scn.obj);
	if (m->scn.l)
		exit_error_free("L already appeared in file\n", m->scn.obj);
	m->scn.obj[i].id = 'L';
	get_pos(info[1], m, i);
	get_l_r(info[2], m, i);
	m->scn.l++;
}
