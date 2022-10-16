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

t_point	new_vec(float x, float y, float z)
{
	t_point	new;

	new.x = x;
	new.y = y;
	new.z = z;
	return (new);
}

float	dot(t_point rhs, t_point lhs)
{
	float	res;

	res = (rhs.x * lhs.x) + (rhs.y * lhs.y) + (rhs.z * lhs.z);
	return (res);
}

t_point	vec_minus(t_point lhs, t_point rhs)
{
	t_point	res;

	res.x = lhs.x - rhs.x;
	res.y = lhs.y - rhs.y;
	res.z = lhs.z - rhs.z;
	return (res);
}
