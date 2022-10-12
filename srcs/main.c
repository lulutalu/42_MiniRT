/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduboulo <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 14:54:21 by lduboulo          #+#    #+#             */
/*   Updated: 2022/10/12 20:25:32 by lduboulo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	draw_rectangle(t_data *img, int x_start, int y_start, int x_end, int y_end)
{
	int	x = x_start;
	int	y = y_start;

	while (x < x_end)
		my_mlx_pixel_put(img, x++, y, 0x00FFFFFF);
	while (y < y_end)
		my_mlx_pixel_put(img, x, y++, 0x00FFFFFF);
	while (x > x_start)
		my_mlx_pixel_put(img, x--, y, 0x00FFFFFF);
	while (y > y_start)
		my_mlx_pixel_put(img, x, y--, 0x00FFFFFF);
}

int	animation(t_mlx	*mlx)
{
	if (mlx->frame)
	{
		mlx->frame1.img = mlx_new_image(mlx->mlx, 1920, 1080);
		mlx->frame1.addr = mlx_get_data_addr(mlx->frame1.img, \
				&mlx->frame1.bits_per_pixel, &mlx->frame1.line_length, &mlx->frame1.endian);
		draw_rectangle(&mlx->frame1, mlx->x_start, mlx->y_start, mlx->x_end, mlx->y_end);
		mlx_put_image_to_window(mlx->mlx, mlx->window, mlx->frame1.img, 0, 0);
		mlx_destroy_image(mlx->mlx, mlx->frame2.img);
		mlx->frame = 0;
	}
	else
	{
		mlx->frame2.img = mlx_new_image(mlx->mlx, 1920, 1080);
		mlx->frame2.addr = mlx_get_data_addr(mlx->frame2.img, \
				&mlx->frame2.bits_per_pixel, &mlx->frame2.line_length, &mlx->frame2.endian);
		draw_rectangle(&mlx->frame2, mlx->x_start, mlx->y_start, mlx->x_end, mlx->y_end);
		mlx_put_image_to_window(mlx->mlx, mlx->window, mlx->frame2.img, 0, 0);
		mlx_destroy_image(mlx->mlx, mlx->frame1.img);
		mlx->frame = 1;
	}
	if (mlx->direction)
	{
		mlx->x_start += 1;
		mlx->x_end += 1;
		mlx->y_start += 1;
		mlx->y_end += 1;
		if (mlx->x_end > 1915 || mlx->y_end > 1070)
			mlx->direction = false;
	}
	else
	{
		mlx->x_start -= 1;
		mlx->x_end -= 1;
		mlx->y_start -= 1;
		mlx->y_end -= 1;
		if (mlx->x_start < 15 || mlx->y_start < 15)
			mlx->direction = true;
	}
	return (1);
}

int	main(void)
{
	t_mlx	mlx;

	mlx.mlx = mlx_init();
	mlx.window = mlx_new_window(mlx.mlx, 1920, 1080, "Hello world!");
	mlx.frame2.img = mlx_new_image(mlx.mlx, 1920, 1080);
	mlx.x_start = 100;
	mlx.y_start = 100;
	mlx.x_end = 600;
	mlx.y_end = 600;
	mlx.frame = 1;
	mlx.direction = true;
	//loop hook for the creation of the animation
	mlx_loop_hook(mlx.mlx, animation, &mlx);
	mlx_loop(mlx.mlx);
	return (1);
}
