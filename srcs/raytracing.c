/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduboulo <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 14:54:21 by lduboulo          #+#    #+#             */
/*   Updated: 2022/10/21 22:35:54 by lduboulo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

t_ray	rayGeneration(t_main *main, int x, int y)
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
	right = make_unit_vector(cross(new_vec(0.0f, 1.0f, 0.0f), forward));
	up = cross(forward, right);
	origin = main->cam.pos;

	h = tan(25);
	w = h * main->mlx.aspect_ratio;

//	x -= main->mlx.x_res / 2;
//	y -= main->mlx.y_res / 2;

//	printf("x : %d\ny : %d\n", x, y);

	u = (((float)x * 2.0f) / (float)main->mlx.x_res - 1.0f) * w;
	v = (((float)y * -2.0f) / (float)main->mlx.y_res + 1.0f) * h;

//	printf("U : %f\nV : %f\n", u, v);

	res.direction = vec_float_multi(u, right);
	tmp = vec_float_multi(v, up);
	res.direction = vec_addition(tmp, res.direction);
	res.direction = vec_addition(res.direction, forward);
	res.direction = make_unit_vector(res.direction);

//	u = (float)x / (float)main->mlx.x_res;
//	v = (float)y / (float)main->mlx.y_res;
	res.origin = origin;
//	res.direction = make_unit_vector(vec_addition(vec_addition(forward, vec_float_multi(v, right)), vec_float_multi(u, up)));


//	printf("Ray Direction.x : %f\nRay Direction.y : %f\nRay Direction.z : %f\n", 
//			res.direction.x, res.direction.y, res.direction.z);

	return (res);
}

float	hit_sphere(t_vec3 center, float radius, t_ray ray)
{
	t_vec3	oc;
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

void	pixelColor(t_main *main, t_ray ray, int x, int y)
{
	float	t;
	float	d;
//	t_vec3	N;
//	t_vec3	hitPoint;
//	t_vec3	light;

	t = hit_sphere(new_vec(0.0f, 0.0f, -2.0f), 0.5f, ray);
	if (t < 0.0f)
		putPixelColor(&main->mlx, x, y, new_vec(0.0f, 0.0f, 0.0f));
	else
	{
//		printf("%d\n", i++);
//		printf("Ray Direction.x : %f\nRay Direction.y : %f\nRay Direction.z : %f\n", ray.direction.x, ray.direction.y, ray.direction.z);
//		hitPoint = vec_addition(ray.origin, vec_float_multi(t, ray.direction));
//		N = make_unit_vector(hitPoint);
//		light = make_unit_vector(new_vec(0.0f, 5.0f, 0.0f));
		d = 1; //fmax(dot(N, light), 0.0f);
		putPixelColor(&main->mlx, x, y, vec_float_multi(d, new_vec(0.0f, 0.0f, 1.0f)));
	}
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
			pixelColor(main, rayGeneration(main, x, y), x, y);
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
