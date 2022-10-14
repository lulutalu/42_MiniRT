/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduboulo <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 14:55:19 by lduboulo          #+#    #+#             */
/*   Updated: 2022/10/14 20:07:32 by lduboulo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_RT_H
# define MINI_RT_H

/*
 * Extern Librarys include
*/

# include <fcntl.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <stdbool.h>

/*
 * Mlx and Ft libraries include
*/

# include "utils.h"
# include "../mlx/mlx.h"

/*
 * Defines
*/

/////////////////////////		Mlx Key		////////////////////////////////////

# define UP_ARROW 126
# define DOWN_ARROW 125
# define LEFT_ARROW 123
# define RIGHT_ARROW 124

# define ESC 53

/////////////////////////		Macro		////////////////////////////////////

# define SPHERE 0
# define PLANE 1
# define CYLINDER 2

/*
 * Structures
*/

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

typedef struct s_mlx
{
	void	*mlx;
	void	*window;
	t_data	img;
	int		x_start;
	int		y_start;
	int		x_end;
	int		y_end;
	int		frame;
	bool	direction;
}				t_mlx;

typedef struct s_rgb
{
	int	red;
	int	green;
	int	blue;
}				t_rgb;

typedef struct s_point
{
	float	x;
	float	y;
	float	z;
}				t_point;

typedef struct s_obj
{
	int		id;
	float	light_range;
	t_rgb	rgb;
	t_point	pos;
	t_point	vec;
	float	fov;
	float	diameter;
	float	height;
}				t_obj;

typedef struct s_main
{
	t_obj	*obj;
	t_mlx	mlx;
}				t_main;

/*
 * Functions Prototype
*/

/////////////////////////		mlx_utils.c		////////////////////////////////

void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
int		keyhook(int keycode, t_mlx *mlx);
int		close_window(int keycode, t_mlx *mlx);
void	rt_init(t_mlx *mlx);

#endif
