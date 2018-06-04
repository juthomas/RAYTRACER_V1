/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juthomas <juthomas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/04 03:22:04 by juthomas          #+#    #+#             */
/*   Updated: 2018/04/10 06:03:14 by tle-gac-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt_obj.h"
#include "../includes/rt.h"

t_vec	*new_params_vec(float x, float y, float z)
{
	t_vec		*vec;

	vec = (t_vec*)malloc(sizeof(*vec));
	vec->x = x;
	vec->y = y;
	vec->z = z;
	return (vec);
}

void	cpy_params_vec(t_vec *vec, t_vec *ret)
{
	ret->x = vec->x;
	ret->y = vec->y;
	ret->z = vec->z;
}

void	mult_vec_by_vec(t_vec *vec1, t_vec *vec2, t_vec *ret)
{
	ret->x = vec1->x * vec2->x;
	ret->y = vec1->y * vec2->y;
	ret->z = vec1->z * vec2->z;
}

void	mult_params_vec(t_vec *vec, float mult)
{
	vec->x *= mult;
	vec->y *= mult;
	vec->z *= mult;
}

t_vec	*test_inv(t_vec *vec , t_vec  *tmp)
{
	tmp->x = -vec->x;
	tmp->y = -vec->y;
	tmp->z = -vec->z;
	return (tmp);
}

t_pspher	*new_params_pspher(float radius, float refl, float opac)
{
	t_pspher	*ps;

	ps = (t_pspher*)malloc(sizeof(*ps));
	ps->radius = radius;
	ps->refl = refl;
	ps->opac = opac;
	return (ps);
}

t_spher		*new_params_spher(t_vec *pos, t_vec *color, t_pspher *ps)
{
	t_spher		*sphere;

	sphere = (t_spher*)malloc(sizeof(*sphere));
	sphere->pos = pos;
	sphere->color = color;
	sphere->pspher = ps;
	return (sphere);
}

void	sub_params_vec(t_vec *vec1, t_vec *vec2, t_vec *vec)
{
	vec->x = vec1->x - vec2->x;
	vec->y = vec1->y - vec2->y;
	vec->z = vec1->z - vec2->z;
}

t_vec	*new_sub_params_vec(t_vec *vec1, t_vec *vec2)
{
	t_vec *vec;

	vec = (t_vec*)malloc(sizeof(*vec));
	vec->x = vec1->x - vec2->x;
	vec->y = vec1->y - vec2->y;
	vec->z = vec1->z - vec2->z;
	return (vec);
}

void	push_color_vec(unsigned int color, t_vec *vec)
{
	vec->x = color / 0x10000  % 0x100;
	vec->y = color / 0x100 % 0x100;
	vec->z = color % 0x100;
}

unsigned int	vec_to_color(t_vec *vec)
{
	unsigned int	R;
	unsigned int	G;
	unsigned int	B;

	if (vec->x >= 1 && vec->x >= vec->y && vec->x >= vec->z) // ET R > G ET B
	{
		if (vec->x > 2)
			vec->x = 2;
		R = 0xff;
		if (vec->y < 1)
			G = vec->y * 0xff + (1 - vec->y) * (vec->x - 1) * 0xff;
		else
			G = 0xff;
		if (vec->z < 1)
			B = vec->z * 0xff + (1 - vec->z) * (vec->x - 1) * 0xff;
		else
			B = 0xff;
	}
	else if (vec->y >= 1 && vec->y >= vec->x && vec->y >= vec->z) // ET G > R ET B
	{
		if (vec->y > 2)
			vec->y = 2;
		if (vec->x < 1)
			R = vec->x * 0xff + (1 - vec->x) * (vec->y - 1) * 0xff;
		else
			R = 0xff;
		G = 0xff;
		if (vec->z < 1)
			B = vec->z * 0xff + (1 - vec->z) * (vec->y - 1) * 0xff;
		else
			B = 0xff;
	}
	else if (vec->z >= 1 && vec->z >= vec->x && vec->z >= vec->y) // ET G > R ET B
	{
		if (vec->z > 2)
			vec->z = 2;
		if (vec->x < 1)
			R = vec->x * 0xff + (1 - vec->x) * (vec->z - 1) * 0xff;
		else
			R = 0xff;
		if (vec->y < 1)
			G = vec->y * 0xff + (1 - vec->y) * (vec->z - 1) * 0xff;
		else
			G = 0xff;
		B = 0xff;
	}
	else
	{
		R = (int)(vec->x * 0xff);
		G = (int)(vec->y * 0xff);
		B = (int)(vec->z * 0xff);
	}
	return (R * 0x10000 + G * 0x100 + B);
}


unsigned int	vec_to_color_oldy(t_vec *vec)
{
	unsigned int	R;
	unsigned int	G;
	unsigned int	B;
	//	float			col[3];


	if (vec->x >= 1 && vec->x >= vec->y && vec->x >= vec->z) // ET R > G ET B
	{
		R = 0xff;
		if (vec->y < 1)
			G = vec->y * 0xff + (1 - vec->y) * (vec->x - 1) * 0xff;
		else
			G = 0xff;
		if (vec->z < 1)
			B = vec->z * 0xff + (1 - vec->z) * (vec->x - 1) * 0xff;
		else
			B = 0xff;
	}
	else if (vec->y >= 1 && vec->y >= vec->x && vec->y >= vec->z) // ET G > R ET B
	{
		if (vec->x < 1)
			R = vec->x * 0xff + (1 - vec->x) * (vec->y - 1) * 0xff;
		else
			R = 0xff;
		G = 0xff;
		if (vec->z < 1)
			B = vec->z * 0xff + (1 - vec->z) * (vec->y - 1) * 0xff;
		else
			B = 0xff;
	}
	else if (vec->z >= 1 && vec->z >= vec->x && vec->z >= vec->y) // ET G > R ET B
	{
		if (vec->x < 1)
			R = vec->x * 0xff + (1 - vec->x) * (vec->z - 1) * 0xff;
		else
			R = 0xff;
		if (vec->y < 1)
			G = vec->y * 0xff + (1 - vec->y) * (vec->z - 1) * 0xff;
		else
			G = 0xff;
		B = 0xff;
	}
	else
	{
		R = (int)(vec->x * 0xff);
		G = (int)(vec->y * 0xff);
		B = (int)(vec->z * 0xff);
	}
	return (R * 0x10000 + G * 0x100 + B);
}

unsigned int	vec_to_color_old(t_vec *vec)
{
	unsigned int	color;

	color = 0;
	if (vec->x < 1)
		color += (int)(vec->x * 0xff) * 0x10000;
	else
		color += 0xff * 0x10000;
	if (vec->y < 1)
		color += (int)(vec->y * 0xff) * 0x100;
	else
		color += 0xff * 0x100;
	if (vec->z < 1)
		color += vec->z * 0xff;
	else
		color += 0xff;
	return (color);
}

void	push_params_vec(float x, float y, float z, t_vec *vec)
{
	vec->x = x;
	vec->y = y;
	vec->z = z;
}

void	push_one4all_param_vec(float x, t_vec *vec)
{
	vec->x = x;
	vec->y = x;
	vec->z = x;
}

unsigned int	img_get_px(t_win *mlx, int x, int y)
{
	unsigned int	color;

	color = 0;
	if (x < mlx->x_img && y < mlx->x_img && x >= 0 && y >= 0)
	{
		color = mlx->addr[(y * mlx->sizeline + x * mlx->bpp / 8)];
		color += mlx->addr[(y * mlx->sizeline + x *
				mlx->bpp / 8) + 1] * 256;
		color += mlx->addr[(y * mlx->sizeline + x *
				mlx->bpp / 8) + 2] * 256 * 256;
	}
	return (color);
}

void		img_add_px(t_win *mlx, unsigned int color, int x, int y)
{

	//		printf("COOOLEOEOENF %x\n", color);
	if (x < mlx->x_img && y < mlx->y_img && x >= 0 && y >= 0)
	{
		mlx->addr[(y * mlx->sizeline + x * mlx->bpp / 8)] = color;
		mlx->addr[(y * mlx->sizeline + x * mlx->bpp / 8) + 1] = color >> 8;
		mlx->addr[(y * mlx->sizeline + x * mlx->bpp / 8) + 2] = color >> 16;
	}
}

void		img_add_px2(t_win *mlx, unsigned int color, int x, int y)
{

	//		printf("COOOLEOEOENF %x\n", color);
	if (x < mlx->x_win && y < mlx->y_win && x >= 0 && y >= 0)
	{
		mlx->addr2[(y * mlx->sizeline2 + x * mlx->bpp2 / 8)] = color;
		mlx->addr2[(y * mlx->sizeline2 + x * mlx->bpp2 / 8) + 1] = color >> 8;
		mlx->addr2[(y * mlx->sizeline2 + x * mlx->bpp2 / 8) + 2] = color >> 16;
	}
}

void		img_add_px_las(t_win *mlx, unsigned int color, int x, int y)
{

	//		printf("COOOLEOEOENF %x\n", color);
	if (x < mlx->x_win && y < 10 && x >= 0 && y >= 0)
	{
		mlx->addr_las[(y * mlx->sizeline_las + x * mlx->bpp_las / 8)] = color;
		mlx->addr_las[(y * mlx->sizeline_las + x * mlx->bpp_las / 8) + 1] = color >> 8;
		mlx->addr_las[(y * mlx->sizeline_las + x * mlx->bpp_las / 8) + 2] = color >> 16;
	}
}





void		img_add_px3(t_win *mlx, unsigned int color, int x, int y)
{

	//		printf("COOOLEOEOENF %x\n", color);
	if (x < mlx->x_win && y < mlx->y_win && x >= 0 && y >= 0)
	{
		mlx->addr3[(y * mlx->sizeline3 + x * mlx->bpp3 / 8)] = color;
		mlx->addr3[(y * mlx->sizeline3 + x * mlx->bpp3 / 8) + 1] = color >> 8;
		mlx->addr3[(y * mlx->sizeline3 + x * mlx->bpp3 / 8) + 2] = color >> 16;
	}
}


void	normalize_vec(t_vec *vec)
{
	float	inv_len_vec;

	inv_len_vec = 1 / sqrt(vec->x * vec->x + vec->y * vec->y + vec->z * vec->z);
	vec->x *= inv_len_vec;
	vec->y *= inv_len_vec;
	vec->z *= inv_len_vec;
}

float	dot_product(t_vec *vec1, t_vec *vec2)
{
	return (vec1->x * vec2->x + vec1->y * vec2->y + vec1->z * vec2->z);
}

void	check_vec_dir(t_vec *vec)
{
	if (vec->x == 0 && vec->y == 0 && vec->z == 0)
		vec->z = 1;
	normalize_vec(vec);
}

void	cross_product(t_vec *vec1, t_vec *vec2, t_vec *ret)
{
	//	ret->x = vec1->y * vec2->z - vec1->z * vec2->y;
	//	ret->y = vec1->x * vec2->z - vec1->z * vec2->x;
	//	ret->z = vec1->x * vec2->y - vec1->y * vec2->x;

	ret->x = vec2->y * vec1->z - vec2->z * vec1->y;
	ret->y = vec2->z * vec1->x - vec2->x * vec1->z;
	ret->z = vec2->x * vec1->y - vec2->y * vec1->x;
}

int		intersect_plan(t_trace *tr, float *t, t_plan *plan)
{
	float	denom;
	t_vec	*v;

	denom = dot_product(plan->rot, tr->tmp_dir);
	if (denom < -0.000001 || denom > 0.000001)
	{
		v = new_sub_params_vec(plan->pos, tr->tmp_orig);
		*t = dot_product(v, plan->rot) / denom;
		free(v);
		//inverser nhit si necessaire
		return (*t >=0);
	}
	return (0);
}

int		intersect_triangle(t_trace *tr, float *t, t_triangle *triangle)
{
	t_vec	*v1[2];
	t_vec	*v2[3];
	float	len[3];
	float	inv;
	float	det;

	v2[2] = new_params_vec(0,0,0);
	v2[0] = new_params_vec(0, 0, 0);
	v1[0] = new_sub_params_vec(triangle->p2, triangle->p1);
	v1[1] = new_sub_params_vec(triangle->p3, triangle->p1);


	cross_product(tr->tmp_dir, v1[1], v2[0]);
	//	cross_product(tr->raydir, v1[1], v2[0]);
	if ((det = dot_product(v1[0], v2[0])), det > -0.000001 && det < 0.000001)
	{
		free(v1[0]);
		free(v1[1]);
		free(v2[0]);
		//free(v2[1]);
		free(v2[2]);


		return (0);
	}
	inv = 1. / det;
	//	v2[1] = new_sub_params_vec(tr->rayorig, triangle->p1);
	v2[1] = new_sub_params_vec(tr->tmp_orig, triangle->p1);
	if ((len[0] = dot_product(v2[1], v2[0]) * inv), len[0] < 0 || len[0] > 1)
	{
		free(v1[0]);
		free(v1[1]);
		free(v2[0]);
		free(v2[1]);
		free(v2[2]);
		return (0);
	}
	cross_product(v2[1], v1[0], v2[2]);
	//	if (len[1] = dot_product(tr->raydir, v2[2]) * inv, len[1] < 0 || len[0] + len[1] > 1)
	if (len[1] = dot_product(tr->tmp_dir, v2[2]) * inv, len[1] < 0 || len[0] + len[1] > 1)
	{
		free(v1[0]);
		free(v1[1]);
		free(v2[0]);
		free(v2[1]);
		free(v2[2]);
		return (0);
	}
	if ((len[2] =  dot_product(v1[1], v2[2]) * inv) > 0.000001)
	{

		//		push_params_vec(tr->tmp_orig->x + tr->tmp_dir->x * len[2], tr->tmp_orig->y + tr->tmp_dir->y * len[2], tr->tmp_orig->z + tr->tmp_dir->z * len[2], tr->phit);

		cross_product(v1[0], v1[1], tr->tmp_nhit);
		//	if (dot_product(tr->raydir, tr->nhit) > 0)
		if (dot_product(tr->tmp_dir, tr->tmp_nhit) > 0)
		{
			tr->tmp_nhit->x *= -1;
			tr->tmp_nhit->y *= -1;
			tr->tmp_nhit->z *= -1;
		}
		*t = len[2];
		free(v1[0]);
		free(v1[1]);
		free(v2[0]);
		free(v2[1]);
		free(v2[2]);
		return (1);
	}
	free(v1[0]);
	free(v1[1]);
	free(v2[0]);
	free(v2[1]);
	free(v2[2]);
	return (0);
}


int		intersect_triangle3(t_trace *tr, float *t, t_triangle *triangle)
{
	t_vec	*e0;
	t_vec	*e1;
	t_vec	*p0;
	t_vec	*p1;
	float	inv;
	float	det;
	float	v0;
	float	v1;
	float	v2;
	t_vec	*tmp;

	tmp = new_params_vec(0,0,0);
	p0 = new_params_vec(0, 0, 0);
	e0 = new_sub_params_vec(triangle->p2, triangle->p1);
	e1 = new_sub_params_vec(triangle->p3, triangle->p1);
	cross_product(tr->raydir, e1, p0);
	if ((det = dot_product(e0, p0)), det > -0.000001 && det < 0.000001)
		return (0);
	inv = 1. / det;
	p1 = new_sub_params_vec(tr->rayorig, triangle->p1);
	if ((v0 = dot_product(p1, p0) * inv), v0 < 0 || v0 > 1)
		return (0);
	cross_product(p1, e0, tmp);
	if (v1 = dot_product(tr->raydir, tmp) * inv, v1 < 0 || v0 + v1 > 1)
		return (0);
	if ((v2 =  dot_product(e1, tmp) * inv) > 0.000001)
	{
		*t = v2;
		return (1);
	}
	return (0);


}

int		intersect_triangle3_rr(t_trace *tr, float *t, t_triangle *triangle)
{
	t_vec	*e0;
	t_vec	*e1;
	t_vec	*p0;
	t_vec	*p1;
	float	inv;
	float	det;
	float	v0;
	float	v1;
	float	v2;
	t_vec	*tmp;
	t_vec	*tp1;
	t_vec	*tp2;
	t_vec	*tp3;


	tp1 = new_params_vec(-triangle->p1->x, triangle->p1->y, -triangle->p1->z);
	tp2 = new_params_vec(-triangle->p2->x, triangle->p2->y, -triangle->p2->z);
	tp3 = new_params_vec(-triangle->p3->x, triangle->p3->y, -triangle->p3->z);

	tmp = new_params_vec(0,0,0);
	p0 = new_params_vec(0, 0, 0);
	e0 = new_sub_params_vec(tp2, tp1);
	e1 = new_sub_params_vec(tp3, tp1);
	cross_product(tr->raydir, e1, p0);
	if ((det = dot_product(e0, p0)), det > -0.000001 && det < 0.000001)
		return (0);
	inv = 1. / det;
	p1 = new_sub_params_vec(tr->rayorig, tp1);
	if ((v0 = dot_product(p1, p0) * inv), v0 < 0 || v0 > 1)
		return (0);
	cross_product(p1, e0, tmp);
	if (v1 = dot_product(tr->raydir, tmp) * inv, v1 < 0 || v0 + v1 > 1)
		return (0);
	if ((v2 =  dot_product(e1, tmp) * inv) > 0.000001)
	{
		*t = v2;
		return (1);
	}
	return (0);


}

int		intersect_triangle3_ww(t_trace *tr, float *t, t_triangle *triangle)
{
	t_vec	*v1v2;
	t_vec	*v1v3;
	t_vec	*pvec;
	float	det;
	float	invdet;
	t_vec	*tvec;
	float	u;
	t_vec	*qvec;
	float	v;
	float	p;

	pvec = new_params_vec(0,0,0);
	v1v2 = new_sub_params_vec(triangle->p2, triangle->p1); //e1
	v1v3 = new_sub_params_vec(triangle->p3, triangle->p1); //e2
	cross_product(tr->raydir, v1v3, pvec); //h < d cross e2
	det = dot_product(v1v2, pvec); //a < innerproduct( e1, h)
	//	if (det < 1e-8 || fabs(det) < 1e-8)
	//		return (0);
	invdet = 1/det;
	tvec = new_sub_params_vec(tr->rayorig, triangle->p1);
	u = dot_product(tvec, pvec) * invdet;
	if (u < 0 || u > 1)
		return (0);
	qvec = new_params_vec(0, 0, 0);
	cross_product(tvec, v1v2, qvec);
	v = dot_product(tr->raydir, qvec) * invdet;
	if (v < 0 || u + v > 1)
		return (0);
	*t = dot_product(v1v3, qvec) * invdet;
	return (1);
}

int		intersect_triangle3_dd(t_trace *tr, float *t, t_triangle *triangle)
{
	t_vec	*v1v2;
	t_vec	*v1v3;
	//	t_vec	*hain;
	t_vec	*P;
	t_vec	*C;
	t_vec	*edge1;
	t_vec	*vp1;
	t_vec	*edge2;
	t_vec	*vp2;
	t_vec	*edge3;
	t_vec	*vp3;

	float	area2;
	float	NdotRayDirection;
	float	d;

	C = new_params_vec(0,0,0);
	//	hain = new_params_vec(0,0,0);
	// compute plane's normal
	///Vec3f v0v1 = v1 - v0; 
	v1v2 = new_sub_params_vec(triangle->p2, triangle->p1);

	///Vec3f v0v2 = v2 - v0;

	v1v3 = new_sub_params_vec(triangle->p3, triangle->p1);

	// no need to normalize
	//Vec3f N = v0v1.crossProduct(v0v2); // N 
	cross_product(v1v2, v1v3, tr->nhit);

	///float area2 = N.length(); D
	area2 = sqrt(tr->nhit->x * tr->nhit->x + tr->nhit->y * tr->nhit->y + tr->nhit->z * tr->nhit->z);

	// Step 1: finding P
	// check if ray and plane are parallel ?
	/// NdotRayDirection = N.dotProduct(dir); D
	NdotRayDirection = dot_product(tr->nhit, tr->raydir);

	/// if (fabs(NdotRayDirection) < kEpsilon) // almost 0 
	///return false; // they are parallel so they don't intersect ! 
	if (fabs(NdotRayDirection) < 1e-8)
	{
		free(v1v2);
		free(v1v3);
		free(C);
		return (0);
	}
	// compute d parameter using equation 2
	d = dot_product(tr->nhit, triangle->p1);

	// compute t (equation 3)
	//t = (N.dotProduct(orig) + d) / NdotRayDirection; 
	*t = (dot_product(tr->nhit, tr->rayorig) + d) / NdotRayDirection;
	// check if the triangle is in behind the ray
	///if (t < 0) return false; // the triangle is behind 
	if (t < 0)
	{
		free(v1v2);
		free(v1v3);
		free(C);
		return (0);
	}
	// compute the intersection point using equation 1
	///Vec3f P = orig + t * dir; 
	P = new_params_vec(tr->rayorig->x + *t * tr->raydir->x, tr->rayorig->y + *t * tr->raydir->y, tr->rayorig->z + *t * tr->raydir->z);
	// Step 2: inside-outside test
	///Vec3f C; // vector perpendicular to triangle's plane 

	// edge 0
	///Vec3f edge0 = v1 - v0; 
	edge1 = new_sub_params_vec(triangle->p2, triangle->p1);
	///Vec3f vp0 = P - v0; 
	vp1 = new_sub_params_vec(P, triangle->p1);
	///C = edge0.crossProduct(vp0); 
	cross_product(edge1, vp1, C);
	///if (N.dotProduct(C) < 0) return false; // P is on the right side 
	if (dot_product(tr->nhit, C) < 0)
	{
		free(v1v2);
		free(v1v3);
		free(C);
		free(edge1);
		free(vp1);
		free(P);


		return (0);

	}

	// edge 1
	///Vec3f edge1 = v2 - v1; 
	edge2 = new_sub_params_vec(triangle->p3, triangle->p2);
	///Vec3f vp1 = P - v1; 
	vp2 = new_sub_params_vec(P, triangle->p2);
	///C = edge1.crossProduct(vp1); 
	cross_product(edge2, vp2, C);

	///if (N.dotProduct(C) < 0)  return false; // P is on the right side 
	if (dot_product(tr->nhit, C) < 0)
	{
		free(v1v2);
		free(v1v3);
		free(C);
		free(edge1);
		free(vp1);
		free(P);	

		free(edge2);	
		free(vp2);	



		return (0);
	}

	// edge 2
	///Vec3f edge2 = v0 - v2; 
	edge3 = new_sub_params_vec(triangle->p1, triangle->p3);
	///Vec3f vp2 = P - v2; 
	vp3 = new_sub_params_vec(P, triangle->p3);
	///C = edge2.crossProduct(vp2); 
	cross_product(edge3, vp3, C);
	//if (N.dotProduct(C) < 0) return false; // P is on the right side; 
	if (dot_product(tr->nhit, C) < 0)
	{
		free(v1v2);
		free(v1v3);
		free(C);
		free(edge1);
		free(vp1);
		free(P);	

		free(edge2);	
		free(vp2);	
		free(edge3);
		free(vp3);
		return (0);
	}
	free(v1v2);
	free(v1v3);
	free(C);
	free(edge1);
	free(vp1);
	free(P);	

	free(edge2);	
	free(vp2);	
	free(edge3);
	free(vp3);



	return (1); // this ray hits the triangle`
}


int		intersect_spher(t_trace *dat, float *t0, float *t1, t_spher *sphere)
{
	t_vec	*l;
	float	tca;
	float	d2;
	float	thc;


	l = new_sub_params_vec(sphere->pos, dat->tmp_orig);
	//	printf("x = %f, y = %f, z = %f", l.x, l.y, l.z);
	//	printf("x = %f, y = %f, z = %f	", sphere->pos.x, sphere->pos.y, sphere->pos.z);
	//	printf("x = %f, y = %f, z = %f\n", raydir->x, raydir->y, raydir->z);
	tca = dot_product(l, dat->tmp_dir);
	//	printf("tca = %f", tca);
	if (tca < 0)
	{
		free(l);
		return (0);
	}
	d2 = dot_product(l, l) - tca * tca;
	if (d2 > sphere->pspher->radius * sphere->pspher->radius)
	{
		free(l);
		return (0);
	}
	thc = sqrt(sphere->pspher->radius * sphere->pspher->radius - d2);
	*t0 = tca - thc;
	*t1 = tca + thc;
	free(l);




	//	if (*t0 < 0)
	//			*t0 = *t1;

	//	push_params_vec(dat->tmp_orig->x + dat->tmp_dir->x * *t0, dat->tmp_orig->y + dat->tmp_dir->y * *t0, dat->tmp_orig->z + dat->tmp_dir->z * *t0, l);
	//	push_params_vec(l->x - dat->sphere->pos->x, l->y - dat->sphere->pos->y, l->z - dat->sphere->pos->z, dat->nhit);
	//	dat->inside = 0;
	//	if (dot_product(dat->tmp_dir, dat->nhit) > 0)
	//	{
	//		push_params_vec(-dat->nhit->x, -dat->nhit->y, -dat->nhit->z, dat->nhit);
	//		dat->inside = 1;
	//	}


	return (1);
}

float			mixitude(float x, float y, float a)
{
	//	return (y * a + x * (1 - a));
	return (x * (1 - a) + y * a);
}

double			powered(double nb, int power)
{
	double	tmp;

	tmp = nb;
	if (power < 0)
	{
		if (nb == 0)
			return (INFINITY);
		while (power <= 0)
		{
			tmp /= nb;
			power++;
		}
	}
	else if (power == 0)
		return (1.0);
	else
	{
		while (power > 1)
		{
			tmp *= nb;
			power--;
		}
	}
	return (tmp);
}

void		rm_trace(t_trace *ret)
{
	free(ret->surface_color);
	free(ret->phit);
	free(ret->nhit);
	free(ret->tmp_nhit);
	free(ret->refldir);
	free(ret->reflection);
	free(ret->refraction);
	free(ret->tmp_vec);
	free(ret->refrdir);
	free(ret->lum_inc);
	free(ret->normal);
	free(ret->obj_color);
	free(ret->tmp_orig);
	free(ret->tmp_dir);

	free(ret);


}



t_trace		*setup_trace(void)
{
	t_trace		*ret;

	if ((ret = (t_trace*)malloc(sizeof(*ret))) == 0)
		exit(-1);
	ret->inter = 0;
	ret->spher = 0;
	ret->sphere = 0;


	ret->tnear = INFINI;
	ret->surface_color = new_params_vec(0, 0, 0);
	ret->phit = new_params_vec(0, 0, 0);
	ret->nhit = new_params_vec(0, 0, 0);
	ret->tmp_nhit = new_params_vec(0, 0, 0);

	ret->refldir = new_params_vec(0, 0, 0);
	ret->reflection = new_params_vec(0, 0, 0);
	ret->refraction = new_params_vec(0, 0, 0);

	ret->tmp_vec = new_params_vec(0, 0, 0);
	ret->refrdir = new_params_vec(0, 0, 0);
	ret->lum_inc = new_params_vec(0, 0, 0);

	ret->normal = new_params_vec(0, 0, 0);

	ret->obj_color = new_params_vec(0,0,0);
	ret->tmp_orig = new_params_vec(0, 0, 0);
	ret->tmp_dir = new_params_vec(0, 0, 0);

	ret->depth = 0;

	return (ret);
}

void		setup_trace_test(t_trace *ret)
{
	//	t_trace		*ret;

	if ((ret = (t_trace*)malloc(sizeof(*ret))) == 0)
		exit(-1);
	ret->inter = 0;
	ret->spher = 0;
	ret->sphere = 0;


	ret->tnear = INFINI;
	ret->surface_color = new_params_vec(0, 0, 0);
	ret->phit = new_params_vec(0, 0, 0);
	ret->nhit = new_params_vec(0, 0, 0);


	ret->refldir = new_params_vec(0, 0, 0);
	ret->reflection = new_params_vec(0, 0, 0);
	ret->refraction = new_params_vec(0, 0, 0);

	ret->tmp_vec = new_params_vec(0, 0, 0);
	ret->refrdir = new_params_vec(0, 0, 0);
	ret->lum_inc = new_params_vec(0, 0, 0);

	ret->normal = new_params_vec(0, 0, 0);
	ret->tmp_orig = new_params_vec(0, 0, 0);
	ret->tmp_dir = new_params_vec(0, 0, 0);

	ret->depth = 0;

	//	return (ret);
}



void		reset_trace(t_trace *trace)
{
	trace->inter = 0;
	trace->spher = 0;
	trace->sphere = 0;
	trace->triangle = 0;

	trace->tnear = INFINI;
	push_params_vec(0, 0, 0, trace->surface_color);
	push_params_vec(0, 0, 0, trace->phit);
	push_params_vec(0, 0, 0, trace->nhit);


	push_params_vec(0, 0, 0, trace->refldir);
	push_params_vec(0, 0, 0, trace->reflection);
	push_params_vec(0, 0, 0, trace->refraction);



}


void	apply_color(t_vec *surface_color, t_vec *color)
{
	float r;
	float g;
	float b;

	r = surface_color->x;
	g = surface_color->y;
	b = surface_color->z;

	surface_color->x = (1-r) * color->x + r;
	surface_color->y = (1-g) * color->y + g;
	surface_color->z = (1-b) * color->z + b;
	//	printf("t########################### %f\n", r);

}

void	compute_color(t_trace *dat)
{
	float	refl; //(dat->sphere->pspher->refl)
	float	trans; //(dat->sphere->pspher->opac)
	float	col;
	float	refr[3];
	float	att;

	refl = dat->reflec / (dat->reflec + dat->trans + ((1 - dat->reflec) * (1 - dat->trans)));
	trans = dat->trans / (dat->reflec + dat->trans + ((1 - dat->reflec) * (1 - dat->trans)));
	col = ((1 - dat->reflec) * (1 - dat->trans)) / (dat->reflec + dat->trans + ((1 - dat->reflec) * (1 - dat->trans)));
	att = -10 * log10(dat->trans);
	if (att > 1)
		att = 1;
	refr[0] = dat->refraction->x * (1 - att) + dat->obj_color->x * dat->refraction->x * (att);
	refr[1] = dat->refraction->y * (1 - att) + dat->obj_color->y * dat->refraction->y * (att);
	refr[2] = dat->refraction->z * (1 - att) + dat->obj_color->z * dat->refraction->z * (att);
	dat->surface_color->x = dat->reflection->x * refl * (1-dat->fresneleffect) + refr[0] * trans * (1-(dat->fresneleffect / 10)) + dat->obj_color->x * col * dat->lum_inc->x * (1-dat->fresneleffect);
	dat->surface_color->y = dat->reflection->y * refl * (1-dat->fresneleffect) + refr[1] * trans * (1-(dat->fresneleffect / 10)) + dat->obj_color->y * col * dat->lum_inc->y * (1-dat->fresneleffect);
	dat->surface_color->z = dat->reflection->z * refl * (1-dat->fresneleffect) + refr[2] * trans * (1-(dat->fresneleffect / 10)) + dat->obj_color->z * col * dat->lum_inc->z * (1-dat->fresneleffect);
	/// AVEC OU SANS LE /10?   ///
}


void	compute_light(t_trace *dat, t_list *cpy_lst)
{
	t_list *list;
	t_list *tmp_lst;
	list = cpy_lst;
	t_vec *tmp_vec;
	float useless1;
	float useless2;
	t_vec *tmp_color;
	//	t_vec *obj_pos;
	t_vec *light_pos;
	t_vec *tmp;



	float att;
	//	float refr[3];
	float test_x;
	float test_y;
	float test_z;
	int		do_while;
	float	len;

	test_x = 0;
	test_y = 0;
	test_z = 0;

	light_pos = new_params_vec(0,0,0);
	//	obj_pos = new_params_vec(0,0,0);
	tmp_color = new_params_vec(0,0,0);
	tmp_vec = new_params_vec(0,0,0);
	tmp = new_params_vec(0,0,0);
	while(list)
	{



		dat->type = list->content;
		if (dat->type->name == 'S' || dat->type->name == 'L')
		{
			//	spher = type->obj;
			if (dat->type->name == 'S')
			{
				dat->lsphere = dat->type->obj;
				cpy_params_vec(dat->lsphere->color, tmp_color);
				//		cpy_params_vec(dat->lsphere->color, color_obj);


				cpy_params_vec(dat->lsphere->pos, light_pos);
				//		cpy_params_vec(dat->lsphere->pos, obj_pos);
				if (dat->lsphere->lpspher->type == 0)
				{
					len = sqrt((light_pos->x - dat->phit->x) * (light_pos->x - dat->phit->x) + (light_pos->y - dat->phit->y) * (light_pos->y - dat->phit->y) +
							(light_pos->z - dat->phit->z) * (light_pos->z - dat->phit->z));
				}
				//					tr->nhit->x + tr->nhit->y * tr->nhit->y + tr->nhit->z * tr->nhit->z);
				//			len = sqrt(tr->nhit->x * tr->nhit->x + tr->nhit->y * tr->nhit->y + tr->nhit->z * tr->nhit->z);


				mult_params_vec(tmp_color, dat->lsphere->lpspher->emi);
				do_while = 1; 
			}
			else if (dat->type->name == 'L')
			{
				dat->lproj = dat->type->obj;

				sub_params_vec(dat->lproj->pos, dat->phit, tmp_vec);

				normalize_vec(tmp_vec);

				cpy_params_vec(dat->lproj->pos, light_pos);
				//		cpy_params_vec(dat->lproj->pos, obj_pos);
				//rintf("vers le proj = x=%f y=%fz=%f\n", tmp_vec->x, tmp_vec->y, tmp_vec->z);
				//		printf("dir du proj = x=%f y=%f z=%f\n", dat->lproj->dir->x, dat->lproj->dir->y, dat->lproj->dir->z);
				if (dat->lproj->lpproj->type == 0)
				{
					len = sqrt((light_pos->x - dat->phit->x) * (light_pos->x - dat->phit->x) + (light_pos->y - dat->phit->y) * (light_pos->y - dat->phit->y) +
							(light_pos->z - dat->phit->z) * (light_pos->z - dat->phit->z));
				}
				cpy_params_vec(dat->lproj->color, tmp_color);
				//		cpy_params_vec(dat->lsphere->color, color_obj);
				mult_params_vec(tmp_color, dat->lproj->lpproj->emi);


				//		printf("couleur = x=%f y=%f z=%f\n", tmp_color->x, tmp_color->y, tmp_color->z);

				//		printf("angle angulaire = %f\n", dot_product(dat->lproj->dir, tmp_vec) );
				if ((dot_product(dat->lproj->dir, tmp_vec) + 1.) * 180. < dat->lproj->lpproj->fov)
				{
					//			printf("CA TOUCHE\n");
					do_while = 1;
				}
				else
				{
					//			printf("TOUCHE PAS\n");
					do_while = 0; 
				}

				//	do_while = 0; 

			}
			tmp_lst = cpy_lst;
			while(tmp_lst && do_while)
			{
				//					type = list->content;
				dat->type = tmp_lst->content;
				///		if (type->name == 's')
				if (dat->type->name == 's')
				{
					dat->spher = dat->type->obj;
					sub_params_vec(light_pos, dat->phit, tmp_vec);
					normalize_vec(tmp_vec);
					cpy_params_vec(tmp_vec, dat->tmp_dir);
					cpy_params_vec(dat->phit, dat->tmp_orig);

					push_params_vec(dat->tmp_orig->x + dat->tmp_dir->x * dat->bias,
							dat->tmp_orig->y + dat->tmp_dir->y * dat->bias,
							dat->tmp_orig->z + dat->tmp_dir->z * dat->bias, tmp);
					//
					cpy_params_vec(tmp, dat->tmp_orig);
					if (intersect_spher(dat, &useless1, &useless2, dat->spher))
					{
						att = -10 * log10(dat->spher->pspher->opac);
						if (att > 1)
							att = 1;
						tmp_color->x = tmp_color->x * (1 - att) + tmp_color->x * dat->spher->color->x * (att);
						tmp_color->y = tmp_color->y * (1 - att) + tmp_color->y * dat->spher->color->y * (att);
						tmp_color->z = tmp_color->z * (1 - att) + tmp_color->z * dat->spher->color->z * (att);
						mult_params_vec(tmp_color, dat->spher->pspher->opac / (dat->spher->pspher->refl + dat->spher->pspher->opac + ((1 - dat->spher->pspher->refl) * (1 - dat->spher->pspher->opac))));
					}
				}
				else if (dat->type->name == 't' && 1)
				{
					dat->triangl = dat->type->obj;
					sub_params_vec(light_pos, dat->phit, tmp_vec);
					normalize_vec(tmp_vec);
					cpy_params_vec(tmp_vec, dat->tmp_dir);
					cpy_params_vec(dat->phit, dat->tmp_orig);


					push_params_vec(dat->tmp_orig->x + dat->tmp_dir->x * dat->bias,
							dat->tmp_orig->y + dat->tmp_dir->y * dat->bias,
							dat->tmp_orig->z + dat->tmp_dir->z * dat->bias, tmp);

					//					push_params_vec(dat->tmp_orig->x - dat->tmp_dir->x * 1,
					//					dat->tmp_orig->y - dat->tmp_dir->y * 1,
					//					dat->tmp_orig->z - dat->tmp_dir->z * 1, tmp);


					cpy_params_vec(tmp, dat->tmp_orig);

					if (intersect_triangle(dat, &useless1, dat->triangl))
					{
						att = -10 * log10(dat->triangl->pbas->opac);
						if (att > 1)
							att = 1;
						tmp_color->x = tmp_color->x * (1 - att) + tmp_color->x * dat->triangl->color->x * (att);
						tmp_color->y = tmp_color->y * (1 - att) + tmp_color->y * dat->triangl->color->y * (att);
						tmp_color->z = tmp_color->z * (1 - att) + tmp_color->z * dat->triangl->color->z * (att);
						mult_params_vec(tmp_color, dat->triangl->pbas->opac / (dat->triangl->pbas->refl + dat->triangl->pbas->opac + ((1 - dat->triangl->pbas->refl) * (1 - dat->triangl->pbas->opac))));
					}
					//			printf("booo");
				}




				tmp_lst = tmp_lst->next;
			}
			if (do_while)
			{
				test_x += __exp10(tmp_color->x * 10);
				test_y += __exp10(tmp_color->y * 10);
				test_z += __exp10(tmp_color->z * 10);
			}
		}
		list = list->next;
	}
	dat->lum_inc->x = log10(test_x + 1) / 10;
	dat->lum_inc->y = log10(test_y + 1) / 10;
	dat->lum_inc->z = log10(test_z + 1) / 10;

	//	t_vec *tmp_color;
	//	t_vec *obj_pos;
	free(light_pos);
	free(tmp);





	free(tmp_color);
	free(tmp_vec);
}


void			trace_complex_obj(t_trace *dat)
{
	dat->ior = 1.1;
	if (dat->inside == 1)
		dat->eta = dat->ior;
	else
		dat->eta = 1 / dat->ior;
	dat->cosi = -dot_product(dat->nhit, dat->raydir);

	dat->k = (dat->cosi *dat->cosi);  ///////////////////////////////////////////////////////////////// BUG WAS HERE

	push_params_vec(dat->raydir->x * dat->eta + dat->nhit->x * (dat->eta * dat->cosi - sqrt(dat->k)),
			dat->raydir->y * dat->eta + dat->nhit->y * (dat->eta * dat->cosi - sqrt(dat->k)),
			dat->raydir->z * dat->eta + dat->nhit->z * (dat->eta * dat->cosi - sqrt(dat->k)), dat->refrdir);
	normalize_vec(dat->refrdir);





}




t_vec	*trace( int depth, t_list *list, t_trace *dat)
{
	t_list	*cpy_lst;

	reset_trace(dat);

	dat->lumiere_inc = 0;
	push_params_vec(0, 0, 0, dat->tmp_vec);
	cpy_lst = list;
	while (list)
	{
		dat->t0 = INFINI;
		dat->t1 = INFINI;
		dat->type = list->content;
		if (dat->type->name == 's')
		{
			dat->spher = dat->type->obj;
			cpy_params_vec(dat->rayorig, dat->tmp_orig);
			cpy_params_vec(dat->raydir, dat->tmp_dir);
			if (intersect_spher(dat,  &dat->t0, &dat->t1, dat->spher))
			{
				//inter = 1;
				if (dat->t0 < 0)
					dat->t0 = dat->t1;
				if (dat->t0 < dat->tnear)
				{
					dat->inter = 2;
					//tnear = t0;
					dat->tnear = dat->t0;
					//sphere = spher;
					dat->sphere = dat->spher;
					dat->triangle = 0;
					dat->reflec = dat->sphere->pspher->refl;
					dat->trans = dat->sphere->pspher->opac;
					cpy_params_vec(dat->sphere->color,dat->obj_color);

					push_params_vec(dat->tmp_orig->x + dat->tmp_dir->x * dat->tnear, dat->tmp_orig->y + dat->tmp_dir->y * dat->tnear, dat->tmp_orig->z + dat->tmp_dir->z * dat->tnear, dat->phit);
					push_params_vec(dat->phit->x - dat->sphere->pos->x, dat->phit->y - dat->sphere->pos->y, dat->phit->z - dat->sphere->pos->z, dat->nhit);
					dat->inside = 0;
					if (dot_product(dat->tmp_dir, dat->nhit) > 0)
					{
						push_params_vec(-dat->nhit->x, -dat->nhit->y, -dat->nhit->z, dat->nhit);
						dat->inside = 1;
					}



				}
			}
		}
		if (dat->type->name == 't')
		{
			dat->triangl = dat->type->obj;
			cpy_params_vec(dat->rayorig, dat->tmp_orig);
			cpy_params_vec(dat->raydir, dat->tmp_dir);


			if (intersect_triangle(dat, &dat->t, dat->triangl))
			{

				if (dat->t < dat->tnear)
				{
					dat->tnear = dat->t;
					dat->inter = 1;
					dat->triangle = dat->triangl;
					dat->sphere = 0;
					dat->reflec = dat->triangle->pbas->refl;
					dat->trans = dat->triangle->pbas->opac;
					cpy_params_vec(dat->tmp_nhit, dat->nhit);
					cpy_params_vec(dat->triangle->color,dat->obj_color);
					push_params_vec(dat->rayorig->x + dat->raydir->x * dat->tnear, dat->rayorig->y + dat->raydir->y * dat->tnear, dat->rayorig->z + dat->raydir->z * dat->tnear, dat->phit);
				}

			}
		}

		list = list->next;
	}
	if (!dat->sphere && !dat->triangle)
	{
		push_params_vec(0, 0, 0, dat->surface_color);
		return (0);
	}

	if (dat->inter)// && dat->sphere)
	{

		normalize_vec(dat->nhit);
		dat->bias = 0.0001;
		if ((dat->trans >= 0 || dat->reflec >= 0) && dat->depth < MAX_RAY_DEPTH)
		{
			//		facingratio = -dot_product(raydir, nhit);
			dat->facingratio = -dot_product(dat->raydir, dat->nhit);

			//		fresneleffect = mixitude(powered(1 - facingratio, 3), 1, 0.1);
			dat->fresneleffect = mixitude(powered(1 - dat->facingratio, 3), 1, 0.1);

			push_params_vec(dat->raydir->x - dat->nhit->x * 2 * dot_product(dat->raydir, dat->nhit),
					dat->raydir->y - dat->nhit->y * 2 * dot_product(dat->raydir, dat->nhit),
					dat->raydir->z - dat->nhit->z * 2 * dot_product(dat->raydir, dat->nhit), dat->refldir);

			normalize_vec(dat->refldir);
			dat->tmp_refl	 = setup_trace();
			dat->tmp_refl->depth = dat->depth + 1;
			push_params_vec(dat->phit->x + dat->nhit->x * dat->bias,
					dat->phit->y + dat->nhit->y * dat->bias,
					dat->phit->z + dat->nhit->z * dat->bias, dat->tmp_vec);
			dat->tmp_refl->rayorig = dat->tmp_vec;
			dat->tmp_refl->raydir = dat->refldir;
			trace(depth, cpy_lst, dat->tmp_refl);
			push_params_vec(dat->tmp_refl->surface_color->x, dat->tmp_refl->surface_color->y, dat->tmp_refl->surface_color->z, dat->reflection);
			push_params_vec(0, 0, 0, dat->refraction);
			if (dat->trans)
			{
				if (dat->inter == 2)
					trace_complex_obj(dat);
				else
					cpy_params_vec(dat->raydir, dat->refrdir);
				dat->tmp_refr = setup_trace();
				dat->tmp_refr->depth = dat->depth + 1;
				push_params_vec(dat->phit->x - dat->nhit->x * dat->bias,
						dat->phit->y - dat->nhit->y * dat->bias,
						dat->phit->z - dat->nhit->z * dat->bias, dat->tmp_vec);
				dat->tmp_refr->rayorig = dat->tmp_vec;
				dat->tmp_refr->raydir = dat->refrdir;
				trace(depth, cpy_lst, dat->tmp_refr);
				push_params_vec(dat->tmp_refr->surface_color->x, dat->tmp_refr->surface_color->y, dat->tmp_refr->surface_color->z, dat->refraction);
				rm_trace(dat->tmp_refr);

			}
			compute_light(dat, cpy_lst);
			compute_color(dat);
			rm_trace(dat->tmp_refl);

		}
	}
	return (0);
}

void	test_list(t_list *list)
{
	t_spher *sphere;
	int		i;
	t_type	*type;
	t_lspher *lsphere;

	i = 0;
	while (list)
	{

		sphere = (t_spher*)list->content;
		sphere = 0;
		lsphere = 0;
		if (list->content)
			type = list->content;
		if (type->name == 's')
			sphere = type->obj;
		else if (type->name == 'S')
			lsphere = type->obj;
		if (sphere)
		{
			printf("pos:  x= %f, y = %f, z = %f\n", sphere->pos->x, sphere->pos->y, sphere->pos->z);
			printf("color:  r= %f, g = %f, b = %f\n", sphere->color->x, sphere->color->y, sphere->color->z);
			printf("radius = %f, refl = %f, opac = %f\n", sphere->pspher->radius, sphere->pspher->refl, sphere->pspher->opac);
		}
		else if (lsphere)
		{
			printf("pos:  x= %f, y = %f, z = %f\n", lsphere->pos->x, lsphere->pos->y, lsphere->pos->z);
			printf("color:  r= %f, g = %f, b = %f\n", lsphere->color->x, lsphere->color->y, lsphere->color->z);
			printf("radius = %f, EMI = %f\n", lsphere->lpspher->radius, lsphere->lpspher->emi);
		}





		list = list->next;
	}
}



void	test_void(void *vo)
{
	t_spher *sphere;
	int		i;
	sphere = vo;
	i = 0;
	while (i < 10000)
	{
		//		printf("x = %f, y = %f, z = %f\n", sphere->ps->radius, sphere->ps->refl, sphere->ps->trans);
		i++;
	}
}
void	*sphere_to_void(t_spher *sphere)
{
	void	*ret;
	//	ret = (void*)malloc(sizeof(void*));
	ret = sphere;

	test_void(ret);
	return (ret);
}

void	test_img(t_win *win)
{
	int		x;
	int		y;

	x = 0;
	y = 0;
	while (x < win->x_win)
	{
		while (y < win->y_win)
		{
			img_add_px2(win, 0xff00ff, x, y);
			y++;
		}
		y = 0;
		x++;
	}
}

t_list	*ft_lstnew_2(t_spher *content, size_t content_size)
{
	t_list	*new;

	new = NULL;
	if ((new = (t_list*)malloc(sizeof(t_list))) == NULL)
		return (NULL);
	if (content)
	{
		new->content = content;
		new->content_size = content_size;
	}
	else
	{
		new->content = NULL;
		new->content_size = 0;
	}
	new->next = NULL;
	return (new);
}

void	ft_lstadd_2(t_list **last, t_list *elem)
{
	t_list	*old;

	old = *last;
	*last = elem;
	elem->next = old;
}




void	render(t_win *win, t_list *list)
{
	unsigned int	width;
	unsigned int	height;
	unsigned int	y;
	unsigned int	x;
	float			yy;
	float			xx;
	float			invWidth;
	float			invHeight;
	float			fov;
	float			aspectratio;
	float			angle;
	t_vec			*raydir;
	t_vec			*rayorig;
	t_trace			*datrace;

	raydir = new_params_vec(0, 0, 0);
	rayorig = new_params_vec(0, 0, 0);
	width = win->x_img;
	height = win->y_img;
	invWidth = 1.0 / (float)width;
	invHeight = 1.0 / (float)height;
	fov = 30;
	aspectratio = (float)width / (float)height;
	angle = tan(M_PI * 0.5 * fov / 180.);
	y = 0;

	datrace = setup_trace();
	while (y < height)
	{
		if (y == 55 && 0)
		{
			test_img(win);
			mlx_put_image_to_window(win->mlx, win->win,	win->img2, 0, 0);

			mlx_loop(win->mlx);
		}
		x = 0;
		while (x < width)
		{
			xx = (2 * ((x + 0.5) * invWidth) - 1) * angle * aspectratio;
			yy = (1 - 2 * ((y + 0.5) * invHeight)) * angle;
			push_params_vec(xx, yy, -1, raydir);
			reset_trace(datrace);
			//		push_params_vec(xx, yy, -1, datrace->raydir);
			//		printf("x = %f, y = %f, z = %f	", raydir.x, raydir.y, raydir.z);
			normalize_vec(raydir);

			//	img_add_px(win, vec_to_color(new_params_vec(0.22, (float)y / (float)Y_WIN ,(float)x / (float)X_WIN)), x, y);

			img_add_px(win, vec_to_color(trace(0, list, datrace)), x, y);
			x++;
		}
		y++;
	}
}





void	apply_autoauto(t_win *mlx)
{
	int				x;
	int				y;
	//	unsigned int	r;
	//	unsigned int	g;
	//	unsigned int	b;
	unsigned int	color;
	int				x2;
	int				y2;

	x = 0;
	y = 0;
	//	r = 0;
	//	g = 0;
	//	b = 0;
	x2 = 0;
	y2 = 0;
	color = 0;
	while (y2 < mlx->y_win)
	{
		while (x2 < mlx->x_win)
		{
			//		r  = img_get_px(mlx, x)
			color = 0;
			x = x2 / 2 * 4 + x2 % 2;

			y = y2 / 2 * 4 + y2 % 2;
			color = (unsigned char)mlx->addr[(y * mlx->sizeline + x * mlx->bpp / 8)];



			//	color =0xff;

			color += (unsigned char)mlx->addr[(y * mlx->sizeline + x * mlx->bpp / 8) + 1] * 256;

			color += (unsigned char)mlx->addr[(y * mlx->sizeline + x * mlx->bpp / 8) + 2] * 256 * 256;
			//	color = img_get_px(mlx, x, y);
			img_add_px3(mlx, color, x2, y2);
			//	printf("COOOLEOEOENF %x\n", color);

			x2++;
		}
		x2 = 0;
		y2++;
	}


}

void	apply_filling_p3(t_win *mlx, t_phase *p)
{
	int				x;
	int				y;
	//	unsigned int	r;
	//	unsigned int	g;
	//	unsigned int	b;
	unsigned int	color;
	int				x2;
	int				y2;
	int				tmp_z;

	x = 0;
	y = 0;

	x2 = 0;
	y2 = 0;
	color = 0;
	tmp_z = 0;
	//	tmp_z = (X_WIN + 0) * (Y_WIN + 0);
	//	ft_putstr("booouuu\n");
	tmp_z =  ((mlx->x_win) * (mlx->y_win) / 3);

	//	printf("fewffewfwe few ew ew= = ew= %d\n",  ((X_WIN) * (Y_WIN) / 4));
	//	tmp_z =  ((X_IMG + 1) * (Y_IMG + 1) / 16);
	while (y2 < mlx->y_win && tmp_z * 3 < p->z)// - (X_WIN / 4) * (Y_WIN / 4))
	{
		//		ft_putstr("dooouuu\n");
		while (x2 < mlx->x_win && tmp_z * 3 < p->z)// - (X_WIN / 4) * (X_WIN / 4))
		{



			color = 0;
			x = x2 * 2;

			y = y2 * 2;
			color = ((unsigned char)mlx->addr[(y * mlx->sizeline + x * mlx->bpp / 8)]
					+ (unsigned char)mlx->addr[(y * mlx->sizeline + (x + 1) * mlx->bpp / 8)]
					+ (unsigned char)mlx->addr[((y + 1) * mlx->sizeline + x * mlx->bpp / 8)]
					+ (unsigned char)mlx->addr[((y + 1) * mlx->sizeline + (x + 1) * mlx->bpp / 8)]) / 4;


			//	color =0xff;

			color += ((unsigned char)mlx->addr[(y * mlx->sizeline + x * mlx->bpp / 8) + 1]
					+ (unsigned char)mlx->addr[(y * mlx->sizeline + (x + 1) * mlx->bpp / 8) + 1]
					+ (unsigned char)mlx->addr[((y + 1) * mlx->sizeline + x * mlx->bpp / 8) + 1]
					+ (unsigned char)mlx->addr[((y + 1) * mlx->sizeline + (x + 1) * mlx->bpp / 8) + 1]) / 4 * 256;


			color += ((unsigned char)mlx->addr[(y * mlx->sizeline + x * mlx->bpp / 8) + 2]
					+ (unsigned char)mlx->addr[(y * mlx->sizeline + (x + 1) * mlx->bpp / 8) + 2]
					+ (unsigned char)mlx->addr[((y + 1) * mlx->sizeline + x * mlx->bpp / 8) + 2]
					+ (unsigned char)mlx->addr[((y + 1) * mlx->sizeline + (x + 1) * mlx->bpp / 8) + 2]) / 4 * 256 * 256;
			//	color = img_get_px(mlx, x, y);
			img_add_px3(mlx, color, x2, y2);


			tmp_z++;








			x2++;
		}
		x2 = 0;
		y2++;
	}
}



void	apply_filling_p2(t_win *mlx, t_phase *p)
{
	int				x;
	int				y;
	//	unsigned int	r;
	//	unsigned int	g;
	//	unsigned int	b;
	unsigned int	color;
	int				x2;
	int				y2;
	int				tmp_z;

	x = 0;
	y = 0;

	x2 = 0;
	y2 = 0;
	color = 0;
	tmp_z = 0;
	//	tmp_z = (X_WIN + 0) * (Y_WIN + 0);
	//	ft_putstr("booouuu\n");
	tmp_z =  ((mlx->x_win) * (mlx->y_win) / 4);

	//	printf("fewffewfwe few ew ew= = ew= %d\n",  ((X_WIN) * (Y_WIN) / 4));
	//	tmp_z =  ((X_IMG + 1) * (Y_IMG + 1) / 16);
	while (y2 < mlx->y_win && tmp_z  < p->z)// - (X_WIN / 4) * (Y_WIN / 4))
	{
		//		ft_putstr("dooouuu\n");
		while (x2 < mlx->x_win && tmp_z  < p->z)// - (X_WIN / 4) * (X_WIN / 4))
		{

			//		ft_putstr("POUOUUuuu\n");
			//		r  = img_get_px(mlx, x)
			color = 0;
			//x = x2 / 2 * 4;

			x = x2 / 2 * 4 + x2 % 2;

			y = y2 / 2 * 4 + y2 % 2;
			//	y = y2 / 2 * 4;

			if (x % 4 >= 1  || y % 4 >= 1)
			{

				//	ft_putstr("POUOUUuuu\n");
				color = (unsigned char)mlx->addr[(y * mlx->sizeline + x * mlx->bpp / 8)];



				//	color =0xff;

				color += (unsigned char)mlx->addr[(y * mlx->sizeline + x * mlx->bpp / 8) + 1] * 256;

				color += (unsigned char)mlx->addr[(y * mlx->sizeline + x * mlx->bpp / 8) + 2] * 256 * 256;
				//	color = img_get_px(mlx, x, y);
				img_add_px3(mlx, color, x2, y2);
				//	printf("COOOLEOEOENF %x\n", color);

				tmp_z++;
			}

			x2++;
		}
		x2 = 0;
		y2++;
	}
}

void	apply_filling_p1(t_win *mlx, t_phase *p)
{
	int				x;
	int				y;
	//	unsigned int	r;
	//	unsigned int	g;
	//	unsigned int	b;
	unsigned int	color;
	int				x2;
	int				y2;
	int				tmp_z;

	x = 0;
	y = 0;

	x2 = 0;
	y2 = 0;
	color = 0;
	tmp_z = 0;
	//	tmp_z = (X_WIN + 0) * (Y_WIN + 0);
	//	ft_putstr("booouuu\n");
	tmp_z =  ((mlx->x_win) * (mlx->y_win) / 4);

	//	printf("fewffewfwe few ew ew= = ew= %d\n",  ((X_WIN) * (Y_WIN) / 4));
	//	tmp_z =  ((X_IMG + 1) * (Y_IMG + 1) / 16);
	while (y2 < mlx->y_win && tmp_z / 4 < p->z)// - (X_WIN / 4) * (Y_WIN / 4))
	{
		//		ft_putstr("dooouuu\n");
		while (x2 < mlx->x_win && tmp_z / 4 < p->z)// - (X_WIN / 4) * (X_WIN / 4))
		{
			//		r  = img_get_px(mlx, x)
			color = 0;
			x = x2 / 2 * 4;

			y = y2 / 2 * 4;

			if (x % 8 != 0  || y % 8 != 0)
			{
				color = (unsigned char)mlx->addr[(y * mlx->sizeline + x * mlx->bpp / 8)];



				//	color =0xff;

				color += (unsigned char)mlx->addr[(y * mlx->sizeline + x * mlx->bpp / 8) + 1] * 256;

				color += (unsigned char)mlx->addr[(y * mlx->sizeline + x * mlx->bpp / 8) + 2] * 256 * 256;
				//	color = img_get_px(mlx, x, y);
				img_add_px3(mlx, color, x2, y2);
				//	printf("COOOLEOEOENF %x\n", color);

				tmp_z++;
			}

			x2++;
		}
		x2 = 0;
		y2++;
	}
}

void	apply_filling_p0(t_win *mlx, t_phase *p)
{
	int				x;
	int				y;
	//	unsigned int	r;
	//	unsigned int	g;
	//	unsigned int	b;
	unsigned int	color;
	int				x2;
	int				y2;
	int				tmp_z;

	x = 0;
	y = 0;

	x2 = 0;
	y2 = 0;
	color = 0;
	tmp_z = 0;
	while (y2 < mlx->y_win && tmp_z / 16 < p->z)
	{
		while (x2 < mlx->x_win && tmp_z / 16 < p->z)
		{
			//		r  = img_get_px(mlx, x)
			color = 0;
			x = x2 / 4 * 8;

			y = y2 / 4 * 8;
			color = (unsigned char)mlx->addr[(y * mlx->sizeline + x * mlx->bpp / 8)];



			//	color =0xff;

			color += (unsigned char)mlx->addr[(y * mlx->sizeline + x * mlx->bpp / 8) + 1] * 256;

			color += (unsigned char)mlx->addr[(y * mlx->sizeline + x * mlx->bpp / 8) + 2] * 256 * 256;
			//	color = img_get_px(mlx, x, y);
			img_add_px3(mlx, color, x2, y2);
			//	printf("COOOLEOEOENF %x\n", color);
			tmp_z++;
			x2++;
		}
		x2 = 0;
		y2++;
	}
	//	printf("tmp_MAAAXXX %d\n", tmp_z);
}


void	apply_autofill(t_win *mlx)
{
	int				x;
	int				y;
	//	unsigned int	r;
	//	unsigned int	g;
	//	unsigned int	b;
	unsigned int	color;
	int				x2;
	int				y2;

	x = 0;
	y = 0;
	//	r = 0;
	//	g = 0;
	//	b = 0;
	x2 = 0;
	y2 = 0;
	color = 0;
	while (y2 < mlx->y_win)
	{
		while (x2 < mlx->x_win)
		{
			//		r  = img_get_px(mlx, x)
			color = 0;
			x = x2 / 2 * 4;

			y = y2 / 2 * 4;
			color = (unsigned char)mlx->addr[(y * mlx->sizeline + x * mlx->bpp / 8)];



			//	color =0xff;

			color += (unsigned char)mlx->addr[(y * mlx->sizeline + x * mlx->bpp / 8) + 1] * 256;

			color += (unsigned char)mlx->addr[(y * mlx->sizeline + x * mlx->bpp / 8) + 2] * 256 * 256;
			//	color = img_get_px(mlx, x, y);
			img_add_px3(mlx, color, x2, y2);
			//	printf("COOOLEOEOENF %x\n", color);

			x2++;
		}
		x2 = 0;
		y2++;
	}
}

void	apply_antiaaaliasing(t_win *mlx)
{
	int				x;
	int				y;
	//	unsigned int	r;
	//	unsigned int	g;
	//	unsigned int	b;
	unsigned int	color;
	int				x2;
	int				y2;

	x = 0;
	y = 0;
	//	r = 0;
	//	g = 0;
	//	b = 0;
	x2 = 0;
	y2 = 0;
	color = 0;
	while (y2 < mlx->y_win)
	{
		while (x2 < mlx->x_win)
		{
			//		r  = img_get_px(mlx, x)
			color = 0;
			x = x2 * 2;

			y = y2 * 2;
			color = ((unsigned char)mlx->addr[(y * mlx->sizeline + x * mlx->bpp / 8)]
					+ (unsigned char)mlx->addr[(y * mlx->sizeline + (x + 1) * mlx->bpp / 8)]
					+ (unsigned char)mlx->addr[((y + 1) * mlx->sizeline + x * mlx->bpp / 8)]
					+ (unsigned char)mlx->addr[((y + 1) * mlx->sizeline + (x + 1) * mlx->bpp / 8)]) / 4;


			//	color =0xff;

			color += ((unsigned char)mlx->addr[(y * mlx->sizeline + x * mlx->bpp / 8) + 1]
					+ (unsigned char)mlx->addr[(y * mlx->sizeline + (x + 1) * mlx->bpp / 8) + 1]
					+ (unsigned char)mlx->addr[((y + 1) * mlx->sizeline + x * mlx->bpp / 8) + 1]
					+ (unsigned char)mlx->addr[((y + 1) * mlx->sizeline + (x + 1) * mlx->bpp / 8) + 1]) / 4 * 256;


			color += ((unsigned char)mlx->addr[(y * mlx->sizeline + x * mlx->bpp / 8) + 2]
					+ (unsigned char)mlx->addr[(y * mlx->sizeline + (x + 1) * mlx->bpp / 8) + 2]
					+ (unsigned char)mlx->addr[((y + 1) * mlx->sizeline + x * mlx->bpp / 8) + 2]
					+ (unsigned char)mlx->addr[((y + 1) * mlx->sizeline + (x + 1) * mlx->bpp / 8) + 2]) / 4 * 256 * 256;
			//	color = img_get_px(mlx, x, y);
			img_add_px3(mlx, color, x2, y2);
			//	printf("COOOLEOEOENF %x\n", color);

			x2++;
		}
		x2 = 0;
		y2++;
	}


}


void	test_color()
{
	//	printf("COLOR = ");







}

int	rt_close(void)
{
	exit(0);
	return (0);
}


int			key_hook(int keycode, t_super *super)
{
	if (keycode == 53 || keycode == 17)
		exit(0);
	if (keycode == 15)
	{
		system("./rtv1 template.rtv1.1&");
	}
	printf("touche : %d\n", keycode);
	return (0);
}

void		setup_thread(t_thread *thread)
{
	//	if ((thread->trace = (t_trace*)malloc(sizeof(*thread->trace))) == NULL)
	//		exit(0);
	if ((thread->render = (t_render*)malloc(sizeof(*thread->render))) == NULL)
		exit(0);
	thread->render->raydir = new_params_vec(0, 0, 0);
	thread->render->rayorig = new_params_vec(0, 0, 0);







}

t_super		*setup_super(void)
{
	t_super *super;
	int		i;

	if ((super = (t_super*)malloc(sizeof(*super))) == NULL)
		exit(0);
	if ((super->thread_1 = (t_thread*)malloc(sizeof(*super->thread_1))) == NULL)
		exit(0);
	//	if ((super->thread_2 = (t_thread*)malloc(sizeof(*super->thread_2))) == NULL)
	//		exit(0);
	//	if ((super->thread_3 = (t_thread*)malloc(sizeof(*super->thread_3))) == NULL)
	//		exit(0);
	//	if ((super->thread_4 = (t_thread*)malloc(sizeof(*super->thread_4))) == NULL)
	//		exit(0);

	i = 0;
	//	if ((super->thread = (t_thread**)malloc(sizeof(*super->thread) * THREADS)) == NULL)
	//		exit(0);

	while (i < THREADS)
	{
		if ((super->thread[i] = (t_thread*)malloc(sizeof(*super->thread[i]))) == NULL)
			exit(0);
		setup_thread(super->thread[i]);
		i++;
	}


	if ((super->phase = (t_phase*)malloc(sizeof(*super->phase))) == NULL)
		exit(0);


	setup_thread(super->thread_1);
	//	setup_thread(super->thread_2);
	//
	//	setup_thread(super->thread_3);
	//	setup_thread(super->thread_4);




	//	if ((super->trace = (t_trace*)malloc(sizeof(*super->trace))) == NULL)
	//		exit(0);
	//	if ((super->render = (t_render*)malloc(sizeof(*super->render))) == NULL)
	//		exit(0);
	if ((super->win = (t_win*)malloc(sizeof(*super->win))) == NULL)
		exit(0);


	//	super->render->raydir = new_params_vec(0, 0, 0);
	//	super->render->rayorig = new_params_vec(0, 0, 0);
	super->phase->state = 1;



	return (super);
}

void		setup_super_test(t_super **sup)
{
	int		i;
	t_super *super;
	super = *sup;

	//	if ((super = (t_super*)malloc(sizeof(*super))) == NULL)
	//		exit(0);
	//	if ((super->thread_1 = (t_thread*)malloc(sizeof(*super->thread_1))) == NULL)
	//		exit(0);
	//	if ((super->thread_2 = (t_thread*)malloc(sizeof(*super->thread_2))) == NULL)
	//		exit(0);
	//	if ((super->thread_3 = (t_thread*)malloc(sizeof(*super->thread_3))) == NULL)
	//		exit(0);
	//	if ((super->thread_4 = (t_thread*)malloc(sizeof(*super->thread_4))) == NULL)
	//		exit(0);

	i = 0;
	while (i < THREADS)
	{
		if ((super->thread[i] = (t_thread*)malloc(sizeof(*super->thread[i]))) == NULL)
			exit(0);
		setup_thread(super->thread[i]);
		i++;
	}


	if ((super->phase = (t_phase*)malloc(sizeof(*super->phase))) == NULL)
		exit(0);
	//	if ((super->phase->getcoor = (unsigned int *)malloc(sizeof(int) * ((X_IMG + 2) * (Y_IMG + 2)))) == NULL)
	//		exit(0);

	//	setup_thread(super->thread_1);
	//	setup_thread(super->thread_2);
	//
	//	setup_thread(super->thread_3);
	//	setup_thread(super->thread_4);




	//	if ((super->trace = (t_trace*)malloc(sizeof(*super->trace))) == NULL)
	//		exit(0);
	//	if ((super->render = (t_render*)malloc(sizeof(*super->render))) == NULL)
	//		exit(0);
	if ((super->win = (t_win*)malloc(sizeof(*super->win))) == NULL)
		exit(0);


	//	super->render->raydir = new_params_vec(0, 0, 0);
	//	super->render->rayorig = new_params_vec(0, 0, 0);
	super->phase->state = 1;



}


void	print_percent2(t_win *win, float percent)
{
	int		conv_int;

	conv_int = percent * 1000;
	//	if (conv_int / 100 == 0)
	//		mlx_string_put(win->mlx, win->win, X_WIN / 2 - 20, Y_WIN / 2 - 40, 0xffffff, "0");
	if (conv_int / 100 == 1)
		mlx_string_put(win->mlx, win->win, win->x_win / 2 - 20, 0, 0xffffff, "1");
	else if (conv_int / 100 == 2)
		mlx_string_put(win->mlx, win->win, win->x_win / 2 - 20, 0, 0xffffff, "2");
	else if (conv_int / 100 == 3)
		mlx_string_put(win->mlx, win->win, win->x_win / 2 - 20, 0, 0xffffff, "3");
	else if (conv_int / 100 == 4)
		mlx_string_put(win->mlx, win->win, win->x_win / 2 - 20, 0, 0xffffff, "4");
	else if (conv_int / 100 == 5)
		mlx_string_put(win->mlx, win->win, win->x_win / 2 - 20, 0, 0xffffff, "5");
	else if (conv_int / 100 == 6)
		mlx_string_put(win->mlx, win->win, win->x_win / 2 - 20, 0, 0xffffff, "6");
	else if (conv_int / 100 == 7)
		mlx_string_put(win->mlx, win->win, win->x_win / 2 - 20, 0, 0xffffff, "7");
	else if (conv_int / 100 == 8)
		mlx_string_put(win->mlx, win->win, win->x_win / 2 - 20, 0, 0xffffff, "8");
	else if (conv_int / 100 == 9)
		mlx_string_put(win->mlx, win->win, win->x_win / 2 - 20, 0, 0xffffff, "9");
	else if (conv_int / 100 == 10)
	{
		mlx_string_put(win->mlx, win->win, win->x_win / 2 - 20, 0, 0xffffff, "0");
		mlx_string_put(win->mlx, win->win, win->x_win / 2 - 30, 0, 0xffffff, "1");
	}

	if (conv_int / 10 % 10 == 0)
		mlx_string_put(win->mlx, win->win, win->x_win / 2 - 10, 0, 0xffffff, "0");
	else if (conv_int / 10 % 10 == 1)
		mlx_string_put(win->mlx, win->win, win->x_win / 2 - 10, 0, 0xffffff, "1");
	else if (conv_int / 10 % 10 == 2)
		mlx_string_put(win->mlx, win->win, win->x_win / 2 - 10, 0, 0xffffff, "2");
	else if (conv_int / 10 % 10 == 3)
		mlx_string_put(win->mlx, win->win, win->x_win / 2 - 10, 0, 0xffffff, "3");
	else if (conv_int / 10 % 10 == 4)
		mlx_string_put(win->mlx, win->win, win->x_win / 2 - 10, 0, 0xffffff, "4");
	else if (conv_int / 10 % 10 == 5)
		mlx_string_put(win->mlx, win->win, win->x_win / 2 - 10, 0, 0xffffff, "5");
	else if (conv_int / 10 % 10 == 6)
		mlx_string_put(win->mlx, win->win, win->x_win / 2 - 10, 0, 0xffffff, "6");
	else if (conv_int / 10 % 10 == 7)
		mlx_string_put(win->mlx, win->win, win->x_win / 2 - 10, 0, 0xffffff, "7");
	else if (conv_int / 10 % 10 == 8)
		mlx_string_put(win->mlx, win->win, win->x_win / 2 - 10, 0, 0xffffff, "8");
	else if (conv_int / 10 % 10 == 9)
		mlx_string_put(win->mlx, win->win, win->x_win / 2 - 10, 0, 0xffffff, "9");




	mlx_string_put(win->mlx, win->win, win->x_win / 2 , 0, 0xffffff, ".");
	if (conv_int % 10 == 0)
		mlx_string_put(win->mlx, win->win, win->x_win / 2 + 10 , 0, 0xffffff, "0");
	else if (conv_int % 10 == 1)
		mlx_string_put(win->mlx, win->win, win->x_win / 2 + 10 , 0, 0xffffff, "1");
	else if (conv_int % 10 == 2)
		mlx_string_put(win->mlx, win->win, win->x_win / 2 + 10 , 0, 0xffffff, "2");
	else if (conv_int % 10 == 3)
		mlx_string_put(win->mlx, win->win, win->x_win / 2 + 10 , 0, 0xffffff, "3");
	else if (conv_int % 10 == 4)
		mlx_string_put(win->mlx, win->win, win->x_win / 2 + 10 , 0, 0xffffff, "4");
	else if (conv_int % 10 == 5)
		mlx_string_put(win->mlx, win->win, win->x_win / 2 + 10 , 0, 0xffffff, "5");
	else if (conv_int % 10 == 6)
		mlx_string_put(win->mlx, win->win, win->x_win / 2 + 10 , 0, 0xffffff, "6");
	else if (conv_int % 10 == 7)
		mlx_string_put(win->mlx, win->win, win->x_win / 2 + 10 , 0, 0xffffff, "7");
	else if (conv_int % 10 == 8)
		mlx_string_put(win->mlx, win->win, win->x_win / 2 + 10 , 0, 0xffffff, "8");
	else if (conv_int % 10 == 9)
		mlx_string_put(win->mlx, win->win, win->x_win / 2 + 10 , 0, 0xffffff, "9");
	mlx_string_put(win->mlx, win->win, win->x_win / 2 + 20 ,  0, 0xffffff, "%");

}



void	print_percent(t_win *win, float percent)
{
	int		conv_int;

	conv_int = percent * 1000;
	//	if (conv_int / 100 == 0)
	//		mlx_string_put(win->mlx, win->win, X_WIN / 2 - 20, Y_WIN / 2 - 40, 0xffffff, "0");
	if (conv_int / 100 == 1)
		mlx_string_put(win->mlx, win->win, win->x_win / 2 - 20, win->y_win / 2 - 40, 0xffffff, "1");
	else if (conv_int / 100 == 2)
		mlx_string_put(win->mlx, win->win, win->x_win / 2 - 20, win->y_win / 2 - 40, 0xffffff, "2");
	else if (conv_int / 100 == 3)
		mlx_string_put(win->mlx, win->win, win->x_win / 2 - 20, win->y_win / 2 - 40, 0xffffff, "3");
	else if (conv_int / 100 == 4)
		mlx_string_put(win->mlx, win->win, win->x_win / 2 - 20, win->y_win / 2 - 40, 0xffffff, "4");
	else if (conv_int / 100 == 5)
		mlx_string_put(win->mlx, win->win, win->x_win / 2 - 20, win->y_win / 2 - 40, 0xffffff, "5");
	else if (conv_int / 100 == 6)
		mlx_string_put(win->mlx, win->win, win->x_win / 2 - 20, win->y_win / 2 - 40, 0xffffff, "6");
	else if (conv_int / 100 == 7)
		mlx_string_put(win->mlx, win->win, win->x_win / 2 - 20, win->y_win / 2 - 40, 0xffffff, "7");
	else if (conv_int / 100 == 8)
		mlx_string_put(win->mlx, win->win, win->x_win / 2 - 20, win->y_win / 2 - 40, 0xffffff, "8");
	else if (conv_int / 100 == 9)
		mlx_string_put(win->mlx, win->win, win->x_win / 2 - 20, win->y_win / 2 - 40, 0xffffff, "9");
	else if (conv_int / 100 == 10)
	{
		mlx_string_put(win->mlx, win->win, win->x_win / 2 - 20, win->y_win / 2 - 40, 0xffffff, "0");
		mlx_string_put(win->mlx, win->win, win->x_win / 2 - 30, win->y_win / 2 - 40, 0xffffff, "1");
	}

	if (conv_int / 10 % 10 == 0)
		mlx_string_put(win->mlx, win->win, win->x_win / 2 - 10, win->y_win / 2 - 40, 0xffffff, "0");
	else if (conv_int / 10 % 10 == 1)
		mlx_string_put(win->mlx, win->win, win->x_win / 2 - 10, win->y_win / 2 - 40, 0xffffff, "1");
	else if (conv_int / 10 % 10 == 2)
		mlx_string_put(win->mlx, win->win, win->x_win / 2 - 10, win->y_win / 2 - 40, 0xffffff, "2");
	else if (conv_int / 10 % 10 == 3)
		mlx_string_put(win->mlx, win->win, win->x_win / 2 - 10, win->y_win / 2 - 40, 0xffffff, "3");
	else if (conv_int / 10 % 10 == 4)
		mlx_string_put(win->mlx, win->win, win->x_win / 2 - 10, win->y_win / 2 - 40, 0xffffff, "4");
	else if (conv_int / 10 % 10 == 5)
		mlx_string_put(win->mlx, win->win, win->x_win / 2 - 10, win->y_win / 2 - 40, 0xffffff, "5");
	else if (conv_int / 10 % 10 == 6)
		mlx_string_put(win->mlx, win->win, win->x_win / 2 - 10, win->y_win / 2 - 40, 0xffffff, "6");
	else if (conv_int / 10 % 10 == 7)
		mlx_string_put(win->mlx, win->win, win->x_win / 2 - 10, win->y_win / 2 - 40, 0xffffff, "7");
	else if (conv_int / 10 % 10 == 8)
		mlx_string_put(win->mlx, win->win, win->x_win / 2 - 10, win->y_win / 2 - 40, 0xffffff, "8");
	else if (conv_int / 10 % 10 == 9)
		mlx_string_put(win->mlx, win->win, win->x_win / 2 - 10, win->y_win / 2 - 40, 0xffffff, "9");




	mlx_string_put(win->mlx, win->win, win->x_win / 2 , win->y_win / 2 - 40, 0xffffff, ".");
	if (conv_int % 10 == 0)
		mlx_string_put(win->mlx, win->win, win->x_win / 2 + 10 , win->y_win / 2 - 40, 0xffffff, "0");
	else if (conv_int % 10 == 1)
		mlx_string_put(win->mlx, win->win, win->x_win / 2 + 10 , win->y_win / 2 - 40, 0xffffff, "1");
	else if (conv_int % 10 == 2)
		mlx_string_put(win->mlx, win->win, win->x_win / 2 + 10 , win->y_win / 2 - 40, 0xffffff, "2");
	else if (conv_int % 10 == 3)
		mlx_string_put(win->mlx, win->win, win->x_win / 2 + 10 , win->y_win / 2 - 40, 0xffffff, "3");
	else if (conv_int % 10 == 4)
		mlx_string_put(win->mlx, win->win, win->x_win / 2 + 10 , win->y_win / 2 - 40, 0xffffff, "4");
	else if (conv_int % 10 == 5)
		mlx_string_put(win->mlx, win->win, win->x_win / 2 + 10 , win->y_win / 2 - 40, 0xffffff, "5");
	else if (conv_int % 10 == 6)
		mlx_string_put(win->mlx, win->win, win->x_win / 2 + 10 , win->y_win / 2 - 40, 0xffffff, "6");
	else if (conv_int % 10 == 7)
		mlx_string_put(win->mlx, win->win, win->x_win / 2 + 10 , win->y_win / 2 - 40, 0xffffff, "7");
	else if (conv_int % 10 == 8)
		mlx_string_put(win->mlx, win->win, win->x_win / 2 + 10 , win->y_win / 2 - 40, 0xffffff, "8");
	else if (conv_int % 10 == 9)
		mlx_string_put(win->mlx, win->win, win->x_win / 2 + 10 , win->y_win / 2 - 40, 0xffffff, "9");
	mlx_string_put(win->mlx, win->win, win->x_win / 2 + 20 , win->y_win / 2 - 40, 0xffffff, "%");

}

int		loading_screen2(t_win *win, float percent)
{
	int		x;
	int		y;

	x = 0;
	x = 0;
	y = 0;
	while (x < (win->x_win)/ 2)
	{
		while (y < 25)
		{
			if ((x <= percent * win->x_win / 2))
				img_add_px2(win, 0x00ff00, x, y);
			else if ((x <= win->x_win / 2))
				img_add_px2(win, 0x008000, x, y);
			else
				img_add_px2(win, 0x000000, x, y);
			y++;
		}
		y = 0;
		x++;
	}
	mlx_put_image_to_window(win->mlx, win->win, win->img2, win->x_win / 4, 0);

	//	mlx_put_image_to_window(win->mlx, win->win, win->img3, 0, 0);
	print_percent2(win, percent);
	return (0);
}


int		loading_screen(t_win *win, float percent)
{
	int		x;
	int		y;

	x = 0;
	y = 0;
	while (x < win->x_win)
	{
		while (y < win->y_win)
		{
			if ((y >= win->y_win / 2 - 10 && y <= win->y_win / 2 + 10) && (x >= win->x_win / 4 && x <= win->x_win / 4 + percent * win->x_win / 2))
				img_add_px2(win, 0x00ff00, x, y);
			else if ((y >= win->y_win / 2 - 10 && y <= win->y_win / 2 + 10) && (x >= win->x_win / 4 && x <= win->x_win / 4 + win->x_win / 2))
				img_add_px2(win, 0x008000, x, y);
			else
				img_add_px2(win, 0x000000, x, y);
			y++;
		}
		y = 0;
		x++;
	}
	mlx_put_image_to_window(win->mlx, win->win, win->img2, 0, 0);
	print_percent(win, percent);
	return (0);
}

void	r_render_setup(t_thread *super, t_cam *cam, t_win *win)
{
	t_render		*r;

	r = super->render;

	//	raydir = new_params_vec(0, 0, 0);
	//	rayorig = new_params_vec(0, 0, 0);
	r->width = super->win->x_img;
	r->height = win->y_img;
	r->invWidth = 1.0 / (float)r->width;
	r->invHeight = 1.0 / (float)r->height;
	r->fov = 45;
	r->aspectratio = (float)r->width / (float)r->height;
	r->angle = tan(M_PI * 0.5 * r->fov / 180.);

	r->y = 0;
	r->x = 0;
	r->z = 0;

	push_params_vec(cam->cam_org->x, cam->cam_org->y, cam->cam_org->z, r->rayorig);
	//	thread->render->rayorig = new_params_vec(0, 0, 0);
	//	r->y = cam->cam_org->x;
	//	r->x = cam->cam_org->y;
	//	r->z = cam->cam_org->z;
	r->x_tmp = 0;
	r->y_tmp = 0;
	r->zmax = (super->win->x_img) * (win->y_img);

	super->trace = setup_trace();

	//	setup_trace_test(super->trace);
	//	while (1)
	//			;
	super->render->state = 2;
}

void	r_render_setup_2(t_phase *super, t_cam *cam, t_win *win)
{
	t_phase		*r;

	r = super;

	//	raydir = new_params_vec(0, 0, 0);
	//	rayorig = new_params_vec(0, 0, 0);
	r->width = win->x_img;
	r->height = win->y_img;
	r->invWidth = 1.0 / (float)r->width;
	r->invHeight = 1.0 / (float)r->height;
	r->fov = 30;
	r->aspectratio = (float)r->width / (float)r->height;
	r->angle = tan(M_PI * 0.5 * r->fov / 180.);
	r->y = 0;
	r->x = 0;
	r->z = 0;

	//	r->y = cam->cam_org->x;
	//	r->x = cam->cam_org->y;
	//	r->z = cam->cam_org->z;


	r->x_tmp = 0;
	r->y_tmp = 0;
	r->zmax = (win->x_img) * (win->y_img);
	//super->trace = setup_trace();
	super->state = 2;
}




void	*r_render_tour_compute(void *param)
{
	t_thread	*thread;
	t_render	*r;


	//	*super->z = *super->z + 1;
	thread = param;
	r = thread->render;

	//			r->x = x;
	//			r->y = y;
	r->xx = (2 * ((r->x + 0.5) * r->invWidth) - 1) * r->angle * r->aspectratio;
	r->yy = (1 - 2 * ((r->y + 0.5) * r->invHeight)) * r->angle;
	push_params_vec(r->xx, r->yy, -1, r->raydir);
	reset_trace(thread->trace);
	//		push_params_vec(xx, yy, -1, datrace->raydir);
	//		printf("x = %f, y = %f, z = %f	", raydir.x, raydir.y, raydir.z);
	normalize_vec(r->raydir);

	//	img_add_px(win, vec_to_color(new_params_vec(0.22, (float)y / (float)Y_WIN ,(float)x / (float)X_WIN)), x, y);
	thread->trace->rayorig = r->rayorig;
	thread->trace->raydir = r->raydir;
	//	printf("orig : x = %f, y = %f, z = %f\n", r->rayorig->x, r->rayorig->y, r->rayorig->z);
	//	
	//	printf("dir : x = %f, y = %f, z = %f\n", r->raydir->x, r->raydir->y, r->raydir->z);
	trace(0, thread->list, thread->trace);
	img_add_px(thread->win, vec_to_color(thread->trace->surface_color), r->x, r->y);
	pthread_exit(NULL);
}


void	r_render_tour_phase_0(t_super *super)
{
	t_phase		*p;
	pthread_t	test[THREADS];
	int			i;

	i = 0;
	p = super->phase;
	//	while (p->z <= (p->zmax / 64))

	while (p->z <= ((super->win->x_img) / 8 + 1) * ((super->win->y_img) / 8 + 1))
	{
		i = 0;

		//		while (i < THREADS && p->z <= p->zmax / 64)

		while (i < THREADS && p->z <= ((super->win->x_img) / 8 + 1) * ((super->win->y_img)  / 8 + 1))
		{
			super->thread[i]->render->x = p->getcoor[p->z] / 10000;
			super->thread[i]->render->y = p->getcoor[p->z] % 10000;
			pthread_create(&test[i], NULL, r_render_tour_compute, super->thread[i]);
			p->z++;
			i++;
			if (p->getcoor[p->z] / 10000 > p->width)
				ft_putstr("error  ");
		}	
		i--;
		while (i >= 0)
		{
			pthread_join(test[i], NULL);
			i--;
		}
		if ((p->z) % (63) == 0)
		{
			//		exit(-1);
			apply_filling_p0(super->win, super->phase);
			mlx_put_image_to_window(super->win->mlx, super->win->win, super->win->img3, 0, 0);
			mlx_put_image_to_window(super->win->mlx, super->win->win, super->win->img_loa, 0, p->getcoor[p->z] % 10000 / 2 - 30);
			(loading_screen2(super->win, (float)p->z / (float)p->zmax));

			return ;
		}
		//	printf(".");

	}
	apply_filling_p0(super->win, super->phase);
	mlx_put_image_to_window(super->win->mlx, super->win->win, super->win->img3, 0, 0);

	//		apply_autofill(super->win);
	//	mlx_put_image_to_window(super->win->mlx, super->win->win, super->win->img3, 0, 0);
	//	ft_putstr("done mdr\n");
	super->phase->state = 3;
}


void	r_render_tour_phase_1(t_super *super)
{
	t_phase		*p;
	pthread_t	test[THREADS];
	int			i;

	i = 0;
	p = super->phase;

	//		ft_putstr("BOUee?\n");
	//while (p->z <= (p->zmax / 16) + 0)


	while (p->z <= ((super->win->x_img) / 4 + 1) * ((super->win->y_img) / 4 + 1))
	{
		i = 0;
		//		while (i < THREADS &&p->z <= (p->zmax / 16) + 0)

		while (i < THREADS &&p->z <=  ((super->win->x_img) / 4 + 1) * ((super->win->y_img) / 4 + 1))
		{
			super->thread[i]->render->x = p->getcoor[p->z] / 10000;
			super->thread[i]->render->y = p->getcoor[p->z] % 10000;
			pthread_create(&test[i], NULL, r_render_tour_compute, super->thread[i]);
			p->z++;
			i++;
			if (p->getcoor[p->z] / 10000 > p->width)
				ft_putstr("error  ");
		}	
		i--;
		while (i >= 0)
		{
			pthread_join(test[i], NULL);
			i--;
		}

		//	ft_putstr("BOrrU?\n");
		if ((p->z) % (1000) == 2)
		{
			//			exit(-1);
			//			ft_putstr("BpppOU?\n");
			apply_filling_p1(super->win, super->phase);
			mlx_put_image_to_window(super->win->mlx, super->win->win, super->win->img3, 0, 0);
			mlx_put_image_to_window(super->win->mlx, super->win->win, super->win->img_las, 0, p->getcoor[p->z] % 10000 / 2);
			(loading_screen2(super->win, (float)p->z / (float)p->zmax));
			return ;
		}


	}
	//	apply_autofill(super->win);

	apply_filling_p1(super->win, super->phase);
	mlx_put_image_to_window(super->win->mlx, super->win->win, super->win->img3, 0, 0);

	(loading_screen2(super->win, (float)p->z / (float)p->zmax));
	//	ft_putstr("done mdr\n");
	super->phase->state = 5;
}

void	r_render_tour_phase_2(t_super *super)
{
	t_phase		*p;
	pthread_t	test[THREADS];
	int			i;

	p = super->phase;
	//	while (p->z < p->zmax / 4)


	while (p->z < ((super->win->x_img) / 2 + 1) * ((super->win->y_img) / 2 + 1))
	{
		i = 0;
		while (i < THREADS && p->z < ((super->win->x_img) / 2 + 1) * ((super->win->y_img) / 2 + 1))
		{
			//	printf("i = %d", i);
			super->thread[i]->render->x = p->getcoor[p->z] / 10000;
			super->thread[i]->render->y = p->getcoor[p->z] % 10000;
			pthread_create(&test[i], NULL, r_render_tour_compute, super->thread[i]);
			p->z++;
			i++;

		}

		//if ((r->z) % ((r->zmax / 4000) == 0 ? 1 : (r->zmax / 4000))  == 0)


		i--;

		while (i >= 0)
		{
			pthread_join(test[i], NULL);
			i--;
		}
		//		if ((p->z) % ((p->zmax / 1000) == 0 ? 1 : (p->zmax / 1000))  == 0)
		//		{
		//
		//				(loading_screen2(super->win, (float)p->z / (float)p->zmax));
		//				return ;
		//		}
		if ((p->z) % (1000) == 2)
		{
			apply_filling_p2(super->win, super->phase);
			mlx_put_image_to_window(super->win->mlx, super->win->win, super->win->img3, 0, 0);
			//			ft_putstr(",");

			mlx_put_image_to_window(super->win->mlx, super->win->win, super->win->img_las, 0, p->getcoor[p->z] % 10000 / 2);
			(loading_screen2(super->win, (float)p->z / (float)p->zmax));
			return ;
		}

	}
	apply_filling_p2(super->win, super->phase);
	mlx_put_image_to_window(super->win->mlx, super->win->win, super->win->img3, 0, 0);
	//	apply_autoauto(super->win);
	//	mlx_put_image_to_window(super->win->mlx, super->win->win, super->win->img3, 0, 0);
	super->phase->state = 7;
}

void	r_render_tour_phase_3(t_super *super)
{
	t_phase		*p;
	pthread_t	test[THREADS];
	int			i;

	p = super->phase;

	//	while (p->z < p->zmax)
	while (p->z < ((super->win->x_img) + 1) * ((super->win->y_img) + 1))
	{
		i = 0;
		//	while (i < THREADS && p->z < p->zmax)
		while (i < THREADS && p->z < ((super->win->x_img) + 1) * ((super->win->y_img) + 1))
		{
			//	printf("i = %d", i);
			super->thread[i]->render->x = p->getcoor[p->z] / 10000;
			super->thread[i]->render->y = p->getcoor[p->z] % 10000;
			pthread_create(&test[i], NULL, r_render_tour_compute, super->thread[i]);
			p->z++;
			i++;

		}

		//if ((r->z) % ((r->zmax / 4000) == 0 ? 1 : (r->zmax / 4000))  == 0)


		i--;

		while (i >= 0)
		{
			pthread_join(test[i], NULL);
			i--;
		}
		//		if ((p->z) % ((p->zmax / 1000) == 0 ? 1 : (p->zmax / 1000))  == 0)
		//		{
		//
		//				(loading_screen2(super->win, (float)p->z / (float)p->zmax));
		//				return ;
		//		}
		//		ft_putstr("wefwefewfwe ");
		if ((p->z) % (113) == 3)
		{
			apply_filling_p3(super->win, super->phase);
			mlx_put_image_to_window(super->win->mlx, super->win->win, super->win->img3, 0, 0);
			//	ft_putstr(",");

			mlx_put_image_to_window(super->win->mlx, super->win->win, super->win->img_las, 0, (((float)p->z - (float)p->zmax / 4.) / ((float)p->zmax - (float)p->zmax / 4.) * (float)super->win->y_win) - 3);
			(loading_screen2(super->win, (float)p->z / (float)p->zmax));
			return ;
		}

	}
	//		apply_filling_p3(super->win, super->phase);
	//		mlx_put_image_to_window(super->win->mlx, super->win->win, super->win->img3, 0, 0);
	apply_antiaaaliasing(super->win);
	mlx_put_image_to_window(super->win->mlx, super->win->win, super->win->img3, 0, 0);
	super->phase->state = 9;
}


void	r_render_tour_phase_1b(t_super *super)
{
	t_phase		*p;
	pthread_t	test1;
	pthread_t	test2;
	pthread_t	test3;
	pthread_t	test4;
	pthread_t	test[THREADS];
	int			i;

	void		*t1;
	p = super->phase;
	while (p->y_tmp <= p->height / 4)
	{

		while (p->x_tmp <= p->width / 4)
		{

			//	r->x = r->x_tmp * 4;
			//	r->y = r->y_tmp * 4;

			//		r_render_tour_compute(super->thread_1, p->x_tmp * 4, p->y_tmp * 4);
			/*		
					r->xx = (2 * ((r->x + 0.5) * r->invWidth) - 1) * r->angle * r->aspectratio;
					r->yy = (1 - 2 * ((r->y + 0.5) * r->invHeight)) * r->angle;
					push_params_vec(r->xx, r->yy, -1, r->raydir);
					reset_trace(super->trace);
			//		push_params_vec(xx, yy, -1, datrace->raydir);
			//		printf("x = %f, y = %f, z = %f	", raydir.x, raydir.y, raydir.z);
			normalize_vec(r->raydir);
			*/
			//	img_add_px(win, vec_to_color(new_params_vec(0.22, (float)y / (float)Y_WIN ,(float)x / (float)X_WIN)), x, y);

			//	img_add_px(super->win, vec_to_color(trace(r->rayorig, r->raydir, 0, super->list, super->trace)), r->x, r->y);
			//	r->z++;

			//		p->z++;
			super->thread_1->render->x = p->x_tmp * 4;
			super->thread_1->render->y = p->y_tmp * 4;

			super->thread_2->render->x = (p->x_tmp + 1)* 4;
			super->thread_2->render->y = (p->y_tmp) * 4;

			super->thread_3->render->x = (p->x_tmp + 2)* 4;
			super->thread_3->render->y = (p->y_tmp) * 4;

			super->thread_4->render->x = (p->x_tmp + 3)* 4;
			super->thread_4->render->y = (p->y_tmp + 0) * 4;





			//			r_render_tour_compute(super->thread_1);


			if (1)
			{


				i = 0;
				while (i < THREADS)
				{
					super->thread[i]->render->x = (p->x_tmp + i)* 4;
					super->thread[i]->render->y = (p->y_tmp + 0) * 4;
					if (p->x_tmp + i <= p->width / 4 && 1)
						pthread_create(&test[i], NULL, r_render_tour_compute, super->thread[i]);
					i++;
				}
				i = 0;
				while (i < THREADS)
				{
					if (p->x_tmp + i <= p->width / 4 && 1)
					{
						pthread_join(test[i], NULL);
					}
					i++;
				}
				p->x_tmp += THREADS - 1;
			}











			else if (1)
			{
				if (p->x_tmp <= p->width / 4 && 1)
				{
					t1 = super->thread_1;
					pthread_create(&test1, NULL, r_render_tour_compute, super->thread_1);
				}
				if (p->x_tmp + 1 <= p->width / 4 && 1)
				{
					t1 = super->thread_2;
					pthread_create(&test2, NULL, r_render_tour_compute, super->thread_2);
				}
				if (p->x_tmp + 2 <= p->width / 4 && 1)
				{
					t1 = super->thread_3;
					pthread_create(&test3, NULL, r_render_tour_compute, super->thread_3);
				}
				if (p->x_tmp + 3 <= p->width / 4 && 1)
				{
					t1 = super->thread_4;
					pthread_create(&test4, NULL, r_render_tour_compute, super->thread_4);
				}


				if (p->x_tmp <= p->width / 4 && 1)
				{
					pthread_join(test1, NULL);
				}
				if (p->x_tmp + 1 <= p->width / 4 && 1)
				{
					pthread_join(test2, NULL);
				}
				if (p->x_tmp + 2 <= p->width / 4 && 1)
				{
					pthread_join(test3, NULL);
				}
				if (p->x_tmp + 3 <= p->width / 4 && 1)
				{
					pthread_join(test4, NULL);
				}


				p->x_tmp++;
				p->x_tmp++;
				p->x_tmp++;




			}
			else if (0)
			{
				if (p->x_tmp <= p->width / 4 && 1)
				{
					t1 = super->thread_1;
					pthread_create(&test1, NULL, r_render_tour_compute, super->thread_1);
				}
				if (p->x_tmp + 1 <= p->width / 4 && 1)
				{
					t1 = super->thread_2;
					pthread_create(&test2, NULL, r_render_tour_compute, super->thread_2);
				}



				if (p->x_tmp <= p->width / 4 && 1)
				{
					pthread_join(test1, NULL);
				}
				if (p->x_tmp + 1 <= p->width / 4 && 1)
				{
					pthread_join(test2, NULL);
				}


				p->x_tmp++;
			}
			else if (0)
			{
				if (p->x_tmp <= p->width / 4 && 1)
				{
					t1 = super->thread_1;
					pthread_create(&test1, NULL, r_render_tour_compute, super->thread_1);
				}
				if (p->x_tmp + 1 <= p->width / 4 && 0)
				{
					t1 = super->thread_2;
					pthread_create(&test2, NULL, r_render_tour_compute, super->thread_2);
				}



				if (p->x_tmp <= p->width / 4 && 1)
				{
					pthread_join(test1, NULL);
				}
				if (p->x_tmp + 1 <= p->width / 4 && 0)
				{
					pthread_join(test2, NULL);
				}

			}
			p->x_tmp++;
			if ((p->z) % ((p->zmax / 1000) == 0 ? 1 : (p->zmax / 1000))  == 0)
			{

				(loading_screen2(super->win, (float)p->z / (float)p->zmax));
				return ;
			}



		}
		p->y_tmp++;
		p->x_tmp = 0;
	}

	apply_autofill(super->win);
	mlx_put_image_to_window(super->win->mlx, super->win->win, super->win->img3, 0, 0);
	//	ft_putstr("done mdr\n");
	super->phase->state = 3;
}
/*
   void	r_render_tour_phase_2(t_super *super)
   {
   t_phase		*p;

   p = super->phase;
   while (p->y_tmp <= p->height / 4)
   {

   while (p->x_tmp <= p->width / 4)
   {
   if (p->x_tmp <= (p->width - 1) / 4 )
   r_render_tour_compute(super->thread_1, p->x_tmp * 4 + 1, p->y_tmp * 4);
   if (p->y_tmp <= (p->height - 1) / 4 )
   r_render_tour_compute(super->thread_1, p->x_tmp * 4, p->y_tmp * 4 + 1);
   if (p->y_tmp <= (p->height - 1) / 4 && p->x_tmp <= (p->width - 1) / 4)
   r_render_tour_compute(super->thread_1, p->x_tmp * 4 + 1, p->y_tmp * 4 + 1);
//if ((r->z) % ((r->zmax / 4000) == 0 ? 1 : (r->zmax / 4000))  == 0)

if ((p->z) % 113 == 1)
{

(loading_screen2(super->win, (float)p->z / (float)p->zmax));
return ;
}

p->x_tmp++;
}
p->y_tmp++;
p->x_tmp = 0;
}

apply_autoauto(super->win);
mlx_put_image_to_window(super->win->mlx, super->win->win, super->win->img3, 0, 0);
super->phase->state = 5;
}



void	r_render_tour_phase_3(t_super *super)
{
t_phase		*p;

p = super->phase;
//	printf("coucou");
//	ft_putstr("coucou");

while (p->y_tmp <= p->height / 4)
{

while (p->x_tmp <= p->width / 4)
{

//	ft_putstr("coucou");
if (p->x_tmp <= (p->width - 2) / 4 )
r_render_tour_compute(super->thread_1, p->x_tmp * 4 + 2, p->y_tmp * 4);
if (p->y_tmp <= (p->width - 3) / 4 )
r_render_tour_compute(super->thread_1, p->x_tmp * 4 + 3, p->y_tmp * 4);


if (p->x_tmp <= (p->width - 2) / 4 && p->y_tmp <= (p->height - 1) / 4)
r_render_tour_compute(super->thread_1, p->x_tmp * 4 + 2, p->y_tmp * 4 + 1);
if (p->x_tmp <= (p->width - 3) / 4 && p->y_tmp <= (p->height - 1) / 4)
r_render_tour_compute(super->thread_1, p->x_tmp * 4 + 3, p->y_tmp * 4 + 1);


if (p->x_tmp <= (p->width) / 4 && p->y_tmp <= (p->height - 2) / 4)
r_render_tour_compute(super->thread_1, p->x_tmp * 4 , p->y_tmp * 4 + 2);
if (p->x_tmp <= (p->width - 1) / 4 && p->y_tmp <= (p->height - 2) / 4)
r_render_tour_compute(super->thread_1, p->x_tmp * 4 + 1, p->y_tmp * 4 + 2);
if (p->x_tmp <= (p->width - 2) / 4 && p->y_tmp <= (p->height - 2) / 4)
r_render_tour_compute(super->thread_1, p->x_tmp * 4 + 2, p->y_tmp * 4 + 2);		
if (p->x_tmp <= (p->width - 3) / 4 && p->y_tmp <= (p->height - 2) / 4)
	r_render_tour_compute(super->thread_1, p->x_tmp * 4 + 3, p->y_tmp * 4 + 2);	

if (p->x_tmp <= (p->width) / 4 && p->y_tmp <= (p->height - 3) / 4)
	r_render_tour_compute(super->thread_1, p->x_tmp * 4 , p->y_tmp * 4 + 3);
if (p->x_tmp <= (p->width - 1) / 4 && p->y_tmp <= (p->height - 3) / 4)
	r_render_tour_compute(super->thread_1, p->x_tmp * 4 + 1, p->y_tmp * 4 + 3);
if (p->x_tmp <= (p->width - 2) / 4 && p->y_tmp <= (p->height - 3) / 4)
	r_render_tour_compute(super->thread_1, p->x_tmp * 4 + 2, p->y_tmp * 4 + 3);		
if (p->x_tmp <= (p->width - 3) / 4 && p->y_tmp <= (p->height - 3) / 4)
	r_render_tour_compute(super->thread_1, p->x_tmp * 4 + 3, p->y_tmp * 4 + 3);	







if (p->z % 113 == 1)
{

	//			ft_putstr("coucou");
	(loading_screen2(super->win, (float)p->z / (float)p->zmax));
	return ;
}
//
p->x_tmp++;
}
p->y_tmp++;
p->x_tmp = 0;
}

ft_putstr("coucou");
apply_antiaaaliasing(super->win);
mlx_put_image_to_window(super->win->mlx, super->win->win, super->win->img, 0, 0);
super->phase->state = 7;
}
*/



/*
   void	r_render_tour(t_super *super)
   {
   t_phase		*r;

   r = super->phase;
   while (r->y < r->height)
   {
   if (r->y == 55 && 0)
   {
   test_img(super->win);
   mlx_put_image_to_window(super->win->mlx, super->win->win, super->win->img2, 0, 0);

   mlx_loop(super->win->mlx);
   }
   while (r->x < r->width)
   {
   r->xx = (2 * ((r->x + 0.5) * r->invWidth) - 1) * r->angle * r->aspectratio;
   r->yy = (1 - 2 * ((r->y + 0.5) * r->invHeight)) * r->angle;
   push_params_vec(r->xx, r->yy, -1, r->raydir);
   reset_trace(super->trace);
//		push_params_vec(xx, yy, -1, datrace->raydir);
//		printf("x = %f, y = %f, z = %f	", raydir.x, raydir.y, raydir.z);
normalize_vec(r->raydir);

//	img_add_px(win, vec_to_color(new_params_vec(0.22, (float)y / (float)Y_WIN ,(float)x / (float)X_WIN)), x, y);

img_add_px(super->win, vec_to_color(trace(r->rayorig, r->raydir, 0, super->list, super->trace)), r->x, r->y);
r->x++;
r->z++;
if ((r->z) % ((r->zmax / 1000) == 0 ? 1 : (r->zmax / 1000))  == 0)
{

(loading_screen(super->win, (float)r->z / (float)r->zmax));
return ;
}



}
r->y++;
r->x = 0;
}

apply_antiaaaliasing(super->win);
mlx_put_image_to_window(super->win->mlx, super->win->win, super->win->img, 0, 0);
super->render->state = 7;
}
*/




void	fill_getcoor(t_super *super)
{
	t_phase	*p;
	int		i;

	p = super->phase;
	p->zmax = (super->win->x_img) * (super->win->y_img);
	p->z = 0;
	i = 0;
	p->x_tmp = 0;
	p->y_tmp = 0;

	//PHASE 0
	while (p->y_tmp <= p->height / 8)
	{

		while (p->x_tmp <= p->width / 8)
		{
			p->getcoor[i++] = (p->x_tmp)* 8 * 10000 + (p->y_tmp) * 8;
			p->x_tmp++;
			//			ft_putstr(".");
		}
		p->x_tmp = 0;
		p->y_tmp++;
	}
	p->x_tmp = 0;
	p->y_tmp = 0;


	//PHASE 1
	while (p->y_tmp <= p->height / 4)
	{

		while (p->x_tmp <= p->width / 4)
		{ 
			if (p->x_tmp % 2 != 0 || p->y_tmp % 2 != 0)
			{
				p->getcoor[i++] = (p->x_tmp)* 4 * 10000 + (p->y_tmp) * 4;
				//				ft_putstr(";");
			}
			p->x_tmp++;
		}
		p->x_tmp = 0;
		p->y_tmp++;
	}
	p->x_tmp = 0;
	p->y_tmp = 0;

	//	ft_putstr("324");
	//PHASE 2
	while (p->y_tmp <= p->height / 4)
	{

		while (p->x_tmp <= p->width / 4)
		{
			if (p->x_tmp <= (p->width - 1) / 4 )
				p->getcoor[i++] = ((p->x_tmp)* 4 + 1) * 10000 + (p->y_tmp) * 4;
			if (p->y_tmp <= (p->height - 1) / 4 )
				p->getcoor[i++] = ((p->x_tmp)* 4) * 10000 + (p->y_tmp) * 4 + 1;
			if (p->y_tmp <= (p->height - 1) / 4 && p->x_tmp <= (p->width - 1) / 4)
				p->getcoor[i++] = ((p->x_tmp)* 4 + 1) * 10000 + (p->y_tmp) * 4 + 1;
			p->x_tmp++;

			//		ft_putstr(".");
		}
		p->y_tmp++;
		p->x_tmp = 0;
	}
	p->x_tmp = 0;
	p->y_tmp = 0;

	//	ft_putstr("333244");
	//PHASE 3
	while (p->y_tmp <= p->height / 4 && 1)
	{

		while (p->x_tmp <= p->width / 4)
		{

			//	ft_putstr("coucou");
			//		int g = 12;
			//		while (g > 0)
			///		{
			//			printf("getcoor = %d,", p->getcoor[i - g]);
			//				g--;
			//		}
			//		printf("i == %d,", i);
			if (p->x_tmp <= (p->width - 2) / 4 )
				p->getcoor[i++] = ((p->x_tmp)* 4 + 2) * 10000 + (p->y_tmp) * 4;
			if (p->y_tmp <= (p->width - 3) / 4 )
				p->getcoor[i++] = ((p->x_tmp)* 4 + 3) * 10000 + (p->y_tmp) * 4;
			if (p->x_tmp <= (p->width - 2) / 4 && p->y_tmp <= (p->height - 1) / 4)
				p->getcoor[i++] = ((p->x_tmp)* 4 + 2) * 10000 + (p->y_tmp) * 4 + 1;
			if (p->x_tmp <= (p->width - 3) / 4 && p->y_tmp <= (p->height - 1) / 4)
				p->getcoor[i++] = ((p->x_tmp)* 4 + 3) * 10000 + (p->y_tmp) * 4 + 1;
			if (p->x_tmp <= (p->width) / 4 && p->y_tmp <= (p->height - 2) / 4)
				p->getcoor[i++] = ((p->x_tmp)* 4) * 10000 + (p->y_tmp) * 4 + 2;
			if (p->x_tmp <= (p->width - 1) / 4 && p->y_tmp <= (p->height - 2) / 4)
				p->getcoor[i++] = ((p->x_tmp)* 4 + 1) * 10000 + (p->y_tmp) * 4 + 2;
			if (p->x_tmp <= (p->width - 2) / 4 && p->y_tmp <= (p->height - 2) / 4)
				p->getcoor[i++] = ((p->x_tmp)* 4 + 2) * 10000 + (p->y_tmp) * 4 + 2;
			if (p->x_tmp <= (p->width - 3) / 4 && p->y_tmp <= (p->height - 2) / 4)
				p->getcoor[i++] = ((p->x_tmp)* 4 + 3) * 10000 + (p->y_tmp) * 4 + 2;
			if (p->x_tmp <= (p->width) / 4 && p->y_tmp <= (p->height - 3) / 4)
				p->getcoor[i++] = ((p->x_tmp)* 4) * 10000 + (p->y_tmp) * 4 + 3;
			if (p->x_tmp <= (p->width - 1) / 4 && p->y_tmp <= (p->height - 3) / 4)
				p->getcoor[i++] = ((p->x_tmp)* 4 + 1) * 10000 + (p->y_tmp) * 4 + 3;
			if (p->x_tmp <= (p->width - 2) / 4 && p->y_tmp <= (p->height - 3) / 4)
				p->getcoor[i++] = ((p->x_tmp)* 4 + 2) * 10000 + (p->y_tmp) * 4 + 3;
			if (p->x_tmp <= (p->width - 3) / 4 && p->y_tmp <= (p->height - 3) / 4)
				p->getcoor[i++] = ((p->x_tmp)* 4 + 3) * 10000 + (p->y_tmp) * 4 + 3;
			p->x_tmp++;

			//		ft_putstr(".");
		}
		p->y_tmp++;
		p->x_tmp = 0;
	}
	p->z = 0;

	//		printf("GET COCOOCOCOCOCO OCOCOOCOCOOROEOROEOREO == %d\n\n\n\n\n\n\n,", i);
	//	printf("getcoor = %d,", p->getcoor[i]);
	//	ft_putstr("done");
}

void	setup_loading_laser(t_super *super)
{
	int		i;

	i = 0;
	while (i < super->win->x_win)
	{
		img_add_px_las(super->win, 0xAA0000, i, 0);
		img_add_px_las(super->win, 0xBB0000, i, 1);
		img_add_px_las(super->win, 0xCC0000, i, 2);
		img_add_px_las(super->win, 0xDD0000, i, 3);
		img_add_px_las(super->win, 0xFF0000, i, 4);
		img_add_px_las(super->win, 0xFF0000, i, 5);
		img_add_px_las(super->win, 0xDD0000, i, 6);
		img_add_px_las(super->win, 0xCC0000, i, 7);
		img_add_px_las(super->win, 0xBB0000, i, 8);
		img_add_px_las(super->win, 0xAA0000, i, 9);
		i++;
	}
}

int		rt_loop(t_super *super)
{
	int		i;

	if (super->phase->state == 1)
	{

		//		r_render_setup(super->thread_1);
		//		r_render_setup(super->thread_2);
		//		r_render_setup(super->thread_3);
		//		r_render_setup(super->thread_4);
		//		while (1)
		//			;
		r_render_setup_2(super->phase, super->cam, super->win);
		//		super->thread_1->z = &super->phase->z;
		//		super->thread_2->z = &super->phase->z;
		//		super->thread_3->z = &super->phase->z;
		//		super->thread_4->z = &super->phase->z;



		if (!(super->win->img_loa = mlx_xpm_file_to_image(super->win->mlx, "./XPM/chargementAAAAA_0.xpm",
						&super->win->x_loa, &super->win->y_loa)))
			exit(0);

		setup_loading_laser(super);

		fill_getcoor(super);

		i = 0;
		while (i < THREADS)
		{
			r_render_setup(super->thread[i], super->cam, super->win); // <======== la
			super->thread[i]->z = &super->phase->z;

			i++;
		}


		super->phase->z = 0;
		super->phase->state = 2;


	}
	else if (super->phase->state == 2)
	{
		//	r_render_tour(super);
		r_render_tour_phase_0(super);
		//	super->phase->state == 3
	}
	else if (super->phase->state == 3)
	{
		super->phase->x_tmp = 0;
		super->phase->y_tmp = 0;
		super->phase->state = 4;
	}
	else if (super->phase->state == 4)
	{
		//	r_render_tour(super);
		r_render_tour_phase_1(super);
		//	super->phase->state == 3
	}
	else if (super->phase->state == 5)
	{
		super->phase->x_tmp = 0;
		super->phase->y_tmp = 0;
		super->phase->state = 6;
	}
	else if (super->phase->state == 6)
	{

		r_render_tour_phase_2(super);
	}
	else if (super->phase->state == 7)
	{
		super->phase->x_tmp = 0;
		super->phase->y_tmp = 0;
		super->phase->state = 8;
	}
	else if (super->phase->state == 8)
	{

		r_render_tour_phase_3(super);
	}



	return (0);
}



/*

   void	r_render(t_super *super)
   {

   t_render		*r;

   r = super->render;

//	raydir = new_params_vec(0, 0, 0);
//	rayorig = new_params_vec(0, 0, 0);
r->width = X_IMG;
r->height = Y_IMG;
r->invWidth = 1.0 / (float)r->width;
r->invHeight = 1.0 / (float)r->height;
r->fov = 30;
r->aspectratio = (float)r->width / (float)r->height;
r->angle = tan(M_PI * 0.5 * r->fov / 180.);
r->y = 0;

super->trace = setup_trace();
while (r->y < r->height)
{
if (r->y == 55 && 0)
{
test_img(super->win);
mlx_put_image_to_window(super->win->mlx, super->win->win, super->win->img2, 0, 0);

mlx_loop(super->win->mlx);
}
r->x = 0;
while (r->x < r->width)
{
r->xx = (2 * ((r->x + 0.5) * r->invWidth) - 1) * r->angle * r->aspectratio;
r->yy = (1 - 2 * ((r->y + 0.5) * r->invHeight)) * r->angle;
push_params_vec(r->xx, r->yy, -1, r->raydir);
reset_trace(super->trace);
//		push_params_vec(xx, yy, -1, datrace->raydir);
//		printf("x = %f, y = %f, z = %f	", raydir.x, raydir.y, raydir.z);
normalize_vec(r->raydir);

//	img_add_px(win, vec_to_color(new_params_vec(0.22, (float)y / (float)Y_WIN ,(float)x / (float)X_WIN)), x, y);

img_add_px(super->win, vec_to_color(trace(r->rayorig, r->raydir, 0, super->list, super->trace)), r->x, r->y);
r->x++;
}
r->y++;
}
}

*/


void	fill_getcoor_bas(t_super *super)
{
	t_phase	*p;
	int		i;

	p = super->phase;
	p->zmax = (super->win->x_img) * (super->win->y_img);
	p->z = 0;
	i = 0;
	p->x_tmp = 0;
	p->y_tmp = 0;
	while (p->y_tmp <= p->height / 4)
	{

		while (p->x_tmp <= p->width / 4)
		{
			p->getcoor[i] = (p->x_tmp)* 4 * 10000;
			p->getcoor[i] += (p->y_tmp) * 4;

			p->x_tmp++;
			i++;
			p->z++;//
		}
		p->x_tmp = 0;
		p->y_tmp++;
	}
	p->x_tmp = 0;
	p->y_tmp = 0;
	while (p->y_tmp <= p->height / 4)
	{

		while (p->x_tmp <= p->width / 4)
		{
			if (p->x_tmp <= (p->width - 1) / 4 )
			{
				p->getcoor[i] = ((p->x_tmp)* 4 + 1) * 10000;
				p->getcoor[i] += (p->y_tmp) * 4;
				i++;
				p->z++;//
				//		r_render_tour_compute(super->thread_1, p->x_tmp * 4 + 1, p->y_tmp * 4);
			}
			if (p->y_tmp <= (p->height - 1) / 4 )
			{
				p->getcoor[i] = ((p->x_tmp)* 4) * 10000;
				p->getcoor[i] += (p->y_tmp) * 4 + 1;
				i++;
				p->z++;//
				//r_render_tour_compute(super->thread_1, p->x_tmp * 4, p->y_tmp * 4 + 1);
			}
			if (p->y_tmp <= (p->height - 1) / 4 && p->x_tmp <= (p->width - 1) / 4)
			{
				p->getcoor[i] = ((p->x_tmp)* 4 + 1) * 10000;
				p->getcoor[i] += (p->y_tmp) * 4 + 1;
				i++;
				p->z++;//
				//r_render_tour_compute(super->thread_1, p->x_tmp * 4 + 1, p->y_tmp * 4 + 1);
				//if ((r->z) % ((r->zmax / 4000) == 0 ? 1 : (r->zmax / 4000))  == 0)
			}
			p->x_tmp++;
		}
		p->y_tmp++;
		p->x_tmp = 0;
	}
	p->x_tmp = 0;
	p->y_tmp = 0;
	while (p->y_tmp <= p->height / 4)
	{

		while (p->x_tmp <= p->width / 4)
		{

			//	ft_putstr("coucou");
			if (p->x_tmp <= (p->width - 2) / 4 )
			{
				p->getcoor[i] = ((p->x_tmp)* 4 + 2) * 10000;
				p->getcoor[i] += (p->y_tmp) * 4;
				i++;
				p->z++;//
				//r_render_tour_compute(super->thread_1, p->x_tmp * 4 + 2, p->y_tmp * 4);
			}
			if (p->y_tmp <= (p->width - 3) / 4 )
			{
				p->getcoor[i] = ((p->x_tmp)* 4 + 3) * 10000;
				p->getcoor[i] += (p->y_tmp) * 4;
				i++;
				p->z++;//

				//r_render_tour_compute(super->thread_1, p->x_tmp * 4 + 3, p->y_tmp * 4);
			}
			if (p->x_tmp <= (p->width - 2) / 4 && p->y_tmp <= (p->height - 1) / 4)
			{
				p->getcoor[i] = ((p->x_tmp)* 4 + 2) * 10000;
				p->getcoor[i] += (p->y_tmp) * 4 + 1;
				i++;
				p->z++;//

				//r_render_tour_compute(super->thread_1, p->x_tmp * 4 + 2, p->y_tmp * 4 + 1);
			}
			if (p->x_tmp <= (p->width - 3) / 4 && p->y_tmp <= (p->height - 1) / 4)
			{
				p->getcoor[i] = ((p->x_tmp)* 4 + 3) * 10000;
				p->getcoor[i] += (p->y_tmp) * 4 + 1;
				i++;
				p->z++;//

				//r_render_tour_compute(super->thread_1, p->x_tmp * 4 + 3, p->y_tmp * 4 + 1);
			}

			if (p->x_tmp <= (p->width) / 4 && p->y_tmp <= (p->height - 2) / 4)
			{
				p->getcoor[i] = ((p->x_tmp)* 4) * 10000;
				p->getcoor[i] += (p->y_tmp) * 4 + 2;
				i++;
				p->z++;//


				//r_render_tour_compute(super->thread_1, p->x_tmp * 4 , p->y_tmp * 4 + 2);
			}
			if (p->x_tmp <= (p->width - 1) / 4 && p->y_tmp <= (p->height - 2) / 4)
			{
				p->getcoor[i] = ((p->x_tmp)* 4 + 1) * 10000;
				p->getcoor[i] += (p->y_tmp) * 4 + 2;
				i++;
				p->z++;//


				//r_render_tour_compute(super->thread_1, p->x_tmp * 4 + 1, p->y_tmp * 4 + 2);
			}
			if (p->x_tmp <= (p->width - 2) / 4 && p->y_tmp <= (p->height - 2) / 4)
			{
				p->getcoor[i] = ((p->x_tmp)* 4 + 2) * 10000;
				p->getcoor[i] += (p->y_tmp) * 4 + 2;
				i++;
				p->z++;//



				//r_render_tour_compute(super->thread_1, p->x_tmp * 4 + 2, p->y_tmp * 4 + 2);		
			}
			if (p->x_tmp <= (p->width - 3) / 4 && p->y_tmp <= (p->height - 2) / 4)
			{
				p->getcoor[i] = ((p->x_tmp)* 4 + 3) * 10000;
				p->getcoor[i] += (p->y_tmp) * 4 + 2;
				i++;
				p->z++;//


				//r_render_tour_compute(super->thread_1, p->x_tmp * 4 + 3, p->y_tmp * 4 + 2);	
			}
			if (p->x_tmp <= (p->width) / 4 && p->y_tmp <= (p->height - 3) / 4)
			{
				p->getcoor[i] = ((p->x_tmp)* 4) * 10000;
				p->getcoor[i] += (p->y_tmp) * 4 + 3;
				i++;
				p->z++;//


				//r_render_tour_compute(super->thread_1, p->x_tmp * 4 , p->y_tmp * 4 + 3);
			}
			if (p->x_tmp <= (p->width - 1) / 4 && p->y_tmp <= (p->height - 3) / 4)
			{
				p->getcoor[i] = ((p->x_tmp)* 4 + 1) * 10000;
				p->getcoor[i] += (p->y_tmp) * 4 + 3;
				i++;
				p->z++;//


				//r_render_tour_compute(super->thread_1, p->x_tmp * 4 + 1, p->y_tmp * 4 + 3);
			}
			if (p->x_tmp <= (p->width - 2) / 4 && p->y_tmp <= (p->height - 3) / 4)
			{
				p->getcoor[i] = ((p->x_tmp)* 4 + 2) * 10000;
				p->getcoor[i] += (p->y_tmp) * 4 + 3;
				i++;
				p->z++;//


				//r_render_tour_compute(super->thread_1, p->x_tmp * 4 + 2, p->y_tmp * 4 + 3);		
			}
			if (p->x_tmp <= (p->width - 3) / 4 && p->y_tmp <= (p->height - 3) / 4)
			{
				p->getcoor[i] = ((p->x_tmp)* 4 + 3) * 10000;
				p->getcoor[i] += (p->y_tmp) * 4 + 3;
				i++;
				p->z++;//


				//r_render_tour_compute(super->thread_1, p->x_tmp * 4 + 3, p->y_tmp * 4 + 3);	
			}
			p->x_tmp++;
		}
		p->y_tmp++;
		p->x_tmp = 0;
	}
}

int		main(int argc, char **argv)
{
	//	t_spher		*sphere;
	//	t_list		*list;
	//	t_list		*tmp;
	//	t_win		*win;
	int i;
	t_super		*super;

	//	super = 0;
	super = setup_super();
	//	if ((super->cam = (t_cam*)malloc(sizeof(*super->cam))) == NULL)
	//		exit(-1);
	//	if ((super = (t_super*)malloc(sizeof(*super))) == NULL)
	//		exit(0);

	//	setup_super_test(&super);
	//	super->trace->test = 1;
	//	if ((win = (t_win*)malloc(sizeof(*win))) == NULL)
	//		return (0);
	//	if ((sphere = (t_spher*)malloc(sizeof(t_spher))) == NULL)
	//		return (0);
	//	if ((super = (t_super*)malloc(sizeof(*super))) == NULL)
	//		exit(0);
	//	if ((super->win = (t_win*)malloc(sizeof(*super->win))) == NULL)
	//		exit(0);


	//
	//	if (argc == 2)
	super->list = rt_parser_main(argc, argv, &super->cam, super->win);
	printf ("camera : pos x=%f y=%f z=%f rot x=%f y=%f z=%f\n", super->cam->cam_org->x, super->cam->cam_org->y, super->cam->cam_org->z, super->cam->cam_rot->x, super->cam->cam_rot->y, super->cam->cam_rot->z );
	if ((super->phase->getcoor = (unsigned int *)malloc(sizeof(int) * ((super->win->x_img + 2) * (super->win->y_img + 2)))) == NULL)
		exit(0);
	//	sphere->pos = new_params_vec(0.0, 0.0, -20);
	//	sphere->radius = 2;
	//	sphere->color = new_params_vec(1.0, 0.32, 0.36);
	//	sphere->refl = 1;
	//	sphere->trans = 0.5;
	//	sphere->emi = new_params_vec(0, 0, 0);
	//	sphere->ps = new_params_pspher(2, 1, 0.5);
	//	sphere = new_params_spher(new_params_vec(0.0, 0.0, -20), sphere->color = new_params_vec(1.0, 0.32, 0.36),  new_params_vec(0, 0, 0),new_params_pspher(2, 1, 0.5));
	//	list = ft_lstnew_2(new_params_spher(new_params_vec(0.0, 0.0, -20),
	//			new_params_vec(1.0, 0.32, 0.36) ,new_params_pspher(2, 1, 0.5)), 1000);
	//	test_list(list);
	//	printf("ewfwegerhrhtsrt\n");
	//	sphere->pos = new_params_vec(5.0, -3.0, -15);
	//	sphere->radius = 2;
	//	sphere->color = new_params_vec(1.0, 0.32, 0.36);
	//	sphere->refl = 1;
	//	sphere->trans = 0.5;
	//	sphere->emi = new_params_vec(0, 0, 0);
	//	tmp = ft_lstnew_2(new_params_spher(new_params_vec(5.0, -3.0, -15.0),
	//			new_params_vec(1.0, 0.32, 0.36),  new_params_pspher(2, 1, 0.5)), sizeof(void*));
	//	test_list(tmp);
	//	ft_lstadd_2(&list, tmp);



	super->win->mlx = mlx_init(); //<--- CETTE MERDE LEAK

	//	while (1)
	//		;

	//	while (1)
	///		;
	//	ft_putstr("ewfewqgrtrwhsyefweef\n");

	i = 0;
	//	while (i < THREADS)
	//	{
	//		if ((super->thread[i] = (t_thread*)malloc(sizeof(*super->thread[i]))) == NULL)
	//			exit(0);
	//		setup_thread(super->thread[i]);
	//		i++;
	//	}



	super->win->win = mlx_new_window(super->win->mlx, super->win->x_win, super->win->y_win, "RT Mamene");


	if (1)
		super->win->img = mlx_new_image(super->win->mlx, super->win->x_img, super->win->y_img);
	else
		super->win->img = mlx_new_image(super->win->mlx, super->win->x_win * 2, super->win->y_win * 2);

	super->win->img_las = mlx_new_image(super->win->mlx, super->win->x_win, 10);
	super->win->img_loa = mlx_new_image(super->win->mlx, 1200, 800);
	super->win->img2 = mlx_new_image(super->win->mlx, super->win->x_win / 2, 25);
	super->win->img3 = mlx_new_image(super->win->mlx, super->win->x_win, super->win->y_win);
	super->win->addr = mlx_get_data_addr(super->win->img, &super->win->bpp, &super->win->sizeline, &super->win->endian);
	super->win->addr2 = mlx_get_data_addr(super->win->img2, &super->win->bpp2, &super->win->sizeline2, &super->win->endian2);
	super->win->addr3 = mlx_get_data_addr(super->win->img3, &super->win->bpp3, &super->win->sizeline3, &super->win->endian3);
	super->win->addr_las = mlx_get_data_addr(super->win->img_las, &super->win->bpp_las, &super->win->sizeline_las, &super->win->endian_las);

	super->win->addr_loa = mlx_get_data_addr(super->win->img_loa, &super->win->bpp_loa, &super->win->sizeline_loa, &super->win->endian_loa);
	//	test_img(super->win);
	//render(sphere, win, list);
	super->thread_1->list = super->list;
	super->thread_1->win = super->win;
	//	super->thread_2->list = super->list;
	//	super->thread_2->win = super->win;
	//	super->thread_3->list = super->list;
	//	super->thread_3->win = super->win;
	///	super->thread_4->list = super->list;
	//	super->thread_4->win = super->win;

	i = 0;
	while (i < THREADS)
	{
		super->thread[i]->list = super->list;
		super->thread[i]->win = super->win;
		i++;
	}


	//		r_render(super);
	//	apply_antiaaaliasing(super->win);

	//		super->list = 0;
	//	test_list(super->list);
	//	test_color();
	//	while (1)
	//	;
	//	mlx_put_image_to_window(super->win->mlx, super->win->win, super->win->img, 0, 0);

	mlx_key_hook(super->win->win, key_hook, &super->win);
	mlx_hook(super->win->win, 17, (1L << 17), rt_close, NULL);
	mlx_loop_hook(super->win->mlx, rt_loop, super);
	mlx_loop(super->win->mlx);
	return (0);
}
