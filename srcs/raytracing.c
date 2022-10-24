/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduboulo <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 14:54:21 by lduboulo          #+#    #+#             */
/*   Updated: 2022/10/21 23:22:53 by lduboulo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

t_ray	ray_generation(t_main *main, int x, int y)
{
	t_ray	res;
	float	u;
	float	v;
	float	h;
	float	w;

	t_vec3	up;
	t_vec3	right;
	t_vec3	forward;
	t_vec3	origin;

	t_vec3	tmp;

	forward = make_unit_vector(vec_minus(main->cam.pos, main->cam.dir));
	right = make_unit_vector(cross(new_vec(1.0f, 0.0f, 0.0f), forward));
	up = cross(forward, right);
	origin = main->cam.pos;

	h = tan(120);
	w = h * main->mlx.aspect_ratio;

	u = (((float)x * 2.0f) / (float)main->mlx.x_res - 1.0f) * w;
	v = (((float)y * -2.0f) / (float)main->mlx.y_res + 1.0f) * h;

	res.direction = vec_float_multi(u, right);
	tmp = vec_float_multi(v, up);
	res.direction = vec_addition(tmp, res.direction);
	res.direction = vec_addition(res.direction, forward);
	res.direction = make_unit_vector(res.direction);

	res.origin = origin;

	if (forward.x < 0 || forward.y < 0 || forward.z < 0)
		res.direction = new_vec(0, 0, 0);

	return (res);
}

void	pixel_color(t_main *main, t_ray ray, int x, int y)
{
	float	t;
	float	d;
	t_vec3	N;
	t_vec3	hitPoint;
	t_vec3	light;

	t = hit_plane(new_vec(0.0f, 0.0f, -10.0f), make_unit_vector(new_vec(0.0f, 0.0f, 1.0f)), ray);
	if (t < 0.0f)
		put_pixel_color(&main->mlx, x, y, new_vec(0.0f, 0.0f, 0.0f));
	else
	{
		hitPoint = vec_addition(ray.origin, vec_float_multi(t, ray.direction));
		N = make_unit_vector(hitPoint);
		light = make_unit_vector(new_vec(0.0f, 4.0f, 0.0f));
		d = fmax(dot(N, light), 0.2f);
		put_pixel_color(&main->mlx, x, y, vec_float_multi(d, new_vec(0.0f, 0.0f, 1.0f)));
	}

	t = hit_plane(new_vec(0.0f, 20.0f, 0.0f), make_unit_vector(new_vec(0.0f, -1.0f, 0.0f)), ray);
	if (t < 0.0f)
		put_pixel_color(&main->mlx, x, y, new_vec(0.0f, 0.0f, 0.0f));
	else
	{
		hitPoint = vec_addition(ray.origin, vec_float_multi(t, ray.direction));
		N = make_unit_vector(hitPoint);
		light = make_unit_vector(new_vec(0.0f, 4.0f, 0.0f));
		d = fmax(dot(N, light), 0.2f);
		put_pixel_color(&main->mlx, x, y, vec_float_multi(d, new_vec(0.0f, 0.0f, 1.0f)));
	}
}

int	frame_loop(t_main *main)
{
	int	x;
	int	y;

	image_init(&main->mlx);
	printf("%f\n", main->cam.dir.x);
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
