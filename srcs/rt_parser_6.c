/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parser_6.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juthomas <juthomas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/08 07:54:53 by juthomas          #+#    #+#             */
/*   Updated: 2018/04/08 07:58:43 by juthomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt.h"

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
