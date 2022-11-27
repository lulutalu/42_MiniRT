/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngda-sil <ngda-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 14:54:21 by lduboulo          #+#    #+#             */
/*   Updated: 2022/11/10 20:09:35 by ngda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

float	shadow_value(t_ray ray, t_vec3 l_pos, t_scn scn)
{
	t_ray	shadow;
	t_vec3	hit_point;
	float	coeff;
	int		i;

	i = 0;
	coeff = 0.1f;
	hit_point = vec_addition(ray.origin, vec_float_multi(ray.t, ray.direction));
	shadow.origin = hit_point;
	shadow.direction = normalize(vec_minus(l_pos, shadow.origin));
	shadow.i_close = -1;
	while (i < scn.n_obj)
	{
		check_shadow_intersection(scn.obj[i], i, &shadow, distance(l_pos, hit_point));
		i++;
	}
	if (shadow.i_close == -1)
	{
		if (scn.obj[ray.i_close].id == PLANE)
			coeff = fabsf(dot(ray_normal(ray, scn, hit_point), shadow.direction));
		else
			coeff = dot(ray_normal(ray, scn, hit_point), shadow.direction);
		coeff *= find_in_tab(&scn, 'L')->light_r;
	}
	if (coeff < find_in_tab(&scn, 'A')->light_r)
		coeff = find_in_tab(&scn, 'A')->light_r;
	return (coeff);
}

t_vec3	ray_normal(t_ray ray, t_scn scn, t_vec3 hit_point)
{
	t_vec3	normal;

	normal = new_vec(0.0f, 0.0f, 0.0f);
	if (scn.obj[ray.i_close].id == SPHERE)
		normal = normalize(vec_minus(hit_point, scn.obj[ray.i_close].pos));
	else if (scn.obj[ray.i_close].id == PLANE)
		normal = scn.obj[ray.i_close].vec;
	else if (scn.obj[ray.i_close].id == CYLINDER)
		normal = cylinder_normal(&scn.obj[ray.i_close], hit_point);
	return (normal);
}

t_vec3	cylinder_normal(t_obj *obj, t_vec3 hit_point)
{
	t_vec3		pbis;
	t_vec3		cpoint;
	float		ax;
	float		ay;

	obj->vec = normalize(obj->vec);
	if (is_vec_equal(obj->vec, new_vec(0.0f, 1.0f, 0.0f)))
	{
		cpoint = new_vec(obj->pos.x, hit_point.y, obj->pos.z);
		return (normalize(vec_minus(hit_point, cpoint)));
	}
	ax = atanf(obj->vec.z / obj->vec.x) * 180.0f / M_PI;
	if (obj->vec.x < 0.0f)
		ax += 180.0f;
	ay = acosf(obj->vec.y / 1.0f) * 180.0f / M_PI;
	pbis = vec_minus(hit_point, obj->pos);
	pbis = rotate(pbis, 0.0f, ax, ay);
	pbis = vec_addition(pbis, obj->pos);
	cpoint = new_vec(obj->pos.x, obj->pos.y, obj->pos.z);
	cpoint.y = pbis.y;
	cpoint = vec_minus(cpoint, obj->pos);
	cpoint = rev_rotate(cpoint, 0.0f, -ax, -ay);
	cpoint = vec_addition(cpoint, obj->pos);
	return (normalize(vec_minus(hit_point, cpoint)));
}
