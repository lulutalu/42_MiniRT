/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduboulo <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 14:54:21 by lduboulo          #+#    #+#             */
/*   Updated: 2022/10/26 17:29:52 by lduboulo         ###   ########.fr       */
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
	res.direction = make_unit_vector(res.direction);
	res.origin = main->cam.pos;
	return (res);
}

float	shadow_value(t_ray ray, t_vec3 l_pos)
{
	t_vec3	normal;
	t_vec3	hit_point;
	float	light;

	hit_point = vec_float_multi(ray.t, ray.direction);
	hit_point = vec_addition(ray.origin, hit_point);
	normal = make_unit_vector(hit_point);
	l_pos = make_unit_vector(l_pos);
	light = fmax(dot(normal, l_pos), 0.1f);
	return (light);
}

void	pixel_color(t_main *main, t_ray ray, int x, int y)
{
	t_vec3	rgb;
	float	l;
	int		i;

	i = 0;
	ray.closest_obj = -1;
	while (i < main->scn.n_obj)
	{
		check_intersection(main->scn.obj[i], i, &ray);
		i++;
	}
	if (ray.closest_obj > -1)
	{
		l = shadow_value(ray, new_vec(0.0f, 0.0f, -1.0f));
		rgb = vec_float_multi(l, main->scn.obj[ray.closest_obj].rgb);
		put_pixel_color(&main->mlx, x, y, rgb);
	}
	else
		put_pixel_color(&main->mlx, x, y, new_vec(0, 0, 0));
/*	float	t;
	float	d;
//	t_vec3	N;
//	t_vec3	hitPoint;
//	t_vec3	light;

	if (hit_plane(new_vec(0.0f, 0.0f, -100.0f), make_unit_vector(new_vec(0.0f, -1.0f, -1.0f)), ray))
	{
//		hitPoint = vec_addition(ray.origin, vec_float_multi(t, ray.direction));
//		N = make_unit_vector(hitPoint);
//		light = make_unit_vector(new_vec(10.0f, 0.0f, -5.0f));
		d = 0.5; //fmax(dot(N, light), 0.2f);
		put_pixel_color(&main->mlx, x, y, vec_float_multi(d, new_vec(0.5f, 0.5f, 0.0f)));
		t = hit_sphere(new_vec(0.0f, 0.0f, -5.0f), 1.0f, ray);
	}
	else if (t > 0.0f)
	{
//		hitPoint = vec_addition(ray.origin, vec_float_multi(t, ray.direction));
//		N = make_unit_vector(hitPoint);
//		light = make_unit_vector(new_vec(0.0f, -10.0f, -3.0f));
		d = 0.5f; //fmax(dot(N, light), 0.2f);
		put_pixel_color(&main->mlx, x, y, vec_float_multi(d, new_vec(0.0f, 0.0f, 1.0f)));
	}
	t = hit_sphere(new_vec(0.0f, -5.0f, 0.0f), 1.0f, ray);
	if (t > 0.0f)
	{
//		hitPoint = vec_addition(ray.origin, vec_float_multi(t, ray.direction));
//		N = make_unit_vector(hitPoint);
//		light = make_unit_vector(new_vec(10.0f, 0.0f, -5.0f));
		d = 0.5f; //fmax(dot(N, light), 0.2f);
		put_pixel_color(&main->mlx, x, y, vec_float_multi(d, new_vec(0.0f, 1.0f, 0.0f)));
	}*/
}

int	frame_loop(t_main *main)
{
	int	x;
	int	y;

	image_init(&main->mlx);
	printf("%f\n", main->cam.pos.z);
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
