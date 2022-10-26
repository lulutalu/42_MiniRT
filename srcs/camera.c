/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduboulo <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 17:45:35 by lduboulo          #+#    #+#             */
/*   Updated: 2022/10/26 16:23:55 by lduboulo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

void	camera_init(t_mlx *mlx, t_camera *cam)
{
	cam->fov = 120;
	cam->pos = new_vec(0.0f, 0.0f, 0.0f);
	cam->dir = new_vec(0.0f, 0.0f, -1.0f);
	cam->forward = make_unit_vector(cam->dir);
	cam->right = cross(new_vec(0.0f, 1.0f, 0.0f), cam->forward);
	cam->right = make_unit_vector(cam->right);
	cam->up = cross(cam->forward, cam->right);
	cam->w = tan(cam->fov);
	cam->h = cam->w * mlx->aspect_ratio;
}
