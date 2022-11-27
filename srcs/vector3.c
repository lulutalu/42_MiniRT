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

t_vec3	rotate(t_vec3 p, float ax, float ay, float az)
{
	float	point[3][1];
	float	m[3][3][3];

	point[0][0] = p.x;
	point[1][0] = p.y;
	point[2][0] = p.z;
	get_angle_mtx(&m, ax, ay, az);
	mtx_mul(m[0], point);
	mtx_mul(m[1], point);
	mtx_mul(m[2], point);
	p.x = point[0][0];
	p.y = point[1][0];
	p.z = point[2][0];
	return (p);
}

void	get_angle_mtx(float (*m)[3][3][3], float ax, float ay, float az)
{
	float	a;
	float	b;
	float	c;

	a = ax * M_PI / 180;
	b = ay * M_PI / 180;
	c = az * M_PI / 180;
	mtx_setline(&(*m)[0][0], 1, 0, 0);
	mtx_setline(&(*m)[0][1], 0, cosf(a), -sinf(a));
	mtx_setline(&(*m)[0][2], 0, sinf(a), cosf(a));
	mtx_setline(&(*m)[1][0], cosf(b), 0, sinf(b));
	mtx_setline(&(*m)[1][1], 0, 1, 0);
	mtx_setline(&(*m)[1][2], -sinf(b), 0, cosf(b));
	mtx_setline(&(*m)[2][0], cosf(c), -sinf(c), 0);
	mtx_setline(&(*m)[2][1], sinf(c), cosf(c), 0);
	mtx_setline(&(*m)[2][2], 0, 0, 1);
}

void	mtx_setline(float (*line)[], float a, float b, float c)
{
	(*line)[0] = a;
	(*line)[1] = b;
	(*line)[2] = c;
}

void	mtx_mul(float a[3][3], float b[3][1])
{
	int		i;
	int		j;
	int		k;
	float	res[3][1];

	i = 0;
	while (i < 3)
	{
		j = 0;
		while (j < 1)
		{
			k = 0;
			res[i][j] = 0;
			while (k < 3)
			{
				res[i][j] += a[i][k] * b[k][j];
				k++;
			}
			j++;
		}
		i++;
	}
	b[0][0] = res[0][0];
	b[1][0] = res[1][0];
	b[2][0] = res[2][0];
}

t_vec3	rev_rotate(t_vec3 p, float ax, float ay, float az)
{
	float	point[3][1];
	float	m[3][3][3];

	point[0][0] = p.x;
	point[1][0] = p.y;
	point[2][0] = p.z;
	get_angle_mtx(&m, ax, ay, az);
	mtx_mul(m[2], point);
	mtx_mul(m[1], point);
	mtx_mul(m[0], point);
	p.x = point[0][0];
	p.y = point[1][0];
	p.z = point[2][0];
	return (p);
}
