/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juthomas <juthomas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/04 03:23:54 by juthomas          #+#    #+#             */
/*   Updated: 2018/04/10 05:41:21 by juthomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H
# include <stdlib.h>
# include <math.h>
# include <stdio.h>
# include <fcntl.h>
# include <pthread.h>
# include "../minilibx_macos/mlx.h"
# include "../libft/libft.h"
# include "./get_next_line.h"
# include "./rt_obj.h"
# include "./rt_light.h"
//# include "./rt_fonction.h"
//# define X_WIN 640
//# define Y_WIN 480

//# define X_WIN 4999
//# define Y_WIN 4999
//# define X_IMG X_WIN * 2
//# define Y_IMG Y_WIN * 2
# define INFINI 200
# define NORM_COLOR 1
# define MAX_RAY_DEPTH 10
# define THREADS 25
# define REFR_2D 0
// NOMBRE DE REFLETS MAX

typedef struct		s_win
{
	int				bpp;
	int				bpp2;
	int				bpp3;
	int				bpp4;
	int				bpp5;
	int				bpp6;
	int				bpp_las;
	int				bpp_loa;

	int				sizeline;
	int				sizeline2;
	int				sizeline3;
	int				sizeline4;
	int				sizeline5;
	int				sizeline6;
	int				sizeline_las;
	int				sizeline_loa;

	int				endian;
	int				endian2;
	int				endian3;
	int				endian4;
	int				endian5;
	int				endian6;
	int				endian_las;
	int				endian_loa;

	void			*img;
	void			*img2;
	void			*img3;
	void			*img4;
	void			*img5;
	void			*img6;
	void			*img_las;
	void			*img_loa;

	char			*addr;
	char			*addr2;
	char			*addr3;
	char			*addr4;
	char			*addr5;
	char			*addr6;
	char			*addr_las;
	char			*addr_loa;

	void			*mlx;
	void			*win;
	int				x_loa;
	int				y_loa;

//	unsigned int	x_win;
//	unsigned int	y_win;
//	unsigned int	x_img;
//	unsigned int	y_img;

	int	x_win;
	int	y_win;
	int	x_img;
	int	y_img;


}					t_win;

typedef struct		s_type
{
	void			*obj;
	char			name;
}					t_type;


typedef struct		s_cam
{
	struct s_vec	*cam_org;
	struct s_vec	*cam_rot;
}					t_cam;

typedef struct		s_scene
{
	struct s_vec	*cam_org;
	struct s_vec	*cam_rot;
	t_list			*cam;
	t_list			*light;
	t_list			*obj;
}					t_scene;

typedef struct		s_trace
{
	int		inter;
	t_vec	*rayorig;
	t_vec	*raydir;
	t_spher	*spher;
	t_spher *sphere;
	t_triangle *triangl;
	t_triangle *triangle;
	t_lspher *lsphere;
	t_lproj	*lproj;
	t_type	*type;
	float	t0;
	float	t1;
	float	t;
	t_vec	*surface_color;
	t_vec	*phit;
	t_vec	*nhit;
	t_vec	*tmp_nhit;
	float	tnear;
	short	inside;
	float	bias;
	float	facingratio;
	float	fresneleffect;
	t_vec	*refldir;
	t_vec	*reflection;
	t_vec	*refraction;
	float	ior;
	float	cosi;
	float	k;
	float	eta;
	t_vec	*refrdir;
	t_vec	*tmp_vec;
	unsigned int i;
	float	lumiere_inc;
	t_vec	*lum_inc;
	int		depth;
	int		test;
	t_vec	*normal;
	float	reflec;
	float	trans;
	t_vec	*obj_color;
	t_vec	*tmp_orig;
	t_vec	*tmp_dir;
	struct s_trace	*tmp_refr;
	struct s_trace	*tmp_refl;
}					t_trace;

typedef struct		s_render
{
	unsigned int	width;
	unsigned int	height;
	unsigned int	y;
	unsigned int	x;
	unsigned int	z;
	unsigned int	x_tmp;
	unsigned int	y_tmp;
	float			yy;
	float			xx;
	float			invWidth;
	float			invHeight;
	float			fov;
	float			aspectratio;
	float			angle;
	int				state;
	unsigned int	zmax;
	t_vec			*raydir;
	t_vec			*rayorig;
}					t_render;

typedef struct		s_thread
{
	t_trace		*trace;
	t_render	*render;
	t_list		*list;
	t_win		*win;
	int			*z;
}					t_thread;

typedef struct		s_phase
{
	unsigned int	width;
	unsigned int	height;
	unsigned int	y_tmp;
	unsigned int	x_tmp;
	int	z;
	unsigned int	zmax;
//	int				state;


	unsigned int	y;
	unsigned int	x;

	float			yy;
	float			xx;
	float			invWidth;
	float			invHeight;
	float			fov;
	float			aspectratio;
	float			angle;
	int				state;
	unsigned int	*getcoor;
}					t_phase;

typedef struct		s_parser
{
	int				fd;
	char			*line;
	int				i;
	int				state;
	char			obj_name;
	int				vo;
}					t_parser;

typedef struct		s_filtre
{
	int				matrix[3][3];
	int				div;
}					t_filtre;

typedef struct		s_super
{
	t_thread	*thread_1;
	t_thread	*thread_2;
	t_thread	*thread_3;
	t_thread	*thread_4;

	t_thread	*thread[THREADS];




	t_phase		*phase;
	t_win		*win;
	t_list		*list;
	t_cam		*cam;
	t_filtre	*filtre;

}					t_super;


t_list			*ft_lstnew_2(t_spher *content, size_t content_size);


//t_list			*rt_parser_main(int argc, char **argv, t_cam **cam, t_win *win);


void			check_vec_dir(t_vec *vec);
void			normalize_vec(t_vec *vec);
t_vec			*new_params_vec(float x, float y, float z);
t_pspher		*new_params_pspher(float radius, float refl, float opac);
t_spher			*new_params_spher(t_vec *pos, t_vec *color, t_pspher *ps);
t_vec			*new_sub_params_vec(t_vec *vec1, t_vec *vec2);
t_list			*ft_lstnew_2(t_spher *content, size_t content_size);
void			*sphere_to_void(t_spher *sphere);
void			img_add_px(t_win *mlx, unsigned int color, int x, int y);
void			normalize_vec(t_vec *vec);
void			push_params_vec(float x, float y, float z, t_vec *vec);
void			test_img(t_win *win);
void			ft_lstadd_2(t_list **last, t_list *elem);
double			ft_adolphe(char *str);
float			dot_product(t_vec *vec1, t_vec *vec2);
int				intersect(t_vec *rayorig, t_vec *raydir, float t0, float t1, t_spher *sphere);
t_vec			*trace(int depth, t_list *list, t_trace *dat);

int				exit_error(int error);
int				rt_parser_no_space(char *str, int i);
int				rt_parser_balise_name(char *str, int i, int *state);
int				rt_parser_go_next_number(char *str, int i);
int				rt_parser_stock_vec(char *str, t_vec *vec, int *nb, int dec);
int				rt_parser_is_correct(char *str, char *ac, int len);
int				rt_parser_stock_color_norm(int *tmp, t_vec *vec, unsigned int color, char *str);
int				rt_parser_stock_color(char *str, t_vec *vec, int *nb, int dec);
int				rt_parser_go_next_number_2(char *str, int i);
int				rt_parser_stock_number(char *str, float *nu, int *nb, int dec);
int				stock_triangle(t_triangle *triangle, char *str, int *nb);
int				stock_cycon(t_cycon *cycon, char *str, int *nb);
int				stock_plan(t_plan *plan, char *str, int *nb);
int				stock_disque(t_disque *disque, char *str, int *nb);
int				stock_spher(t_spher *spher, char *str, int *nb);
int				stock_lpsher(t_lspher *spher, char *str, int *nb);
int				stock_camera(t_cam *cam, char *str, int *nb);
int				stock_lproj_norm(t_lproj *proj, char *str, int *nb);
int				stock_lproj(t_lproj *proj, char *str, int *nb);
void			rt_parser_objtype_lspher_setup(t_lspher *spher);
void			rt_parser_objtype_camera_setup(t_cam *cam);
void			rt_parser_objtype_lproj_setup(t_lproj *proj);
char			rt_parser_objtype_lspher(char *str, void **addr, char type);
void			rt_parser_objtype_camera(char *str, t_cam *cam);
char			rt_parser_objtype_lproj(char *str, void **addr, char type);
void			rt_parser_objtype_spher_setup(t_spher *spher);
void			rt_parser_objtype_triangle_setup(t_triangle *triangle);
void			rt_parser_objtype_cycon_setup(t_cycon *cycon);
void			rt_parser_objtype_disque_setup(t_disque *disque);
void			rt_parser_objtype_plan_setup(t_plan *plan);
void			rt_parser_objtype_triangle_norm(t_triangle *triangle);
char			rt_parser_objtype_triangle(char *str, void **addr, char type);
char			rt_parser_objtype_cycon(char *str, void **addr, char type);
char			rt_parser_objtype_plan(char *str, void **addr, char type);
char			rt_parser_objtype_disque(char *str, void **addr, char type);
char			rt_parser_objtype_spher(char *str, void **addr, char type);
char			rt_parser_objtype(char *str);
char			rt_parser_camera(char *str);
t_type			*rt_parser_objtype_done(char *str, char type);
t_type			*rt_parser_lobjtype_done(char *str, char type);
t_cam			*rt_parser_camera_done(char *str, char type);
int				rt_parser_state(char *str, int state, int i);
void			ft_lstdellast(t_list **list);
t_list			*ft_lstnew2(void *content, size_t content_size, int *vo);
void			rt_parser_stock_win(char *str, t_win *win);

void			img_add_px4(t_win *mlx, unsigned int color, int x, int y);
void 			grayscale(t_win *mlx);
void			img_add_px5(t_win *mlx, int x, int y, unsigned int tr, unsigned int tg, unsigned int tb);
void 			sepia(t_win *mlx);
void 			matrix(t_filtre *filtre);
unsigned int 	ligne1(t_win *mlx, int x, int y, t_filtre *filtre);
unsigned int 	ligne2(t_win *mlx, int x, int y, t_filtre *filtre);
unsigned int 	ligne3(t_win *mlx, int x, int y, t_filtre *filtre);
unsigned int 	Rgb(unsigned int color);
unsigned int 	rGb(unsigned int color);
unsigned int 	rgB(unsigned int color);
void			img_add_px6(t_win *mlx, unsigned int color, int x, int y);
void 			kernel(t_win *mlx);

void			rt_parser_main_setup(int argc, char **argv, t_parser *parser, t_win *win);
t_list			*rt_parser_main_end(t_parser *parser, t_list *list, t_win *win);
void			rt_parser_main_while(t_parser *parser, t_win *win);
t_list			*rt_parser_main(int argc, char **argv, t_cam **cam, t_win *win);

void			rt_parser_objtype_lproj_norm(t_lproj *proj);
void			rt_parser_objtype_cycon_norm(t_cycon *cycon);
void			rt_parser_objtype_plan_norm(t_plan *plan);
void			rt_parser_objtype_disque_norm(t_disque *disq);

void			rt_parser_objtype_spher_norm(t_spher *spher);

void			rt_parser_check_var_max(float *var, float max);




#endif
