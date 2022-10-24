/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduboulo <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 14:54:21 by lduboulo          #+#    #+#             */
/*   Updated: 2022/10/21 23:22:53 by lduboulo         ###   ########.fr       */
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
		return ((-b - sqrtf(discri)) / (2.0f * a));
}

float	hit_plane(t_vec3 pos, t_vec3 dir, t_ray ray)
{
	float		denom;
	float		t;
	t_vec3	diff;

	t = 0;
	denom = dot(dir, ray.direction);
	if (fabs(denom) > 0.0001)
	{
		diff = make_unit_vector(vec_minus(pos, ray.origin));
		t = dot(diff, dir);
		t /= denom;
	}
	return (t);
}
