/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngda-sil <ngda-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 17:36:14 by lduboulo          #+#    #+#             */
/*   Updated: 2022/11/17 14:25:26 by lduboulo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *) dst = color;
}

int	keyhook(int keycode, t_main *main)
{
	if (keycode == RIGHT_ARROW)
	{
		main->cam.dir.y += 0.4f;
		frame_loop(main);
	}
	if (keycode == LEFT_ARROW)
	{
		main->cam.dir.y -= 0.4f;
		frame_loop(main);
	}
	if (keycode == UP_ARROW)
	{
		main->cam.pos.z -= 0.2f;
		frame_loop(main);
	}
	if (keycode == DOWN_ARROW)
	{
		main->cam.pos.z += 0.2f;
		frame_loop(main);
	}
	if (keycode == ESC)
	{
		mlx_destroy_window(main->mlx.ptr, main->mlx.window);
		exit(EXIT_SUCCESS);
	}
	return (1);
}

void	image_init(t_mlx *mlx)
{
	mlx->img.ptr = mlx_new_image(mlx->ptr, mlx->x_res, mlx->y_res);
	mlx->img.addr = mlx_get_data_addr(mlx->img.ptr, &mlx->img.bits_per_pixel, \
			&mlx->img.line_length, &mlx->img.endian);
}

int	close_window(int keycode, t_mlx *mlx)
{
	(void)keycode;
	(void)mlx;
	exit(0);
}

void	rt_init(t_mlx *mlx)
{
	mlx->ptr = mlx_init();
	mlx->aspect_ratio = 16.0f / 9.0f;
	mlx->x_res = 1500;
	mlx->y_res = mlx->x_res / (int)roundf(mlx->aspect_ratio);
	mlx->window = mlx_new_window(mlx->ptr, mlx->x_res, mlx->y_res, "Mini RT");
	mlx_hook(mlx->window, 17, 0L, close_window, &mlx);
	mlx_do_key_autorepeaton(mlx->ptr);
}
