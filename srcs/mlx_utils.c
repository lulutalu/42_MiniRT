/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduboulo <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 17:36:14 by lduboulo          #+#    #+#             */
/*   Updated: 2022/10/14 18:09:56 by lduboulo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int		keyhook(int keycode, t_mlx *mlx)
{
	if (keycode == RIGHT_ARROW)
		mlx->x_start += 10;
	if (keycode == LEFT_ARROW)
		mlx->x_start -= 10;
	if (keycode == UP_ARROW)
		mlx->y_start -= 10;
	if (keycode == DOWN_ARROW)
		mlx->y_start += 10;
	if (keycode == ESC)
	{
		mlx_destroy_window(mlx->mlx, mlx->window);
		exit(EXIT_SUCCESS);
	}
	return (1);
}

int		close_window(int keycode, t_mlx *mlx)
{
	(void)keycode;
	(void)mlx;
	exit(0);
}

void	rt_init(t_mlx *mlx)
{
	mlx->mlx = mlx_init();
	printf("Address in sub-function : %p\n", mlx->mlx);
	mlx->window = mlx_new_window(mlx->mlx, 1920, 1080, "Hello world!");
	mlx->x_start = 1000;
	mlx->y_start = 500;
	mlx_hook(mlx->window, 17, 0L, close_window, &mlx);
	mlx_do_key_autorepeaton(mlx->mlx);
}
