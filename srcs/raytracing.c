/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngda-sil <ngda-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 14:54:21 by lduboulo          #+#    #+#             */
/*   Updated: 2022/11/10 20:09:35 by ngda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

t_ray	ray_generation(t_main *main, int x, int y)
{
	t_vec3	tmp;
	t_ray	res;
	float	u;
	float	v;

	u = (((float)x * 2.0f) / (float)main->mlx.x_res - 1.0f) * main->cam.h;
	v = (((float)y * -2.0f) / (float)main->mlx.y_res + 1.0f) * main->cam.w;
	res.direction = vec_float_multi(u, main->cam.right);
	tmp = vec_float_multi(v, main->cam.up);
	res.direction = vec_addition(tmp, res.direction);
	res.direction = vec_addition(res.direction, main->cam.forward);
	res.direction = normalize(res.direction);
	res.origin = main->cam.pos;
	return (res);
}

void	pixel_color(t_main *main, t_ray ray, int x, int y)
{
	t_vec3	rgb;
	t_vec3	rgb_l;
	t_vec3	light_pos;
	float	l;
	int		i;

	light_pos = find_in_tab(&main->scn, 'L')->pos;
	i = 0;
	ray.i_close = -1;
	while (i < main->scn.n_obj)
	{
		check_intersection(main->scn.obj[i], i, &ray);
		i++;
	}
	if (ray.i_close > -1)
	{
		l = shadow_value(ray, light_pos, main->scn);
		rgb_l = vec_float_multi(l, main->scn.obj[ray.i_close].rgb);
		rgb = vec_float_multi(find_in_tab(&main->scn, 'A')->light_r, find_in_tab(&main->scn, 'A')->rgb);
		rgb = vec_addition(rgb_l, rgb);
		color_max(&rgb);
		put_pixel_color(&main->mlx, x, y, rgb);
	}
	else
		put_pixel_color(&main->mlx, x, y, new_vec(0.0f, 0.0f, 0.0f));
}

int	frame_loop(t_main *main)
{
	int	x;
	int	y;

	image_init(&main->mlx);
	camera_update(main);
	y = 0;
	while (y < main->mlx.y_res)
	{
		x = 0;
		while (x < main->mlx.x_res)
		{
			pixel_color(main, ray_generation(main, x, y), x, y);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(main->mlx.ptr, main->mlx.window, \
			main->mlx.img.ptr, 0, 0);
	mlx_destroy_image(main->mlx.ptr, main->mlx.img.ptr);
	printf("Rendering Done\n");
	return (1);
}
