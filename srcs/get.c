/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngda-sil <ngda-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 20:26:40 by ngda-sil          #+#    #+#             */
/*   Updated: 2022/11/02 22:57:17 by ngda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

void	get_l_r(char *l_r, t_main *m, int i)
{
	float	f_l_r;

	if (valid_char_fl(l_r))
		exit_error("L_R : Invalid input\n", m);
	f_l_r = ft_atof(l_r);
	if (f_l_r < 0 || f_l_r > 1)
		exit_error("L_R : Input not in range\n", m);
	m->scn.obj[i].light_r = f_l_r;
}

void	get_rgb(char *rgb, t_main *m, int i)
{
	char	**split;
	int		j;
	int		tmp;

	j = 0;
	if (valid_char_rgb(rgb))
		exit_error("RGB : Invalid input : char\n", m);
	split = ft_split(rgb, ',');
	if (check_size_tab(split, 3))
		exit_error("RGB : Invalid input : nb\n", m);
	while (split[j])
	{
		tmp = ft_atoi(split[j]);
		if (tmp < 0 || tmp > 255)
			exit_error("RGB : Invalid input : range\n", m);
		j++;
	}
	m->scn.obj[i].rgb.x = ft_atof(split[0]) / 255;
	m->scn.obj[i].rgb.y = ft_atof(split[1]) / 255;
	m->scn.obj[i].rgb.z = ft_atof(split[2]) / 255;
	free(split);
}

void	get_pos(char *coord, t_main *m, int i)
{
	char	**split;
	int		j;

	j = 0;
	split = ft_split(coord, ',');
	while (j < 3)
		if (valid_char(split[j++]))
			exit_error("COORD : Invalid input : char\n", m);
	if (check_size_tab(split, 3))
		exit_error("COORD : Invalid input : nb\n", m);
	m->scn.obj[i].pos.x = ft_atof(split[0]);
	m->scn.obj[i].pos.y = ft_atof(split[1]);
	m->scn.obj[i].pos.z = ft_atof(split[2]);
	free(split);
}

void	get_vec(char *coord, t_main *m, int i)
{
	char	**split;
	int		j;
	float	p;

	j = -1;
	split = ft_split(coord, ',');
	if (check_size_tab(split, 3))
		exit_error("V3d : Invalid input nb arg\n", m);
	while (split[++j])
	{
		if (valid_char(split[j]))
			exit_error("V3d : Invalid input invalid char\n", m);
		p = ft_atoi(split[j]);
		if (p < -1 || p > 1)
			exit_error("V3d : Invalid input : range\n", m);
	}
	m->scn.obj[i].vec.x = ft_atof(split[0]);
	m->scn.obj[i].vec.y = ft_atof(split[1]);
	m->scn.obj[i].vec.z = ft_atof(split[2]);
	free(split);
}

void	get_fov(char *fov, t_main *m, int i)
{
	int	fov_i;
	int	j;

	j = -1;
	while (fov[++j])
	{
		if (!isdigit(fov[j]))
			exit_error("FOV : Invalid input\n", m);
	}
	fov_i = ft_atoi(fov);
	if (fov_i > 180)
		exit_error("FOV : Invalid input\n", m);
	m->scn.obj[i].fov = fov_i;
}
