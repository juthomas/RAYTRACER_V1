/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juthomas <juthomas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 03:23:06 by juthomas          #+#    #+#             */
/*   Updated: 2018/04/08 23:44:34 by juthomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt.h"

int		exit_error(int error)
{
	ft_putstr_fd("Parser :\n", 2);
	if (error == -1)
		ft_putstr_fd("Erreur avec les nombres\n", 2);
	else if (error == -2)
		ft_putstr_fd("Erreur avec l'orthographe des parametres\n", 2);
	else if (error == -3)
		ft_putstr_fd("Erreur d'argument\nEssaye avec <./rtv2 \"map\">\n", 2);
	else if (error == -4)
		ft_putstr_fd("Erreur de balise\n", 2);
	else if (error == -9)
		ft_putstr_fd("Erreur avec les nombres (Fov > 90)\n", 2);
	else
		ft_putstr_fd("Erreur non repertoriée\n", 2);
	return (error);
}

int		rt_parser_no_space(char *str, int i)
{
	while (str[i] != '\0' && (str[i] == ' ' || str[i] == '\t'))
		i++;
	return (i);
}

int		rt_parser_balise_name(char *str, int i, int *state)
{
	if (ft_strncmp(&str[i], "SCN", 3) == 0)
		*state = 4;
	else if (ft_strncmp(&str[i], "/", 1) == 0)
		*state = 0;
	else if (ft_strncmp(&str[i], "camera(s)", 9) == 0)
		*state = 1;
	else if (ft_strncmp(&str[i], "lightspot(s)", 12) == 0)
		*state = 2;
	else if (ft_strncmp(&str[i], "objet(s)", 8) == 0)
		*state = 3;
	else
		*state = -1;
	while (str[i] != '>' && str[i] != '\0')
		i++;
	return (i);
}

int		rt_parser_go_next_number(char *str, int i)
{
	int		tmp;

	tmp = i;
	while (((str[tmp] >= '0' && str[tmp] <= '9') || str[tmp] == '.' || str[tmp] == '-'))
		tmp++;
	if (str[tmp] != ' ' && str[tmp] != '	' && str[tmp] != '}' && tmp == i)
		return (-1);
	while (str[tmp] == ' ' || str[tmp] == '	')
		tmp++;
	if (!((str[i] >= '0' && str[i] <= '9') || str[i] == '-' || str[i] == '}'))
		return (-1);
	return (tmp);
}

int		rt_parser_stock_vec(char *str, t_vec *vec, int *nb, int dec)
{
	int		i;
	int		nu_of_params;

	nu_of_params = 0;
	i = *nb + dec;
	while (str[i] == ' ' || str[i] == '	')
		i++;
	while (str[i] != '\0' && ((str[i] >= '0' && str[i] <= '9') || str[i] == '.'
				|| str[i] == ' ' || str[i] == '	' || str[i] == '-'))
	{
		if (nu_of_params == 0)
			vec->x = ft_adolphe(&str[i]);
		else if (nu_of_params == 1)
			vec->y = ft_adolphe(&str[i]);
		else if (nu_of_params == 2)
			vec->z = ft_adolphe(&str[i]);
		if ((i = rt_parser_go_next_number(str, i)) == -1)
			exit(exit_error(-1));
		nu_of_params++;
	}
	*nb = i + 1;
	if (str[i] != '}' || nu_of_params != 3)
		return (-1);
	return (0);
}

int		rt_parser_is_correct(char *str, char *ac, int len)
{
	int		i;
	int		u;
	int		lenac;
	int		ok;

	ok = 1;
	u = 0;
	i = 0;
	lenac = ft_strlen(ac);
	while (i < len)
	{
		ok = 1;
		u = 0;
		while (u < lenac && ok)
		{
			if (str[i] == ac[u])
				ok = 0;
			u++;
		}
		if (ok)
			return (0);
		i++;
	}
	return (1);
}

int		rt_parser_stock_color_norm(int *tmp, t_vec *vec, unsigned int color, char *str)
{
	while (str[*tmp] == '	' || str[*tmp] == ' ')
		*tmp = *tmp + 1;
	if (str[*tmp] != ')')
		return (-1);
	vec->x = color / 256 / 256 % 256;
	vec->y = color / 256 % 256;
	vec->z = color % 256;
	if (NORM_COLOR == 1)
	{
		vec->x /= 255;
		vec->y /= 255;
		vec->z /= 255;
	}
	return (0);
}

int		rt_parser_stock_color(char *str, t_vec *vec, int *nb, int dec)
{
	int				i;
	unsigned int	color;

	i = *nb + dec;
	while (str[i] == ' ' || str[i] == '	')
		i++;
	if (ft_strncmp(&str[i], "0X", 2) && rt_parser_is_correct(&str[i + 2],
				"0123456789ABCDEF", 6))
		color = ft_atoi_base(&str[i + 2], "0123456789ABCDEF");
	else if (ft_strncmp(&str[i], "0x", 2) && rt_parser_is_correct(&str[i + 2],
				"0123456789ABCDEF", 6))
		color = ft_atoi_base(&str[i + 2], "0123456789ABCDEF");
	else if (ft_strncmp(&str[i], "0X", 2) && rt_parser_is_correct(&str[i + 2],
				"0123456789abcdef", 6))
		color = ft_atoi_base(&str[i + 2], "0123456789abcdef");
	else if (ft_strncmp(&str[i], "0x", 2) && rt_parser_is_correct(&str[i + 2],
				"0123456789abcdef", 6))
		color = ft_atoi_base(&str[i + 2], "0123456789abcdef");
	else
		return (-1);
	i = i + 8;
	if (rt_parser_stock_color_norm(&i, vec, color, str) == -1)
		return (-1);
	*nb = i + 1;
	return (0);
}

int		rt_parser_go_next_number_2(char *str, int i)
{
	int		tmp;

	tmp = i;
	while (((str[tmp] >= '0' && str[tmp] <= '9') || str[tmp] == '.'
				|| str[tmp] == '-'))
		tmp++;
	if (str[tmp] != ' ' && str[tmp] != ')' && tmp == i)
		return (-1);
	while (str[tmp] == ' ' || str[tmp] == '	')
		tmp++;
	if (!((str[tmp] == ')')))
		return (-1);
	return (tmp);
}

int		rt_parser_stock_number(char *str, float *nu, int *nb, int dec)
{
	int		i;
	int		tmp;

	i = *nb + dec;
	while (str[i] == ' ' || str[i] == '	')
		i++;
	tmp = i;
	if ((i = rt_parser_go_next_number_2(str, i)) == -1)
		return (-1);
	*nu = ft_adolphe(&str[tmp]);
	*nb = i + 1;
	return (0);
}

int		stock_triangle(t_triangle *triangle, char *str, int *nb)
{
	int		i;

	i = *nb;
	if (ft_strncmp(&str[i], "O1{", 3) == 0
			|| ft_strncmp(&str[i], "o1{", 3) == 0)
		return (rt_parser_stock_vec(str, triangle->p1, nb, 3));
	else if (ft_strncmp(&str[i], "O2{", 3) == 0
			|| ft_strncmp(&str[i], "o2{", 3) == 0)
		return (rt_parser_stock_vec(str, triangle->p2, nb, 3));
	else if (ft_strncmp(&str[i], "O3{", 3) == 0
			|| ft_strncmp(&str[i], "o3{", 3) == 0)
		return (rt_parser_stock_vec(str, triangle->p3, nb, 3));
	else if (ft_strncmp(&str[i], "Couleur(", 8) == 0
			|| ft_strncmp(&str[i], "couleur(", 8) == 0)
		return (rt_parser_stock_color(str, triangle->color, nb, 8));
	else if (ft_strncmp(&str[i], "Reflexion(", 10) == 0 
			|| ft_strncmp(&str[i], "reflexion(", 10) == 0)
		return (rt_parser_stock_number(str, &triangle->pbas->refl, nb, 10));
	else if (ft_strncmp(&str[i], "Opacity(", 8) == 0
			|| ft_strncmp(&str[i], "opacity(", 8) == 0)
		return (rt_parser_stock_number(str, &triangle->pbas->opac, nb, 8));
	return (-2);
}

int		stock_cycon(t_cycon *cycon, char *str, int *nb)
{
	int		i;

	i = *nb;
	if (ft_strncmp(&str[i], "Origine{", 8) == 0
			|| ft_strncmp(&str[i], "origine{", 8) == 0)
		return(rt_parser_stock_vec(str, cycon->pos, nb, 8));
	else if (ft_strncmp(&str[i], "Rotation{", 9) == 0
			|| ft_strncmp(&str[i], "rotation{", 9) == 0)
		return(rt_parser_stock_vec(str, cycon->rot, nb, 9));
	else if (ft_strncmp(&str[i], "Rayon(", 6) == 0
			|| ft_strncmp(&str[i], "rayon(", 6) == 0)
		return(rt_parser_stock_number(str, &cycon->pc->radius, nb, 6));
	else if (ft_strncmp(&str[i], "Hauteur(", 8) == 0
			|| ft_strncmp(&str[i], "hauteur(", 8) == 0)
		return(rt_parser_stock_number(str, &cycon->pc->height, nb, 8));
	else if (ft_strncmp(&str[i], "Couleur(", 8) == 0
			|| ft_strncmp(&str[i], "couleur(", 8) == 0)
		return(rt_parser_stock_color(str, cycon->color, nb, 8));
	else if (ft_strncmp(&str[i], "Reflexion(", 10) == 0
			|| ft_strncmp(&str[i], "reflexion(", 10) == 0)
		return(rt_parser_stock_number(str, &cycon->pc->refl, nb, 10));
	else if (ft_strncmp(&str[i], "Opacity(", 8) == 0
			|| ft_strncmp(&str[i], "opacity(", 8) == 0)
		return(rt_parser_stock_number(str, &cycon->pc->opac, nb, 8));
	return (-2);
}


int		stock_plan(t_plan *plan, char *str, int *nb)
{
	int		state;
	int		i;

	state = -1;
	i = *nb;
	if (ft_strncmp(&str[i], "Origine{", 8) == 0
			|| ft_strncmp(&str[i], "origine{", 8) == 0)
		state = rt_parser_stock_vec(str, plan->pos, nb, 8);
	else if (ft_strncmp(&str[i], "Rotation{", 9) == 0
			|| ft_strncmp(&str[i], "rotation{", 9) == 0)
		state = rt_parser_stock_vec(str, plan->rot, nb, 9);
	else if (ft_strncmp(&str[i], "Couleur(", 8) == 0
			|| ft_strncmp(&str[i], "couleur(", 8) == 0)
		state = rt_parser_stock_color(str, plan->color, nb, 8);
	else if (ft_strncmp(&str[i], "Reflexion(", 10) == 0
			|| ft_strncmp(&str[i], "reflexion(", 10) == 0)
		state = rt_parser_stock_number(str, &plan->pbasic->refl, nb, 10);
	else if (ft_strncmp(&str[i], "Opacity(", 8) == 0
			|| ft_strncmp(&str[i], "opacity(", 8) == 0)
		state = rt_parser_stock_number(str, &plan->pbasic->opac, nb, 8);
	else
		state = -2;
	return (state);
}

int		stock_disque(t_disque *disque, char *str, int *nb)
{
	int		i;

	i = *nb;
	if (ft_strncmp(&str[i], "Origine{", 8) == 0
			|| ft_strncmp(&str[i], "origine{", 8) == 0)
		return (rt_parser_stock_vec(str, disque->pos, nb, 8));
	else if (ft_strncmp(&str[i], "Rotation{", 9) == 0
			|| ft_strncmp(&str[i], "rotation{", 9) == 0)
		return (rt_parser_stock_vec(str, disque->rot, nb, 9));
	else if (ft_strncmp(&str[i], "Couleur(", 8) == 0
			|| ft_strncmp(&str[i], "couleur(", 8) == 0)
		return (rt_parser_stock_color(str, disque->color, nb, 8));
	else if (ft_strncmp(&str[i], "Reflexion(", 10) == 0
			|| ft_strncmp(&str[i], "reflexion(", 10) == 0)
		return (rt_parser_stock_number(str, &disque->pdisque->refl, nb, 10));
	else if (ft_strncmp(&str[i], "Opacity(", 8) == 0
			|| ft_strncmp(&str[i], "opacity(", 8) == 0)
		return (rt_parser_stock_number(str, &disque->pdisque->opac, nb, 8));
	else if (ft_strncmp(&str[i], "Rayon(", 6) == 0
			|| ft_strncmp(&str[i], "rayon(", 6) == 0)
		return (rt_parser_stock_number(str, &disque->pdisque->radius, nb, 6));
	return (-2);
}



int		stock_spher(t_spher *spher, char *str, int *nb)
{
	int		state;
	int		i;

	state = -1;
	i = *nb;
	if (ft_strncmp(&str[i], "Origine{", 8) == 0
			|| ft_strncmp(&str[i], "origine{", 8) == 0)
		state = rt_parser_stock_vec(str, spher->pos, nb, 8);
	else if (ft_strncmp(&str[i], "Rayon(", 6) == 0
			|| ft_strncmp(&str[i], "rayon(", 6) == 0)
		state = rt_parser_stock_number(str, &spher->pspher->radius, nb, 6);
	else if (ft_strncmp(&str[i], "Couleur(", 8) == 0
			|| ft_strncmp(&str[i], "couleur(", 8) == 0)
		state = rt_parser_stock_color(str, spher->color, nb, 8);
	else if (ft_strncmp(&str[i], "Reflexion(", 10) == 0
			|| ft_strncmp(&str[i], "reflexion(", 10) == 0)
		state = rt_parser_stock_number(str, &spher->pspher->refl, nb, 10);
	else if (ft_strncmp(&str[i], "Opacity(", 8) == 0
			|| ft_strncmp(&str[i], "opacity(", 8) == 0)
		state = rt_parser_stock_number(str, &spher->pspher->opac, nb, 8);
	else
		state = -2;
	return (state);
}


int		stock_lpsher(t_lspher *spher, char *str, int *nb)
{
	int		i;

	i = *nb;
	if (ft_strncmp(&str[i], "Origine{", 8) == 0
			|| ft_strncmp(&str[i], "origine{", 8) == 0)
		return (rt_parser_stock_vec(str, spher->pos, nb, 8));
	else if (ft_strncmp(&str[i], "Rayon(", 6) == 0
			|| ft_strncmp(&str[i], "rayon(", 6) == 0)
		return (rt_parser_stock_number(str, &spher->lpspher->radius, nb, 6));
	else if (ft_strncmp(&str[i], "Couleur(", 8) == 0
			|| ft_strncmp(&str[i], "couleur(", 8) == 0)
		return (rt_parser_stock_color(str, spher->color, nb, 8));
	else if (ft_strncmp(&str[i], "Emission(", 9) == 0
			|| ft_strncmp(&str[i], "emission(", 9) == 0)
		return (rt_parser_stock_number(str, &spher->lpspher->emi, nb, 9));
	else if (ft_strncmp(&str[i], "laser", 5) == 0
			|| ft_strncmp(&str[i], "laser", 5) == 0)
	{
		spher->lpspher->type = 1;
		*nb = *nb + 5;
		return (0);
	}
	return (-2);
}

int		stock_camera(t_cam *cam, char *str, int *nb)
{
	int		state;
	int		i;

	state = -1;
	i = *nb;
	if (ft_strncmp(&str[i], "Origine{", 8) == 0
			|| ft_strncmp(&str[i], "origine{", 8) == 0)
		state = rt_parser_stock_vec(str, cam->cam_org, nb, 8);
	else if (ft_strncmp(&str[i], "Rotation{", 9) == 0
			|| ft_strncmp(&str[i], "rotation{", 9) == 0)
		state = rt_parser_stock_vec(str, cam->cam_rot, nb, 9);
	else
		state = -2;
	return (state);
}


int		stock_lproj_norm(t_lproj *proj, char *str, int *nb)
{
	int		state;
	int		i;

	i = *nb;
	state = -1;
	if (ft_strncmp(&str[i], "Fov(", 4) == 0
			|| ft_strncmp(&str[i], "fov(", 4) == 0)
	{
		state = rt_parser_stock_number(str, &proj->lpproj->fov, nb, 4);
		if (proj->lpproj->fov > 90)
			state = -9;
	}
	else if (ft_strncmp(&str[i], "laser", 5) == 0 || ft_strncmp(&str[i], "laser", 5) == 0)
	{
		proj->lpproj->type = 1;
		state = 0;
		*nb = *nb + 5;
	}
	else
		state = -2;
	return (state);
}

int		stock_lproj(t_lproj *proj, char *str, int *nb)
{
	int		i;

	i = *nb;
	if (ft_strncmp(&str[i], "Origine{", 8) == 0
			|| ft_strncmp(&str[i], "origine{", 8) == 0)
		return (rt_parser_stock_vec(str, proj->pos, nb, 8));
	else if (ft_strncmp(&str[i], "Direction{", 10) == 0
			|| ft_strncmp(&str[i], "direction{", 10) == 0)
		return (rt_parser_stock_vec(str, proj->dir, nb, 10));
	else if (ft_strncmp(&str[i], "Rayon(", 6) == 0
			|| ft_strncmp(&str[i], "rayon(", 6) == 0)
		return (rt_parser_stock_number(str, &proj->lpproj->radius, nb, 6));
	else if (ft_strncmp(&str[i], "Couleur(", 8) == 0
			|| ft_strncmp(&str[i], "couleur(", 8) == 0)
		return (rt_parser_stock_color(str, proj->color, nb, 8));
	else if (ft_strncmp(&str[i], "Emission(", 9) == 0
			|| ft_strncmp(&str[i], "emission(", 9) == 0)
		return (rt_parser_stock_number(str, &proj->lpproj->emi, nb, 9));
	return (stock_lproj_norm(proj, str, nb));
}

void	rt_parser_objtype_lspher_setup(t_lspher *spher)
{
	spher->pos->x = 0;
	spher->pos->y = 0;
	spher->pos->z = 0;
	spher->color->x = 0;
	spher->color->y = 0;
	spher->color->z = 0;
	spher->lpspher->radius = 0;
	spher->lpspher->emi = 0;
	spher->lpspher->type = 0;
}

void	rt_parser_objtype_camera_setup(t_cam *cam)
{
	cam->cam_org->x = 0;
	cam->cam_org->y = 0;
	cam->cam_org->z = 0;
	cam->cam_rot->x = 0;
	cam->cam_rot->y = 0;
	cam->cam_rot->z = 0;
}


void	rt_parser_objtype_lproj_setup(t_lproj *proj)
{
	proj->pos->x = 0;
	proj->pos->y = 0;
	proj->pos->z = 0;
	proj->color->x = 0;
	proj->color->y = 0;
	proj->color->z = 0;
	proj->dir->x = 0;
	proj->dir->y = 0;
	proj->dir->z = 0;
	proj->lpproj->type = 0;
	proj->lpproj->radius = 0;
	proj->lpproj->emi = 0;
	proj->lpproj->fov = 0;
}



char	rt_parser_objtype_lspher(char *str, void **addr, char type)
{
	int		i;
	int		state;
	t_lspher		*spher;

	state = 0;
	i = 0;
	if ((spher = (t_lspher*)malloc(sizeof(*spher))) == NULL)
		exit(-1);
	if ((spher->lpspher = (t_lpspher*)malloc(sizeof(*spher->lpspher))) == NULL)
		exit(-1);
	if ((spher->pos = (t_vec*)malloc(sizeof(*spher->pos))) == NULL)
		exit(-1);
	if ((spher->color = (t_vec*)malloc(sizeof(*spher->color))) == NULL)
		exit(-1);
	rt_parser_objtype_lspher_setup(spher);
	while (str[i] != '\0' && state == 0)
	{
		i = rt_parser_no_space(str, i);
		if (str[i] != '\0' && ((state = stock_lpsher(spher, str, &i)) < 0))
			exit(exit_error(state));
	}
	*addr = spher;
	return (type);
}

void	rt_parser_objtype_camera(char *str, t_cam *cam, char type)
{
	int		i;
	int		state;

	state = 0;
	i = 0;
	if ((cam->cam_org = (t_vec*)malloc(sizeof(*cam->cam_org))) == NULL)
		exit(-1);
	if ((cam->cam_rot = (t_vec*)malloc(sizeof(*cam->cam_rot))) == NULL)
		exit(-1);
	rt_parser_objtype_camera_setup(cam);
	while (str[i] != '\0' && state == 0)
	{
		i = rt_parser_no_space(str, i);
		if (str[i] != '\0' && ((state = stock_camera(cam, str, &i)) < 0))
			exit(exit_error(state));
	}
	check_vec_dir(cam->cam_rot);
}



char	rt_parser_objtype_lproj(char *str, void **addr, char type)
{
	int		i;
	int		state;
	t_lproj		*proj;

	state = 0;
	i = 0;
	if ((proj = (t_lproj*)malloc(sizeof(*proj))) == NULL)
		exit(-1);
	if ((proj->lpproj = (t_lpproj*)malloc(sizeof(*proj->lpproj))) == NULL)
		exit(-1);
	if ((proj->pos = (t_vec*)malloc(sizeof(*proj->pos))) == NULL)
		exit(-1);
	if ((proj->color = (t_vec*)malloc(sizeof(*proj->color))) == NULL)
		exit(-1);
	if ((proj->dir = (t_vec*)malloc(sizeof(*proj->dir))) == NULL)
		exit(-1);
	rt_parser_objtype_lproj_setup(proj);
	while (str[i] != '\0' && state == 0)
	{
		i = rt_parser_no_space(str, i);
		if (str[i] != '\0' && ((state = stock_lproj(proj, str, &i)) < 0))
			exit(exit_error(state));
	}
	check_vec_dir(proj->dir);
	*addr = proj;
	return (type);
}

void	rt_parser_objtype_spher_setup(t_spher *spher)
{
	spher->pos->x = 0;
	spher->pos->y = 0;
	spher->pos->z = 0;
	spher->color->x = 0;
	spher->color->y = 0;
	spher->color->z = 0;
	spher->pspher->radius = 0;
	spher->pspher->refl = 0;
	spher->pspher->opac = 0;
}

void	rt_parser_objtype_triangle_setup(t_triangle *triangle)
{
	triangle->p1->x = 0;
	triangle->p1->y = 0;
	triangle->p1->z = 0;
	triangle->p2->x = 0;
	triangle->p2->y = 0;
	triangle->p2->z = 0;
	triangle->p3->x = 0;
	triangle->p3->y = 0;
	triangle->p3->z = 0;
	triangle->color->x = 0;
	triangle->color->y = 0;
	triangle->color->z = 0;
	triangle->pbas->refl = 0;
	triangle->pbas->opac = 0;
}

void	rt_parser_objtype_cycon_setup(t_cycon *cycon)
{
	cycon->pos->x = 0;
	cycon->pos->y = 0;
	cycon->pos->z = 0;
	cycon->rot->x = 0;
	cycon->rot->y = 0;
	cycon->rot->z = 0;
	cycon->color->x = 0;
	cycon->color->y = 0;
	cycon->color->z = 0;
	cycon->pc->radius = 0;
	cycon->pc->height = 0;
	cycon->pc->refl = 0;
	cycon->pc->opac = 0;
}

void	rt_parser_objtype_disque_setup(t_disque *disque)
{
	disque->pos->x = 0;
	disque->pos->y = 0;
	disque->pos->z = 0;
	disque->rot->x = 0;
	disque->rot->y = 0;
	disque->rot->z = 0;
	disque->color->x = 0;
	disque->color->y = 0;
	disque->color->z = 0;
	disque->pdisque->refl = 0;
	disque->pdisque->opac = 0;
	disque->pdisque->radius = 0;
}

void	rt_parser_objtype_plan_setup(t_plan *plan)
{
	plan->pos->x = 0;
	plan->pos->y = 0;
	plan->pos->z = 0;
	plan->rot->x = 0;
	plan->rot->y = 0;
	plan->rot->z = 0;
	plan->color->x = 0;
	plan->color->y = 0;
	plan->color->z = 0;
	plan->pbasic->refl = 0;
	plan->pbasic->opac = 0;
}

void	rt_parser_objtype_triangle_norm(t_triangle *triangle)
{
	if ((triangle->pbas = (t_pbasic*)malloc(sizeof(*triangle->pbas))) == NULL)
		exit(-1);
	if ((triangle->p1 = (t_vec*)malloc(sizeof(*triangle->p1))) == NULL)
		exit(-1);
	if ((triangle->p2 = (t_vec*)malloc(sizeof(*triangle->p2))) == NULL)
		exit(-1);
	if ((triangle->p3 = (t_vec*)malloc(sizeof(*triangle->p3))) == NULL)
		exit(-1);
	if ((triangle->color = (t_vec*)malloc(sizeof(*triangle->color))) == NULL)
		exit(-1);
}

char	rt_parser_objtype_triangle(char *str, void **addr, char type)//todo
{
	int		i;
	int		state;
	t_triangle		*triangle;

	state = 0;
	i = 0;
	if ((triangle = (t_triangle*)malloc(sizeof(*triangle))) == NULL)
		exit(-1);
	rt_parser_objtype_triangle_norm(triangle);
	rt_parser_objtype_triangle_setup(triangle);
	while (str[i] != '\0' && state == 0)
	{
		i = rt_parser_no_space(str, i);
		if (str[i] != '\0' && ((state = stock_triangle(triangle, str, &i)) < 0))
			exit(exit_error(state));
	}
	*addr = triangle;
	return (type);
}

char	rt_parser_objtype_cycon(char *str, void **addr, char type)
{
	int		i;
	int		state;
	t_cycon		*cycon;

	state = 0;
	i = 0;
	if ((cycon = (t_cycon*)malloc(sizeof(*cycon))) == NULL)
		exit(-1);
	if ((cycon->pc = (t_pcycon*)malloc(sizeof(*cycon->pc))) == NULL)
		exit(-1);
	if ((cycon->pos = (t_vec*)malloc(sizeof(*cycon->pos))) == NULL)
		exit(-1);
	if ((cycon->rot = (t_vec*)malloc(sizeof(*cycon->rot))) == NULL)
		exit(-1);
	if ((cycon->color = (t_vec*)malloc(sizeof(*cycon->color))) == NULL)
		exit(-1);
	rt_parser_objtype_cycon_setup(cycon);
	while (str[i] != '\0' && state == 0)
	{
		i = rt_parser_no_space(str, i);
		if (str[i] != '\0' && ((state = stock_cycon(cycon, str, &i)) < 0))
			exit(exit_error(state));
	}
	check_vec_dir(cycon->rot);
	*addr = cycon;
	return (type);
}

char	rt_parser_objtype_plan(char *str, void **addr, char type)//todo
{
	int		i;
	int		state;
	t_plan		*plan;

	state = 0;
	i = 0;
	if ((plan = (t_plan*)malloc(sizeof(*plan))) == NULL)
		exit(-1);
	if ((plan->pbasic = (t_pbasic*)malloc(sizeof(*plan->pbasic))) == NULL)
		exit(-1);
	if ((plan->pos = (t_vec*)malloc(sizeof(*plan->pos))) == NULL)
		exit(-1);
	if ((plan->rot = (t_vec*)malloc(sizeof(*plan->rot))) == NULL)
		exit(-1);
	if ((plan->color = (t_vec*)malloc(sizeof(*plan->color))) == NULL)
		exit(-1);
	rt_parser_objtype_plan_setup(plan);
	while (str[i] != '\0' && state == 0)
	{
		i = rt_parser_no_space(str, i);
		if (str[i] != '\0' && ((state = stock_plan(plan, str, &i)) < 0))
			exit(exit_error(state));
	}
	check_vec_dir(plan->rot);
	*addr = plan;
	return (type);
}

char	rt_parser_objtype_disque(char *str, void **addr, char type)//todo
{
	int		i;
	int		state;
	t_disque		*disq;

	state = 0;
	i = 0;
	if ((disq = (t_disque*)malloc(sizeof(*disq))) == NULL)
		exit(-1);
	if ((disq->pdisque = (t_pdisque*)malloc(sizeof(*disq->pdisque))) == NULL)
		exit(-1);
	if ((disq->pos = (t_vec*)malloc(sizeof(*disq->pos))) == NULL)
		exit(-1);
	if ((disq->rot = (t_vec*)malloc(sizeof(*disq->rot))) == NULL)
		exit(-1);
	if ((disq->color = (t_vec*)malloc(sizeof(*disq->color))) == NULL)
		exit(-1);
	rt_parser_objtype_disque_setup(disq);
	while (str[i] != '\0' && state == 0)
	{
		i = rt_parser_no_space(str, i);
		if (str[i] != '\0' && ((state = stock_disque(disq, str, &i)) < 0))
			exit(exit_error(state));
	}
	*addr = disq;
	return (type);
}

char	rt_parser_objtype_spher(char *str, void **addr, char type)
{
	int		i;
	int		state;
	t_spher		*spher;

	state = 0;
	i = 0;
	if ((spher = (t_spher*)malloc(sizeof(*spher))) == NULL)
		exit(-1);
	if ((spher->pspher = (t_pspher*)malloc(sizeof(*spher->pspher))) == NULL)
		exit(-1);
	if ((spher->pos = (t_vec*)malloc(sizeof(*spher->pos))) == NULL)
		exit(-1);
	if ((spher->color = (t_vec*)malloc(sizeof(*spher->color))) == NULL)
		exit(-1);
	rt_parser_objtype_spher_setup(spher);
	while (str[i] != '\0' && state == 0)
	{
		i = rt_parser_no_space(str, i);
		if (str[i] != '\0' && ((state = stock_spher(spher, str, &i)) < 0))
			exit(exit_error(state));
	}
	*addr = spher;
	return (type);
}

char	rt_parser_objtype(char *str)
{
	char	type;

	if (ft_strncmp(str, "Sphere:", 7) == 0
			|| ft_strncmp(str, "sphere:", 7) == 0)
		type = 's';
	else if (ft_strncmp(str, "Cylindre", 8) == 0
			|| ft_strncmp(str, "cylindre", 8) == 0)
		type = 'c';
	else if (ft_strncmp(str, "Cone", 4) == 0 || ft_strncmp(str, "cone", 4) == 0)
		type = 'k';
	else if (ft_strncmp(str, "Plan", 4) == 0 || ft_strncmp(str, "plan", 4) == 0)
		type = 'p';
	else if (ft_strncmp(str, "Triangle:", 9) == 0
			|| ft_strncmp(str, "triangle:", 9) == 0)
		type = 't';
	else if (ft_strncmp(str, "Disque", 6) == 0
			|| ft_strncmp(str, "disque", 6) == 0)
		type = 'd';
	else if (ft_strncmp(str, "Projecteur", 10) == 0
			|| ft_strncmp(str, "projecteur", 10) == 0)
		type = 'l';
	else
		type = 0;
	return (type);
}

char	rt_parser_camera(char *str)
{
	char	type;

	if (ft_strncmp(str, "Camera_1:", 9) == 0
			|| ft_strncmp(str, "camera_1:", 9) == 0)
		type = 'V';
	else
		type = 0;
	return (type);
}

t_type	*rt_parser_objtype_done(char *str, char type)
{
	t_type *typ;

	if ((typ = (t_type*)malloc(sizeof(*typ))) == NULL)
		exit(-1);
	if (type == 's')
		typ->name = rt_parser_objtype_spher(&str[7], &typ->obj, 's');
	else if (type == 't')
		typ->name = rt_parser_objtype_triangle(&str[9], &typ->obj, 't');
	else if (type == 'c')
		typ->name = rt_parser_objtype_cycon(&str[9], &typ->obj, 'c');
	else if (type == 'k')
		typ->name = rt_parser_objtype_cycon(&str[5], &typ->obj, 'k');
	else if (type == 'p')
		typ->name = rt_parser_objtype_plan(&str[5], &typ->obj, 'p');
	else if (type == 'd')
		typ->name = rt_parser_objtype_disque(&str[7], &typ->obj, 'd');
	return (typ);
}


t_type	*rt_parser_lobjtype_done(char *str, char type)
{
	t_type *typ;
	t_lspher *spher;
	t_lproj		*proj;

	if ((typ = (t_type*)malloc(sizeof(*typ))) == NULL)
		exit(-1);
	if (type == 's')
	{

		typ->name = rt_parser_objtype_lspher(&str[7], &typ->obj, 'S');
		if (typ->obj)
			spher = typ->obj;
	}
	if (type == 'l')
	{
		typ->name = rt_parser_objtype_lproj(&str[11], &typ->obj, 'L');
		if (typ->obj)
			proj = typ->obj;
	}
	return (typ);
}

t_cam	*rt_parser_camera_done(char *str, char type)
{
	t_cam	*cam;

	if ((cam = (t_cam*)malloc(sizeof(*cam))) == NULL)
		exit(-1);
	if (type == 'V')
		rt_parser_objtype_camera(&str[9], cam, 'S');
	return (cam);
}


int		rt_parser_state(char *str, int state, int i)
{
	if (str[i++] == '<')
		rt_parser_balise_name(str, i, &state);
	return (state);
}


void	ft_lstdellast(t_list **list)
{
	t_list	*tmp;

	tmp = *list;
	while ((tmp)->next)
	{
		if (tmp->next->next == 0)
		{
			ft_memdel((void**)(tmp)->next);
			free((tmp->next));
			(tmp)->next = NULL;
			return ;
		}
		(tmp) = (tmp)->next;
	}
}

t_list	*ft_lstnew2(void *content, size_t content_size, int *vo)
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
	*vo = 0;
	return (new);
}

void	rt_parser_stock_win(char *str, t_win *win)
{
	int		tmp_x;
	int		tmp_y;
	int		i;

	i = 0;
	tmp_x = ft_atoi(str);
	while (str[i] >= '0' && str[i] <= '9')
		i++;
	if (str[i] != 'x' || i < 1)
		return ;
	i++;
	tmp_y = ft_atoi(&str[i]);
	while (str[i] >= '0' && str[i] <= '9')
		i++;
	if (str[i] != '}' || i < 1)
		return ;
	if (tmp_x > 0 && tmp_y > 0 && tmp_x < 5000 && tmp_y < 5000)
	{
		win->x_win = tmp_x;
		win->y_win = tmp_y;
	}
}


void	rt_parser_main_setup(int argc, char **argv, t_parser *parser, t_win *win)
{
	parser->i = 0;
	parser->state = 0;
	if (argc != 2)
		exit(exit_error(-3));
	parser->vo = 1;
	win->x_win = 1200;
	win->y_win = 800;
	if ((parser->fd = open(argv[1], O_RDONLY)) <= 0)
		exit(exit_error(-3));
}

t_list	*rt_parser_main_end(t_parser *parser, t_list *list, t_win *win)
{
	free(parser->line);
	ft_lstdellast(&list);
	win->x_img = win->x_win * 2;
	win->y_img = win->y_win * 2;
	if (parser->vo)
	{
		free(list);
		free(parser);
		return (NULL);
	}
	free(parser);
	return (list);
}

void	rt_parser_main_while(t_parser *parser, t_cam **cam, t_list *list, t_win *win)
{
	parser->i = 0;
	parser->i = rt_parser_no_space(parser->line, parser->i);
	if ((parser->state = rt_parser_state(parser->line, parser->state, parser->i)) == -1)
		exit(exit_error(-4));
	if (ft_strncmp(&parser->line[parser->i], "window:{", 8) == 0 || ft_strncmp(&parser->line[parser->i], "window:{", 8) == 0)
		rt_parser_stock_win(&parser->line[parser->i + 8], win);
}

t_list	*rt_parser_main(int argc, char **argv, t_cam **cam, t_win *win)
{
	t_parser	*parser;
	t_list	*list;

	if ((parser = (t_parser*)malloc(sizeof(t_parser))) == NULL)
		exit(-1);
	rt_parser_main_setup(argc, argv, parser, win);
	list = ft_lstnew(0, 0);
	while (get_next_line(parser->fd, &parser->line) == 1)
	{
		rt_parser_main_while(parser, cam, list, win);
		if ((parser->state == 1) && ((parser->obj_name
						= rt_parser_camera(&parser->line[parser->i])) != 0))
			*cam = rt_parser_camera_done(&parser->line[parser->i],
					parser->obj_name);
		else if ((parser->state == 2) && ((parser->obj_name =
						rt_parser_objtype(&parser->line[parser->i])) != 0))
			ft_lstadd(&list,ft_lstnew2(rt_parser_lobjtype_done(
	&parser->line[parser->i], parser->obj_name), sizeof(t_type), &parser->vo));
		else if ((parser->state == 3) && ((parser->obj_name =
						rt_parser_objtype(&parser->line[parser->i])) != 0))
			ft_lstadd(&list, ft_lstnew2(rt_parser_objtype_done(
	&parser->line[parser->i], parser->obj_name), sizeof(t_type), &parser->vo));
		free(parser->line);
	}
	return (rt_parser_main_end(parser, list, win));
}
