/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduboulo <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 22:55:48 by lduboulo          #+#    #+#             */
/*   Updated: 2022/10/16 19:48:49 by lduboulo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

float	vec_length(t_vec3 vec)
{
	float	res;

	res = sqrtf((vec.x * vec.x) + (vec.y * vec.y) + (vec.z * vec.z));
	return (res);
}

t_vec3	make_unit_vector(t_vec3 vec)
{
	t_vec3	newVec;
	float	k;

	k = 1 / vec_length(vec);
	newVec.x = vec.x * k;
	newVec.y = vec.y * k;
	newVec.z = vec.z * k;
	return (newVec);
}

t_vec3	vec_addition(t_vec3 lhs, t_vec3 rhs)
{
	t_vec3	res;

	res.x = rhs.x + lhs.x;
	res.y = rhs.y + lhs.y;
	res.z = rhs.z + lhs.z;
	return (res);
}

t_vec3	vec_multiplication(t_vec3 lhs, t_vec3 rhs)
{
	t_vec3 res;

	res.x = rhs.x * lhs.x;
	res.y = rhs.y * lhs.y;
	res.z = rhs.z * lhs.z;
	return (res);
}

t_vec3	vec_float_multi(float m, t_vec3 vec)
{
	t_vec3	res;

	res.x = m * vec.x;
	res.y = m * vec.y;
	res.z = m * vec.z;
	return (res);
}
