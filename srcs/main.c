/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduboulo <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 14:54:21 by lduboulo          #+#    #+#             */
/*   Updated: 2022/10/26 17:29:52 by lduboulo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

void	scene_init(t_scn *scn)
{
	scn->obj = ft_calloc(4 + 1, sizeof(t_obj));
	scn->n_obj = 4;

	scn->obj[0].id = PLANE;
	scn->obj[0].rgb = new_vec(1.0f, 0.0f, 0.0f);
	scn->obj[0].pos = new_vec(0.0f, 0.0f, -20.0f);
	scn->obj[0].vec = new_vec(0.0f, 0.0f, 1.0f);

	scn->obj[1].id = SPHERE;
	scn->obj[1].rgb = new_vec(0.0f, 1.0f, 0.0f);
	scn->obj[1].pos = new_vec(2.0f, 0.0f, -10.0f);
	scn->obj[1].diameter = 2.0f;

	scn->obj[2].id = SPHERE;
	scn->obj[2].rgb = new_vec(0.0f, 0.0f, 1.0f);
	scn->obj[2].pos = new_vec(-2.0f, 0.0f, -10.0f);
	scn->obj[2].diameter = 2.0f;

	scn->obj[0].id = PLANE;
	scn->obj[0].rgb = new_vec(1.0f, 1.0f, 0.0f);
	scn->obj[0].pos = new_vec(0.0f, -20.0f, 0.0f);
	scn->obj[0].vec = new_vec(0.0f, -1.0f, 0.0f);
}

int	main(void)
{
	t_main	main;

	rt_init(&main.mlx);
	camera_init(&main.mlx, &main.cam);
	scene_init(&main.scn);
	mlx_hook(main.mlx.window, 2, (1L << 13), keyhook, &main);
	frame_loop(&main);
	mlx_loop(main.mlx.ptr);
	return (1);
}
