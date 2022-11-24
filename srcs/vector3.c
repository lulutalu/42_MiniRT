/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduboulo <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 16:31:13 by lduboulo          #+#    #+#             */
/*   Updated: 2022/10/25 16:36:09 by lduboulo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

bool	is_vec_equal(t_vec3 lhs, t_vec3 rhs)
{
	bool	res;

	res = true;
	if (lhs.x != rhs.x)
		res = false;
	if (lhs.y != rhs.y)
		res = false;
	if (lhs.z != rhs.z)
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
