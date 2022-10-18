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

	oc = vec_minus(ray.origin, center);
	a = dot(ray.direction, ray.direction);
	b = 2.0f * dot(oc, ray.direction);
	c = dot(oc, oc) - (radius * radius);
	discri = b * b - (4 * a * c);
	if (discri < 0.0f)
		return (-1.0f);
	else
		return ((-b - sqrtf(discri)) / (2.0f * a));
}

t_point	color(t_ray ray)
{
	float	t;
	float	d;
	t_point	N;
	t_point	hitPoint;
	t_point	light;

	t = hit_sphere(new_vec(0, 0, 0), 0.5, ray);
	if (t < 0.0f)
		return (new_vec(0, 0, 0));
	hitPoint = vec_addition(ray.origin, vec_float_multi(t, ray.direction));
	N = make_unit_vector(hitPoint);
	light = make_unit_vector(new_vec(-1, -1, -1));
	d = fmax(dot(N, vec_float_multi(-1.0f, light)), 0.0f);
	return (vec_float_multi(d, new_vec(0.1f, 0.7f, 1)));
}

int	movement(t_main *main)
{
	t_point	lower_left;
	t_point	horizontal;
	t_point	vertical;
	t_point	origin;

	lower_left = new_vec(-2.0, -1.0, -1.0);
	horizontal = new_vec(4.0, 0.0, 0.0);
	vertical = new_vec(0.0, 2.0, 0.0);
	origin = new_vec(0.0, 0.0, 2.0);

	float	u;
	float	v;

	t_ray	ray;

	t_point	vec;

	main->mlx.img.ptr = mlx_new_image(main->mlx.ptr, main->mlx.x_res, main->mlx.y_res);
	main->mlx.img.addr = mlx_get_data_addr(main->mlx.img.ptr, \
			&main->mlx.img.bits_per_pixel, &main->mlx.img.line_length, \
			&main->mlx.img.endian);

	main->obj.pos.y = 0;
	while (main->obj.pos.y < main->mlx.y_res)
	{
		main->obj.pos.x = 0;
		while (main->obj.pos.x < main->mlx.x_res)
		{
			u = main->obj.pos.x / main->mlx.x_res;
			v = main->obj.pos.y / main->mlx.y_res;

			ray.origin = origin;
			ray.direction = vec_addition(lower_left, vec_minus(vec_addition(vec_float_multi(u, horizontal), vec_float_multi(v, vertical)), origin));

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
