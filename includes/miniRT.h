/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngda-sil <ngda-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 14:55:19 by lduboulo          #+#    #+#             */
/*   Updated: 2022/11/02 22:57:26 by ngda-sil         ###   ########.fr       */
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
	t_data		img;
	float		aspect_ratio;
	int			x_res;
	int			y_res;
}							t_mlx;

typedef struct s_vec3
{
	float	x;
	float	y;
	float	z;
}				t_vec3;

typedef struct s_intersection
{
	float	discri;
	float	t1;
	float	t2;
	float	t;
}				t_inter;

typedef struct s_ray
{
	t_vec3	origin;
	t_vec3	direction;
	int		closest_obj;
	float	t;
}				t_ray;

typedef struct s_obj
{
	int			id;
	float		light_r;
	t_vec3		rgb;
	t_vec3		pos;
	t_vec3		vec;
	float		fov;
	float		diameter;
	float		height;
}				t_obj;

typedef struct s_camera
{
	t_vec3	pos;
	t_vec3	dir;
	int		fov;
	t_vec3	forward;
	t_vec3	right;
	t_vec3	up;
	float	h;
	float	w;
}				t_camera;

typedef struct s_scn
{
	t_obj	*obj;
	int		n_obj;
	int		a;
	int		c;
	int		l;
}				t_scn;

typedef struct s_main
{
	t_mlx		mlx;
	t_camera	cam;
	t_scn		scn;
	float		aspect_ratio;
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

/////////////////////////		vector3.c		////////////////////////////////

bool	is_vec_equal(t_vec3 lhs, t_vec3 rhs);

///////////////////////		raytracing.c	////////////////////////////////

int		frame_loop(t_main *main);
void	pixel_color(t_main *main, t_ray ray, int x, int y);
float	shadow_value(t_ray ray, t_vec3 l_pos, t_scn scnene);
t_ray	ray_generation(t_main *main, int x, int y);

///////////////////////			camera.c	////////////////////////////////

void	camera_init(t_mlx *mlx, t_camera *cam, t_scn *scn);
t_obj	*find_in_tab(t_scn *scn, int id);

///////////////////////		intersection.c	////////////////////////////////

float	hit_sphere(t_vec3 center, float radius, t_ray ray);
float	hit_plane(t_vec3 pos, t_vec3 dir, t_ray ray);
void	check_intersection(t_obj obj, int i, t_ray *ray);
void	check_shadow_intersection(t_obj obj, int i, t_ray *ray);
float	hit_cylinder(t_obj obj, t_ray ray);

///////////////////////		parcing.c	////////////////////////////////

void	parse(int ac, char **av, t_main *m);

///////////////////////		check_args.c	////////////////////////////////

void	check_args(int ac, char **av, t_main *m);

///////////////////////		clean.c	    ////////////////////////////////

void	exit_error(char *str, t_main *m);
void	perror_exit(char *s);

///////////////////////		init.c	   ////////////////////////////////

void	init_scn(t_scn *scn);
void	init_obj(t_main *m);

///////////////////////		parcing_utils.c	    ////////////////////////////////

char	*trim_free(char *s, char *set);
void	count_obj(char *f_path, t_main *m);
int		check_size_tab(char **str, int nb);
float	ft_atof(char *s);

/////////////////////////		fill_obj_1.c		/////////////////////////

void	fill_obj_a(char **info, t_main *m, int i);
void	fill_obj_c(char **info, t_main *m, int i);
void	fill_obj_l(char **info, t_main *m, int i);

/////////////////////////		fill_obj_2.c		/////////////////////////

void	fill_obj_sp(char **info, t_main *m, int i);
void	fill_obj_pl(char **info, t_main *m, int i);
void	fill_obj_cy(char **info, t_main *m, int i);

/////////////////////////		get.c		/////////////////////////

void	get_l_r(char *l_r, t_main *m, int i);
void	get_rgb(char *rgb, t_main *m, int i);
void	get_pos(char *coord, t_main *m, int i);
void	get_vec(char *coord, t_main *m, int i);
void	get_fov(char *fov, t_main *m, int i);

/////////////////////////		valid_char.c		/////////////////////////

int		valid_char(char *s);
int		valid_char_fl(char *s);
int		valid_char_rgb(char *s);

#endif
