/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngda-sil <ngda-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 14:54:21 by lduboulo          #+#    #+#             */
/*   Updated: 2022/11/02 16:18:09 by ngda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

void	scene_init(t_scn *scn)
{
	scn->obj = ft_calloc(4 + 1, sizeof(t_obj));
	scn->n_obj = 4;

	scn->obj[0].id = PLANE;
	scn->obj[0].rgb = new_vec(0.5f, 0.5f, 0.5f);
	scn->obj[0].pos = new_vec(0.0f, 0.0f, -30.0f);
	scn->obj[0].vec = new_vec(0.0f, 0.0f, 1.0f);

	scn->obj[1].id = SPHERE;
	scn->obj[1].rgb = new_vec(0.0f, 1.0f, 0.0f);
	scn->obj[1].pos = new_vec(5.0f, 0.0f, -10.0f);
	scn->obj[1].diameter = 3.0f;

	scn->obj[2].id = SPHERE;
	scn->obj[2].rgb = new_vec(0.0f, 0.0f, 1.0f);
	scn->obj[2].pos = new_vec(-5.0f, 0.0f, -10.0f);
	scn->obj[2].diameter = 3.0f;

	scn->obj[3].id = PLANE;
	scn->obj[3].rgb = new_vec(0.60f, 0.60f, 0.60f);
	scn->obj[3].pos = new_vec(0.0f, -5.0f, 0.0f);
	scn->obj[3].vec = new_vec(0.0f, -1.0f, 0.0f);
}

int	main(int ac, char **av)
{
	t_main	main;
//	int		i;

	rt_init(&main.mlx);
	parse(ac, av, &main);
	camera_init(&main.mlx, &main.cam);
	scene_init(&main.scn);
	mlx_hook(main.mlx.window, 2, (1L << 13), keyhook, &main);
	frame_loop(&main);
	mlx_loop(main.mlx.ptr);
	/*for (i = 0; i < m.scn.n_obj; i++)
		printf("obj[%i]: id:%d l_r:%f r:%d g:%d b:%d pos.x:%f pos.y:%f vec.z:%fvec.x:%f vec.y:%f vec.z:%f fov:%f diam:%f height:%f\n", i, m.scn.obj[i].id , m.scn.obj[i].light_r, m.scn.obj[i].rgb.r, m.scn.obj[i].rgb.g, m.scn.obj[i].rgb.b, m.scn.obj[i].pos.x, m.scn.obj[i].pos.y, m.scn.obj[i].pos.z, m.scn.obj[i].vec.x, m.scn.obj[i].vec.y, m.scn.obj[i].vec.z, m.scn.obj[i].fov, m.scn.obj[i].diameter, m.scn.obj[i].height);*/
	return (0);
}
