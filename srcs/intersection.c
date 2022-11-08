/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngda-sil <ngda-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 14:54:21 by lduboulo          #+#    #+#             */
/*   Updated: 2022/11/08 22:47:18 by ngda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

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
		return (fminf((-b - sqrtf(discri)) / (2.0f * a), (-b + sqrtf(discri)) / (2.0f * a)));
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

float	hit_cylinder(t_vec3 pos, t_vec3 dir, float radius, t_ray ray)
{
	float	t;
	t_vec3	p_inters;
	t_vec3	dist;
	float	d2;

	t = hit_plane(pos, dir, ray);
	if (t == -1.0f)
		return (-1.0f);
	p_inters = vec_addition(dir, vec_float_multi(t, ray.direction));
	dist = vec_minus(pos, p_inters);
	d2 = dot(dist, dist);
	t = sqrtf(d2);
	if (t <= radius)
		return (t);
	//printf("des fois ca hit pas\n");
	return (-1.0f);
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
		t_obj = hit_cylinder(obj.pos, obj.vec, (obj.diameter * 0.5f), *ray);
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
