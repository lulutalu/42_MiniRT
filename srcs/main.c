/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngda-sil <ngda-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 14:54:21 by lduboulo          #+#    #+#             */
/*   Updated: 2022/10/21 23:11:42 by ngda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

int	main(int ac, char **av)
{
	t_main	m;
	int		i;

	parse(ac, av, &m);
	/*rt_init(&main.mlx);
	mlx_hook(main.mlx.window, 2, (1L << 13), keyhook, &main.mlx);
//	mlx_loop_hook(main.mlx.ptr, movement, &main);
	frame_loop(&main);
	mlx_loop(main.mlx.ptr);*/
	for (i = 0; i < m.scn.n_obj; i++)
		printf("obj[%i]: id:%d l_r:%f r:%d g:%d b:%d pos.x:%f pos.y:%f vec.z:%fvec.x:%f vec.y:%f vec.z:%f fov:%f diam:%f height:%f\n", i, m.scn.obj[i].id , m.scn.obj[i].light_r, m.scn.obj[i].rgb.r, m.scn.obj[i].rgb.g, m.scn.obj[i].rgb.b, m.scn.obj[i].pos.x, m.scn.obj[i].pos.y, m.scn.obj[i].pos.z, m.scn.obj[i].vec.x, m.scn.obj[i].vec.y, m.scn.obj[i].vec.z, m.scn.obj[i].fov, m.scn.obj[i].diameter, m.scn.obj[i].height);
	return (0);
}
