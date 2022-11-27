/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngda-sil <ngda-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 19:19:45 by ngda-sil          #+#    #+#             */
/*   Updated: 2022/11/27 16:46:12 by ngda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

void	init_scn(t_scn *scn)
{
	scn->obj = NULL;
	scn->n_obj = 0;
	scn->a = 0;
	scn->c = 0;
	scn->l = 0;
}

void	init_obj(t_main *m)
{
	int	i;

	i = -1;
	m->scn.obj = ft_calloc(m->scn.n_obj + 1, sizeof(t_obj));
	while (++i < m->scn.n_obj)
	{
		m->scn.obj[i].id = -1;
		m->scn.obj[i].light_r = 0;
		m->scn.obj[i].rgb.x = 0;
		m->scn.obj[i].rgb.y = 0;
		m->scn.obj[i].rgb.z = 0;
		m->scn.obj[i].pos.x = 0;
		m->scn.obj[i].pos.y = 0;
		m->scn.obj[i].pos.z = 0;
		m->scn.obj[i].vec.x = 0;
		m->scn.obj[i].vec.y = 0;
		m->scn.obj[i].vec.z = 0;
		m->scn.obj[i].fov = 0;
		m->scn.obj[i].diameter = 0;
		m->scn.obj[i].height = 0;
	}
}
