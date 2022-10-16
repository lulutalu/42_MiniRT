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

float	hit_sphere(t_point center, float radius, t_ray ray)
{
	t_point	oc;
	float	a;
	float	b;
	float	c;
	float	discri;

	oc = vec_minus(ray.vec2, center);
	a = dot(ray.vec2, ray.vec2);
	b = 2.0 * dot(oc, ray.vec2);
	c = dot(oc, oc) - (radius * radius);
	discri = (b * b) - (4 * a * c);
	if (discri < 0)
		return (-1.0);
	else
		return ((b - sqrtf(discri)) / (2.0 * a));
}

t_point	color(t_ray ray)
{
	t_point	unit_direction;
	t_point	vec_res;
	t_point	N;
	float	t;

	t = hit_sphere(new_vec(0, 0, -1), 0.5, ray);
	if (t > 0.0)
	{
		N = make_unit_vector(vec_minus(vec_addition(ray.vec1, vec_float_multi(t, ray.vec2)), new_vec(0, 0, -1)));
		return (vec_float_multi(0.5, new_vec(N.x + 1, N.y + 1, N.z + 1)));
	}
	unit_direction = make_unit_vector(ray.vec2);
	t = 0.5 * (unit_direction.y + 1.0);
	vec_res = vec_float_multi(1.0 - t, new_vec(1.0, 1.0, 1.0));
	vec_res = vec_addition(vec_res, vec_float_multi(t, new_vec(0.5, 0.7, 1.0)));
	return (vec_res);
}

int	movement(t_main *main)
{
	t_point	lower_left;
	t_point	horizontal;
	t_point	vertical;
	t_point	origin;

	lower_left.x = -2.0;
	lower_left.y = -1.0;
	lower_left.z = -1.0;

	horizontal.x = 4.0;
	horizontal.y = 0.0;
	horizontal.z = 0.0;

	vertical.x = 0.0;
	vertical.y = 2.0;
	vertical.z = 0.0;

	origin.x = 0.0;
	origin.y = 0.0;
	origin.z = 0.0;

	float	u;
	float	v;

	t_ray	ray;

	t_point	vec;

	main->mlx.img.ptr = mlx_new_image(main->mlx.ptr, 1920, 1080);
	main->mlx.img.addr = mlx_get_data_addr(main->mlx.img.ptr, \
			&main->mlx.img.bits_per_pixel, &main->mlx.img.line_length, \
			&main->mlx.img.endian);

	main->obj.pos.y = 0;
	while (main->obj.pos.y < 1079)
	{
		main->obj.pos.x = 0;
		while (main->obj.pos.x < 1919)
		{
			u = main->obj.pos.x / 1920;
			v = main->obj.pos.y / 1080;

			ray.vec1 = origin;
			ray.vec2 = vec_addition(lower_left, vec_minus(vec_addition(vec_float_multi(u, horizontal), vec_float_multi(v, vertical)), origin));

			vec = color(ray);

			my_mlx_pixel_put(&main->mlx.img, main->obj.pos.x, main->obj.pos.y,
				create_trgb(0, vec.x * 255, vec.y * 255, vec.z * 255));
			main->obj.pos.x += 1;
		}
		main->obj.pos.y += 1;
	}

	mlx_put_image_to_window(main->mlx.ptr, main->mlx.window, \
			main->mlx.img.ptr, 0, 0);
	mlx_destroy_image(main->mlx.ptr, main->mlx.img.ptr);

	return (1);
}

int	main(void)
{
	t_main	main;

	rt_init(&main.mlx);
	mlx_hook(main.mlx.window, 2, (1L << 13), keyhook, &main.mlx);
	movement(&main);
	mlx_loop(main.mlx.ptr);
	return (1);
}
