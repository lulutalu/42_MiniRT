/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduboulo <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 17:45:35 by lduboulo          #+#    #+#             */
/*   Updated: 2022/10/21 22:35:56 by lduboulo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

void	camera_init(t_mlx *mlx, t_camera *cam)
{
	float	h;

	cam->fov = 150;
	h = tan(cam->fov);
	cam->viewport_height = 2.0f * h;
	cam->viewport_width = mlx->aspect_ratio * cam->viewport_height;
	cam->pos = new_vec(0.0f, 0.0f, 0);
	cam->dir = new_vec(0.0f, 0.0f, 1.0f);
	cam->vup = new_vec(0, 1, 0);
	//printf("View Height : %f\nView Width : %f\n", cam->viewport_height, cam->viewport_width);
}
