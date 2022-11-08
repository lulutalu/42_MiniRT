/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngda-sil <ngda-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 14:54:21 by lduboulo          #+#    #+#             */
/*   Updated: 2022/11/08 19:20:36 by ngda-sil         ###   ########.fr       */
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

float	shadow_value(t_ray ray, t_vec3 l_pos, t_scn scn)
{
	t_ray	shadow;
	t_vec3	hit_point;
	t_vec3	normal;
	float	coeff;
	int		i;

	i = 0;
	normal = new_vec(0, 0, 0);
	hit_point = vec_addition(ray.origin, vec_float_multi(ray.t, ray.direction));
	shadow.origin = hit_point;
	shadow.direction = make_unit_vector(vec_minus(l_pos, shadow.origin));
	shadow.closest_obj = -1;
	while (i < scn.n_obj)
	{
		check_shadow_intersection(scn.obj[i], i, &shadow);
		i++;
	}
	if (shadow.closest_obj == -1)
	{
		if (scn.obj[ray.closest_obj].id == SPHERE)
			normal = make_unit_vector(vec_minus(hit_point, scn.obj[ray.closest_obj].pos));
		else if (scn.obj[ray.closest_obj].id == PLANE)
			normal = scn.obj[ray.closest_obj].vec;
		coeff = dot(normal, shadow.direction);
		if (coeff < 0.0f && scn.obj[ray.closest_obj].id == PLANE)
			coeff *= -1.0f;
		coeff *= find_in_tab(&scn, 'L')->light_r;
	}
	else
		coeff = find_in_tab(&scn, 'A')->light_r;
	if (coeff < find_in_tab(&scn, 'A')->light_r)
		coeff = find_in_tab(&scn, 'A')->light_r;
	return (coeff);
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
	ray.closest_obj = -1;
	while (i < main->scn.n_obj)
	{
		check_intersection(main->scn.obj[i], i, &ray);
		i++;
	}
	if (ray.closest_obj > -1)
	{
		l = shadow_value(ray, light_pos, main->scn);
		rgb_l = vec_float_multi(l, find_in_tab(&main->scn, 'A')->rgb);
		rgb = vec_multiplication(rgb_l, main->scn.obj[ray.closest_obj].rgb);
		put_pixel_color(&main->mlx, x, y, rgb);
	}
	else
		put_pixel_color(&main->mlx, x, y, new_vec(0, 0, 0));
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
