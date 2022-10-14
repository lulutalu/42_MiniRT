/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduboulo <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 14:54:21 by lduboulo          #+#    #+#             */
/*   Updated: 2022/10/14 17:33:25 by lduboulo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

/*void	circle_pixel_put(t_data *img, int x_center, int y_center, int x, int y)
{
	my_mlx_pixel_put(img, x_center+x, y_center+y, 0x00FFFFFF);
	my_mlx_pixel_put(img, x_center-x, y_center+y, 0x00FFFFFF);
	my_mlx_pixel_put(img, x_center+x, y_center-y, 0x00FFFFFF);
	my_mlx_pixel_put(img, x_center-x, y_center-y, 0x00FFFFFF);
	my_mlx_pixel_put(img, x_center+y, y_center+x, 0x00FFFFFF);
	my_mlx_pixel_put(img, x_center-y, y_center+x, 0x00FFFFFF);
	my_mlx_pixel_put(img, x_center+y, y_center-x, 0x00FFFFFF);
	my_mlx_pixel_put(img, x_center-y, y_center-x, 0x00FFFFFF);
}

void	draw_circle(t_mlx *mlx, int x_center, int y_center, int radius)
{
	int	x;
	int	y;
	int	d;

	x = 0;
	y = radius;
	d = 3 - (2 * radius);
	mlx->img.img = mlx_new_image(mlx->mlx, 1920, 1080);
	mlx->img.addr = mlx_get_data_addr(mlx->img.img, &mlx->img.bits_per_pixel, \
			&mlx->img.line_length, &mlx->img.endian);
	circle_pixel_put(&mlx->img, x_center, y_center, x, y);
	while (y >= x)
	{
		x++;
		if (d > 0)
		{
			y--;
			d = d + 4 * (x - y) + 10;
		}
		else
			d = d + 4 * x + 6;
		circle_pixel_put(&mlx->img, x_center, y_center, x, y);
	}
	mlx_put_image_to_window(mlx->mlx, mlx->window, mlx->img.img, 0, 0);
	mlx_destroy_image(mlx->mlx, mlx->img.img);
}*/

int		keyhook(int keycode, t_mlx *mlx)
{
	if (keycode == 124)
		mlx->x_start += 10;
	if (keycode == 123)
		mlx->x_start -= 10;
	if (keycode == 126)
		mlx->y_start -= 10;
	if (keycode == 125)
		mlx->y_start += 10;
	if (keycode == 53)
	{
		mlx_destroy_window(mlx->mlx, mlx->window);
		exit(EXIT_SUCCESS);
	}
	printf("KeyCode : %d\n", keycode);
	return (1);
}

int		close_window(int keycode, t_mlx *mlx)
{
	(void)keycode;
	(void)mlx;
	exit(0);
}

int		resize_window(int keycode, t_mlx *mlx)
{
	(void)keycode;
	(void)mlx;
	printf("Hello there\n");
	return (1);
}

/*int		movement(t_mlx *mlx)
{
	draw_circle(mlx, mlx->x_start, mlx->y_start, 100);
	return (1);
}*/

int	main(void)
{
	t_mlx	mlx;

	mlx.mlx = mlx_init();
	mlx.window = mlx_new_window(mlx.mlx, 1920, 1080, "Hello world!");
	mlx.x_start = 1000;
	mlx.y_start = 500;
	//loop hook for the creation of the animation
	mlx_hook(mlx.window, 2, (1L << 13), keyhook, &mlx);
	mlx_hook(mlx.window, 17, 0L, close_window, &mlx);
	mlx_hook(mlx.window, 25, 0L, resize_window, &mlx);
	mlx_do_key_autorepeaton(mlx.mlx);
//	mlx_loop_hook(mlx.mlx, movement, &mlx);
	mlx_loop(mlx.mlx);
	return (1);
}
