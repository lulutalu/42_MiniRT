/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngda-sil <ngda-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 22:55:48 by lduboulo          #+#    #+#             */
/*   Updated: 2022/11/08 22:47:22 by ngda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

float	vec_length(t_vec3 vec)
{
	float	res;

	res = sqrtf((vec.x * vec.x) + (vec.y * vec.y) + (vec.z * vec.z));
	return (res);
}

t_vec3	normalize(t_vec3 vec)
{
	t_vec3	new_vec;
	float	k;

	k = 1.0f / vec_length(vec);
	new_vec.x = vec.x * k;
	new_vec.y = vec.y * k;
	new_vec.z = vec.z * k;
	return (new_vec);
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
	t_vec3	res;

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
