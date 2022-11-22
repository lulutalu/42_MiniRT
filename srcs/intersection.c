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
	float	a;
	float	b;
	float	c;
	t_inter	res;

	oc = vec_minus(ray.origin, center);
	a = dot(ray.direction, ray.direction);
	b = 2.0f * dot(oc, ray.direction);
	c = dot(oc, oc) - (radius * radius);
	res.discri = b * b - (4.0f * a * c);
	if (res.discri < 0.0f)
		return (-1.0f);
	res.t1 = (-b - sqrtf(res.discri)) / (2.0f * a);
	res.t2 = (-b + sqrtf(res.discri)) / (2.0f * a);
	return (fminf(res.t1, res.t2));
}

float	hit_plane(t_vec3 pos, t_vec3 dir, t_ray ray)
{
	float	denom;
	float	t;
	t_vec3	diff;

	t = 0;
	denom = dot(dir, ray.direction);
	if (fabs(denom) > 0.0001f)
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
	float	a;
	float	b;
	float	c;
	t_inter	res;
	t_vec3	hp;

	obj.vec = make_unit_vector(obj.vec);
	new_ray.origin = ray.origin;
	new_ray.direction = cross(ray.direction, obj.vec);
	oc = vec_minus(ray.origin, obj.pos);
	a = dot(new_ray.direction, new_ray.direction);
	b = 2.0f * dot(new_ray.direction, cross(oc, obj.vec));
	c = dot(cross(oc, obj.vec), cross(oc, obj.vec)) - powf(0.5f * obj.diameter, 2);
	res.discri = b * b - (4.0f * a * c);
	if (res.discri < 0.0f)
		return (-1.0f);
	res.t1 = (-b - sqrtf(res.discri)) / (2.0f * a);
	res.t2 = (-b + sqrtf(res.discri)) / (2.0f * a);
	res.t = fminf(res.t1, res.t2);
	hp = vec_addition(ray.origin, vec_float_multi(res.t, ray.direction));
	if (hp.y < obj.pos.y || hp.y > obj.pos.y + obj.height)
	{
		if (res.t == res.t1)
			res.t = res.t2;
		else
			res.t = res.t1;
		hp = vec_addition(ray.origin, vec_float_multi(res.t, ray.direction));
		if (hp.y < obj.pos.y || hp.y > obj.pos.y + obj.height)
			return (-1.0f);
	}
	return (res.t);
}

/*float	hit_cylinder(t_obj obj, t_ray ray)
{
	t_vec3	oc;
	float	a;
	float	b;
	float	c;
	t_inter	res;
	t_vec3	hp;

	oc = vec_minus(ray.origin, obj.pos);
	a = dot(ray.direction, ray.direction) - powf(dot(ray.direction, obj.vec), 2);
	c = dot(oc, oc) - powf(dot(oc, obj.vec), 2) - powf(0.5f * obj.diameter, 2);
	b = 2.0f * (dot(ray.direction, oc) - (dot(ray.direction, obj.vec) * dot(oc, obj.vec)));
	res.discri = b * b - (4.0f * a * c);
	res.t1 = (-b - sqrtf(res.discri)) / (2.0f * a);
	res.t2 = (-b + sqrtf(res.discri)) / (2.0f * a);
	res.t = fminf(res.t1, res.t2);
	hp = vec_addition(ray.origin, vec_float_multi(res.t, ray.direction));
	if (hp.y < obj.pos.y || hp.y > obj.pos.y + obj.height)
		return (-1.0f);
	return (res.t);
}*/

/*float	hit_cylinder(t_vec3 pos, t_vec3 dir, float radius, t_ray ray)
{
	float	t;
	t_vec3	p_inters;
	t_vec3	dist;
	float	d2;

	t = hit_plane(pos, dir, ray);
	if (t == -1.0f)
		return (-1.0f);
	p_inters = vec_addition(ray.origin, vec_float_multi(t, ray.direction));
	dist = vec_minus(pos, p_inters);
	d2 = dot(dist, dist);
	t = sqrtf(d2);
	if (t <= radius)
	{
		
		return (t);
	}
	return (-1.0f);
}*/

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
		if (ray->closest_obj == -1)
		{
			ray->closest_obj = i;
			ray->t = t_obj;
		}
		else if (t_obj < ray->t)
		{
			ray->closest_obj = i;
			ray->t = t_obj;
		}
	}
}

void	check_shadow_intersection(t_obj obj, int i, t_ray *ray)
{
	float	t_obj;

	t_obj = -1.0f;
	if (obj.id == SPHERE)
		t_obj = hit_sphere(obj.pos, (obj.diameter * 0.5f), *ray);
	else if (obj.id == PLANE)
		t_obj = hit_plane(obj.pos, obj.vec, *ray);
	else if (obj.id == CYLINDER)
		t_obj = hit_cylinder(obj, *ray);
	if (t_obj > 0.01f)
	{
		if (ray->closest_obj == -1)
		{
			ray->closest_obj = i;
			ray->t = t_obj;
		}
		else if (t_obj < ray->t)
		{
			ray->closest_obj = i;
			ray->t = t_obj;
		}
	}
}
