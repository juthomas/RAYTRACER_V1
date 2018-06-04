/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parser_4.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juthomas <juthomas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/08 07:46:47 by juthomas          #+#    #+#             */
/*   Updated: 2018/04/09 01:53:20 by juthomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt.h"

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
		if (proj->lpproj->fov > 360)
			state = -9;
	}
	else if (ft_strncmp(&str[i], "laser", 5) == 0
			|| ft_strncmp(&str[i], "laser", 5) == 0)
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
