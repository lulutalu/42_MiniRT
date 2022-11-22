/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngda-sil <ngda-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 14:54:21 by lduboulo          #+#    #+#             */
/*   Updated: 2022/11/10 20:09:35 by ngda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

void	hit_wich_cylinder(t_ray ray, t_inter *res, t_obj obj)
{
	t_vec3	hp;

	hp = vec_addition(ray.origin, vec_float_multi(res->t, ray.direction));
	if (hp.y < obj.pos.y || hp.y > obj.pos.y + obj.height)
	{
		if (res->t == res->t1)
			res->t = res->t2;
		else
			res->t = res->t1;
		hp = vec_addition(ray.origin, vec_float_multi(res->t, ray.direction));
		if (hp.y < obj.pos.y || hp.y > obj.pos.y + obj.height)
			res->t = -1.0f;
	}
}
