/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduboulo <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 14:54:21 by lduboulo          #+#    #+#             */
/*   Updated: 2022/10/16 22:06:49 by lduboulo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

int	main(void)
{
	t_main	main;

	rt_init(&main.mlx);
	mlx_hook(main.mlx.window, 2, (1L << 13), keyhook, &main.mlx);
//	mlx_loop_hook(main.mlx.ptr, movement, &main);
	frame_loop(&main);
	mlx_loop(main.mlx.ptr);
	return (1);
}
