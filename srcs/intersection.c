/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngda-sil <ngda-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 14:54:21 by lduboulo          #+#    #+#             */
/*   Updated: 2022/11/10 20:09:34 by ngda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

float	hit_sphere(t_vec3 center, float radius, t_ray ray)
{
	t_vec3	oc;
	t_poly	poly;
	t_inter	res;

	oc = vec_minus(ray.origin, center);
	poly.a = dot(ray.direction, ray.direction);
	poly.b = 2.0f * dot(oc, ray.direction);
	poly.c = dot(oc, oc) - (radius * radius);
	res.discri = poly.b * poly.b - (4.0f * poly.a * poly.c);
	if (res.discri < 0.0f)
		return (-1.0f);
	res.t1 = (-poly.b - sqrtf(res.discri)) / (2.0f * poly.a);
	if (res.t1 > 0.0f)
		return (fabsf(res.t1));
	return (res.t1);
}

float	hit_plane(t_vec3 pos, t_vec3 dir, t_ray ray)
{
	float	denom;
	float	t;
	t_vec3	diff;

	t = 0;
	denom = dot(dir, ray.direction);
	if (fabs(denom) > 0.0000001f)
	{
		diff = vec_minus(pos, ray.origin);
		t = dot(diff, dir);
		t = t / denom;
		return (t);
	}
	return (-1.0f);
}

float	hit_cylinder(t_obj obj, t_ray ray)
{
	t_ray	new_ray;
	t_vec3	oc;
	t_poly	poly;
	t_inter	res;

	obj.vec = normalize(obj.vec);
	new_ray.origin = ray.origin;
	new_ray.direction = cross(ray.direction, obj.vec);
	oc = vec_minus(ray.origin, obj.pos);
	poly.a = dot(new_ray.direction, new_ray.direction);
	poly.b = 2.0f * dot(new_ray.direction, cross(oc, obj.vec));
	poly.c = dot(cross(oc, obj.vec), cross(oc, obj.vec))
		- powf(0.5f * obj.diameter, 2);
	res.discri = poly.b * poly.b - (4.0f * poly.a * poly.c);
	if (res.discri < 0.0f)
		return (-1.0f);
	res.t1 = (-poly.b - sqrtf(res.discri)) / (2.0f * poly.a);
	res.t2 = (-poly.b + sqrtf(res.discri)) / (2.0f * poly.a);
	res.t = fminf(res.t1, res.t2);
	hit_wich_cylinder(ray, &res, obj);
	return (res.t);
}

void	check_intersection(t_obj obj, int i, t_ray *ray)
{
	float	t_obj;

	t_obj = -1.0f;
	if (obj.id == SPHERE)
		t_obj = hit_sphere(obj.pos, (obj.diameter * 0.5f), *ray);
	else if (obj.id == PLANE)
		t_obj = hit_plane(obj.pos, obj.vec, *ray);
	else if (obj.id == CYLINDER)
		t_obj = hit_cylinder(obj, *ray);
	if (t_obj > 0.0f)
	{
		if (ray->i_close == -1)
		{
			ray->i_close = i;
			ray->t = t_obj;
		}
		else if (t_obj < ray->t)
		{
			ray->i_close = i;
			ray->t = t_obj;
		}
	}
}

void	check_shadow_intersection(t_obj obj, int i, t_ray *ray, float t_max)
{
	float	t_obj;

	t_obj = -1.0f;
	if (obj.id == SPHERE)
		t_obj = hit_sphere(obj.pos, (obj.diameter * 0.5f), *ray);
	else if (obj.id == PLANE)
		t_obj = hit_plane(obj.pos, obj.vec, *ray);
	else if (obj.id == CYLINDER)
		t_obj = hit_cylinder(obj, *ray);
	if (t_obj > 0.1f && t_obj < t_max + EPSILON)
	{
		if (ray->i_close == -1)
		{
			ray->i_close = i;
			ray->t = t_obj;
		}
		else if (t_obj < ray->t)
		{
			ray->i_close = i;
			ray->t = t_obj;
		}
	}
}
