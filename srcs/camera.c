/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngda-sil <ngda-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 17:45:35 by lduboulo          #+#    #+#             */
/*   Updated: 2022/11/02 22:57:19 by ngda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

t_obj	*find_in_tab(t_scn *scn, int id)
{
	int	i;

	i = 0;
	while (i < scn->n_obj)
	{
		if (scn->obj[i].id == id)
			break ;
		i++;
	}
	return (&scn->obj[i]);
}

void	camera_init(t_mlx *mlx, t_camera *cam, t_scn *scn)
{
	t_obj	*cam_info;

	cam_info = find_in_tab(scn, 'C');
	cam->fov = cam_info->fov;
	cam->pos = cam_info->pos;
	cam->dir = cam_info->vec;
	cam->forward = normalize(cam->dir);
	cam->right = cross(new_vec(0.0f, -1.0f, 0.0f), cam->forward);
	cam->right = normalize(cam->right);
	cam->up = vec_float_multi(-1.0f, cross(cam->forward, cam->right));
	cam->w = (float)fabs(tan(cam->fov));
	cam->h = cam->w * mlx->aspect_ratio;
}

void	camera_update(t_main *main)
{
	main->cam.forward = normalize(main->cam.dir);
	main->cam.right = cross(new_vec(0.0f, -1.0f, 0.0f), main->cam.forward);
	main->cam.right = normalize(main->cam.right);
	main->cam.up = vec_float_multi(-1.0f, cross(main->cam.forward, main->cam.right));
}
