/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduboulo <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 14:55:19 by lduboulo          #+#    #+#             */
/*   Updated: 2022/10/21 23:22:59 by lduboulo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

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

# define PI 3.142857

/*
 * Structures
*/

typedef struct s_data
{
	void	*ptr;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}							t_data;

typedef struct s_mlx
{
	void		*ptr;
	void		*window;
	t_data	img;
	float		aspect_ratio;
	int			x_res;
	int			y_res;
}							t_mlx;

typedef struct s_rgb
{
	int		red;
	int		green;
	int		blue;
}				t_rgb;

typedef struct s_vec3
{
	float	x;
	float	y;
	float	z;
}				t_vec3;

typedef struct s_ray
{
	t_vec3	origin;
	t_vec3	direction;
}				t_ray;

typedef struct s_obj
{
	int			id;
	float		light_range;
	t_rgb		rgb;
	t_vec3	pos;
	t_vec3	vec;
	float		fov;
	float		diameter;
	float		height;
}				t_obj;

typedef struct s_camera
{
	t_vec3	pos;
	t_vec3	dir;
	t_vec3	vup;
	int		fov;
	float	viewport_height;
	float	viewport_width;
}				t_camera;

typedef struct s_main
{
	t_obj		obj; //remember to declare it as a pointer
	t_mlx		mlx;
	t_camera	cam;
}				t_main;

/*
 * Functions Prototype
*/

/////////////////////////		mlx_utils.c		////////////////////////////////

void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
int		keyhook(int keycode, t_main *main);
void	image_init(t_mlx *mlx);
int		close_window(int keycode, t_mlx *mlx);
void	rt_init(t_mlx *mlx);

/////////////////////////		colors.c		////////////////////////////////

int		create_trgb(int t, int r, int g, int b);
void	put_pixel_color(t_mlx *mlx, int x, int y, t_vec3 rgb);

/////////////////////////		vector.c		////////////////////////////////

float	vec_length(t_vec3 vec);
t_vec3	make_unit_vector(t_vec3 vec);
t_vec3	vec_addition(t_vec3 lhs, t_vec3 rhs);
t_vec3	vec_multiplication(t_vec3 lhs, t_vec3 rhs);
t_vec3	vec_float_multi(float m, t_vec3 vec);

/////////////////////////		vector2.c		////////////////////////////////

t_vec3	new_vec(float x, float y, float z);
float	dot(t_vec3 lhs, t_vec3 rhs);
t_vec3	vec_minus(t_vec3 lhs, t_vec3 rhs);
t_vec3	cross(t_vec3 lhs, t_vec3 rhs);
t_vec3	vec_div(float div, t_vec3 vec);

///////////////////////		raytracing.c	////////////////////////////////

int		frame_loop(t_main *main);
void	pixel_color(t_main *main, t_ray ray, int x, int y);
float	hit_sphere(t_vec3 center, float radius, t_ray ray);
t_ray	ray_generation(t_main *main, int x, int y);

///////////////////////			camera.c	////////////////////////////////

void	camera_init(t_mlx *mlx, t_camera *cam);

///////////////////////		intersection.c	////////////////////////////////

float	hit_sphere(t_vec3 center, float radius, t_ray ray);
float	hit_plane(t_vec3 pos, t_vec3 dir, t_ray ray);

#endif
