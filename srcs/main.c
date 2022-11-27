/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngda-sil <ngda-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 14:54:21 by lduboulo          #+#    #+#             */
/*   Updated: 2022/11/27 17:22:48 by ngda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

int	main(int ac, char **av)
{
	t_main	m;

	parse(ac, av, &m);
	rt_init(&m.mlx);
	camera_init(&m.mlx, &m.cam, &m.scn);
	mlx_hook(m.mlx.window, 2, (1L << 13), keyhook, &m);
	mlx_hook(m.mlx.window, 17, 0, close_window, &m);
	frame_loop(&m);
	mlx_loop(m.mlx.ptr);
	return (0);
}
