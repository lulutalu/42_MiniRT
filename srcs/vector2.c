/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduboulo <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 19:27:32 by lduboulo          #+#    #+#             */
/*   Updated: 2022/10/16 22:06:50 by lduboulo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

t_vec3	new_vec(float x, float y, float z)
{
	t_vec3	new;

	new.x = x;
	new.y = y;
	new.z = z;
	return (new);
}

float	dot(t_vec3 lhs, t_vec3 rhs)
{
	float	res;

	res = (rhs.x * lhs.x) + (rhs.y * lhs.y) + (rhs.z * lhs.z);
	return (res);
}

t_vec3	vec_minus(t_vec3 lhs, t_vec3 rhs)
{
	t_vec3	res;

	res.x = lhs.x - rhs.x;
	res.y = lhs.y - rhs.y;
	res.z = lhs.z - rhs.z;
	return (res);
}
