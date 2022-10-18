/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduboulo <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 14:54:21 by lduboulo          #+#    #+#             */
/*   Updated: 2022/10/16 22:06:49 by lduboulo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

t_ray	rayGeneration(t_main *main, int x, int y)
{
	t_ray	res;
	float	u;
	float	v;

	t_vec3	lower_left;											//Temporary Setup
	t_vec3	horizontal;											////////////////
	t_vec3	vertical;												////////////////
	t_vec3	origin;													////////////////
																					////////////////
	lower_left = new_vec(-4.0, -4.0, -2.0);	////////////////
	horizontal = new_vec(8.0, 0.0, 0.0);		////////////////
	vertical = new_vec(0.0, 8.0, 0.0);			///////////////////
	origin = new_vec(0.0, 0.0, 3.0);				//////////////////////

	u = (float)x / main->mlx.x_res;
	v = (float)y / main->mlx.y_res;
	res.origin = origin;
	res.direction = vec_addition(lower_left, vec_minus(vec_addition(vec_float_multi(u, horizontal), vec_float_multi(v, vertical)), origin));
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
	t_vec3	N;
	t_vec3	hitPoint;
	t_vec3	light;

	t = hit_sphere(new_vec(0, 0, 0), 1.0, ray);
	if (t < 0.0f)
		putPixelColor(&main->mlx, x, y, new_vec(0.0f, 0.0f, 0.0f));
	else
	{
		hitPoint = vec_addition(ray.origin, vec_float_multi(t, ray.direction));
		N = make_unit_vector(hitPoint);
		light = make_unit_vector(new_vec(5.0f, 5.0f, 1.5f));
		d = fmax(dot(N, light), 0.0f);
		putPixelColor(&main->mlx, x, y, vec_float_multi(d, new_vec(0.0f, 0.0f, 1)));
	}
}

int	frame_loop(t_main *main)
{
	int	x;
	int	y;

	image_init(&main->mlx);
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
	return (1);
}
