/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduboulo <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 14:54:21 by lduboulo          #+#    #+#             */
/*   Updated: 2022/10/14 22:48:42 by lduboulo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

int	movement(t_main *main)
{
	main->mlx.img.img = mlx_new_image(main->mlx.mlx, 1920, 1080);
	main->mlx.img.addr = mlx_get_data_addr(main->mlx.img.img, \
			&main->mlx.img.bits_per_pixel, &main->mlx.img.line_length, \
			&main->mlx.img.endian);
	main->obj->pos.y = 0;
	while (main->obj->pos.y < 1079)
	{
		main->obj->pos.x = 0;
		while (main->obj->pos.x < 1919)
		{
			main->obj->rgb.red = (main->obj->pos.x / 1920) * 255;
			main->obj->rgb.green = (main->obj->pos.y / 1080) * 255;
			main->obj->rgb.blue = 51;
			my_mlx_pixel_put(&main->mlx.img, main->obj->pos.x, main->obj->pos.y,
				create_trgb(0, main->obj->rgb.red, main->obj->rgb.green, \
				main->obj->rgb.blue));
			main->obj->pos.x += 1;
		}
		main->obj->pos.y += 1;
	}
	mlx_put_image_to_window(main->mlx.mlx, main->mlx.window, \
			main->mlx.img.img, 0, 0);
	mlx_destroy_image(main->mlx.mlx, main->mlx.img.img);
	return (1);
}

int	main(void)
{
	t_main	main;

	rt_init(&main.mlx);
	mlx_hook(main.mlx.window, 2, (1L << 13), keyhook, &main.mlx);
	movement(&main);
	mlx_loop(main.mlx.mlx);
	return (1);
}
