/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keymaps.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngda-sil <ngda-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 17:36:14 by lduboulo          #+#    #+#             */
/*   Updated: 2022/11/17 14:25:26 by lduboulo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

int	keyhook(int keycode, t_main *main)
{
	if (keycode == ESC)
	{
		mlx_destroy_window(main->mlx.ptr, main->mlx.window);
		exit(EXIT_SUCCESS);
	}
	else if (keycode == RIGHT_ARROW)
		main->cam.pos.x += 0.5f;
	else if (keycode == LEFT_ARROW)
		main->cam.pos.x -= 0.5f;
	else if (keycode == UP_ARROW)
		main->cam.pos.z -= 0.2f;
	else if (keycode == DOWN_ARROW)
		main->cam.pos.z += 0.2f;
	else if (keycode == Q)
		main->cam.pos.y -= 0.5f;
	else if (keycode == E)
		main->cam.pos.y += 0.5f;
	keyhook_more(keycode, main);
	frame_loop(main);
	return (1);
}

int	keyhook_more(int keycode, t_main *main)
{
	if (keycode == A)
		main->cam.dir.x -= 0.1f;
	else if (keycode == D)
		main->cam.dir.x += 0.1f;
	else if (keycode == L)
		main->cam.dir.y += 0.1f;
	else if (keycode == K)
		main->cam.dir.y -= 0.1f;
	else if (keycode == J)
		main->cam.dir.z += 0.1f;
	else if (keycode == H)
		main->cam.dir.z -= 0.1f;
	return (1);
}
