/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduboulo <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 20:55:41 by lduboulo          #+#    #+#             */
/*   Updated: 2022/10/14 22:13:34 by lduboulo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

void	put_pixel_color(t_mlx *mlx, int x, int y, t_vec3 rgb)
{
	my_mlx_pixel_put(&mlx->img, x, y, create_trgb(0, rgb.x * 255, rgb.y * 255, \
				rgb.z * 255));
}
