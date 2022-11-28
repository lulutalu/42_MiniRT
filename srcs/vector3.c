/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduboulo <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 16:31:13 by lduboulo          #+#    #+#             */
/*   Updated: 2022/11/28 13:53:26 by ngda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

bool	is_vec_equal(t_vec3 lhs, t_vec3 rhs)
{
	bool	res;

	res = true;
	if (!(lhs.x <= rhs.x + EPSILON) || !(lhs.x >= rhs.x - EPSILON))
		res = false;
	if (!(lhs.y <= rhs.y + EPSILON) || !(lhs.y >= rhs.y - EPSILON))
		res = false;
	if (!(lhs.z <= rhs.z + EPSILON) || !(lhs.z >= rhs.z - EPSILON))
		res = false;
	return (res);
}

float	distance(t_vec3 lhs, t_vec3 rhs)
{
	float	dist;

	dist = powf(rhs.x - lhs.x, 2) + powf(rhs.y - lhs.y, 2) + \
		powf(rhs.z - lhs.z, 2);
	dist = sqrtf(dist);
	return (dist);
}

void	color_max(t_vec3 *rgb)
{
	if (rgb->x > 1.0f)
		rgb->x = 1.0f;
	if (rgb->y > 1.0f)
		rgb->y = 1.0f;
	if (rgb->z > 1.0f)
		rgb->z = 1.0f;
}
