/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parser_3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juthomas <juthomas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/08 07:46:22 by juthomas          #+#    #+#             */
/*   Updated: 2018/04/08 08:30:33 by juthomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt.h"

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
		return (rt_parser_stock_vec(str, cycon->pos, nb, 8));
	else if (ft_strncmp(&str[i], "Rotation{", 9) == 0
			|| ft_strncmp(&str[i], "rotation{", 9) == 0)
		return (rt_parser_stock_vec(str, cycon->rot, nb, 9));
	else if (ft_strncmp(&str[i], "Rayon(", 6) == 0
			|| ft_strncmp(&str[i], "rayon(", 6) == 0)
		return (rt_parser_stock_number(str, &cycon->pc->radius, nb, 6));
	else if (ft_strncmp(&str[i], "Hauteur(", 8) == 0
			|| ft_strncmp(&str[i], "hauteur(", 8) == 0)
		return (rt_parser_stock_number(str, &cycon->pc->height, nb, 8));
	else if (ft_strncmp(&str[i], "Couleur(", 8) == 0
			|| ft_strncmp(&str[i], "couleur(", 8) == 0)
		return (rt_parser_stock_color(str, cycon->color, nb, 8));
	else if (ft_strncmp(&str[i], "Reflexion(", 10) == 0
			|| ft_strncmp(&str[i], "reflexion(", 10) == 0)
		return (rt_parser_stock_number(str, &cycon->pc->refl, nb, 10));
	else if (ft_strncmp(&str[i], "Opacity(", 8) == 0
			|| ft_strncmp(&str[i], "opacity(", 8) == 0)
		return (rt_parser_stock_number(str, &cycon->pc->opac, nb, 8));
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
