/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parser_11.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juthomas <juthomas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/09 00:04:55 by juthomas          #+#    #+#             */
/*   Updated: 2018/04/10 02:24:41 by juthomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt.h"

void	rt_parser_objtype_lproj_norm(t_lproj *proj)
{
	if ((proj->lpproj = (t_lpproj*)malloc(sizeof(*proj->lpproj))) == NULL)
		exit(-1);
	if ((proj->pos = (t_vec*)malloc(sizeof(*proj->pos))) == NULL)
		exit(-1);
	if ((proj->color = (t_vec*)malloc(sizeof(*proj->color))) == NULL)
		exit(-1);
	if ((proj->dir = (t_vec*)malloc(sizeof(*proj->dir))) == NULL)
		exit(-1);
}

void	rt_parser_objtype_cycon_norm(t_cycon *cycon)
{
	if ((cycon->pc = (t_pcycon*)malloc(sizeof(*cycon->pc))) == NULL)
		exit(-1);
	if ((cycon->pos = (t_vec*)malloc(sizeof(*cycon->pos))) == NULL)
		exit(-1);
	if ((cycon->rot = (t_vec*)malloc(sizeof(*cycon->rot))) == NULL)
		exit(-1);
	if ((cycon->color = (t_vec*)malloc(sizeof(*cycon->color))) == NULL)
		exit(-1);
}

void	rt_parser_objtype_plan_norm(t_plan *plan)
{
	if ((plan->pbasic = (t_pbasic*)malloc(sizeof(*plan->pbasic))) == NULL)
		exit(-1);
	if ((plan->pos = (t_vec*)malloc(sizeof(*plan->pos))) == NULL)
		exit(-1);
	if ((plan->rot = (t_vec*)malloc(sizeof(*plan->rot))) == NULL)
		exit(-1);
	if ((plan->color = (t_vec*)malloc(sizeof(*plan->color))) == NULL)
		exit(-1);
}

void	rt_parser_objtype_disque_norm(t_disque *disq)
{
	if ((disq->pdisque = (t_pdisque*)malloc(sizeof(*disq->pdisque))) == NULL)
		exit(-1);
	if ((disq->pos = (t_vec*)malloc(sizeof(*disq->pos))) == NULL)
		exit(-1);
	if ((disq->rot = (t_vec*)malloc(sizeof(*disq->rot))) == NULL)
		exit(-1);
	if ((disq->color = (t_vec*)malloc(sizeof(*disq->color))) == NULL)
		exit(-1);
}

void	rt_parser_objtype_spher_norm(t_spher *spher)
{
	if ((spher->pspher = (t_pspher*)malloc(sizeof(*spher->pspher))) == NULL)
		exit(-1);
	if ((spher->pos = (t_vec*)malloc(sizeof(*spher->pos))) == NULL)
		exit(-1);
	if ((spher->color = (t_vec*)malloc(sizeof(*spher->color))) == NULL)
		exit(-1);
}
