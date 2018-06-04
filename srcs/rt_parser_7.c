/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parser_7.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juthomas <juthomas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/08 07:55:08 by juthomas          #+#    #+#             */
/*   Updated: 2018/04/10 02:17:31 by juthomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt.h"

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

char	rt_parser_objtype_triangle(char *str, void **addr, char type)
{
	int			i;
	int			state;
	t_triangle	*triangle;

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
	rt_parser_check_var_max(&triangle->pbas->refl, 1);
	rt_parser_check_var_max(&triangle->pbas->opac, 1);
	*addr = triangle;
	return (type);
}

char	rt_parser_objtype_cycon(char *str, void **addr, char type)
{
	int			i;
	int			state;
	t_cycon		*cycon;

	state = 0;
	i = 0;
	if ((cycon = (t_cycon*)malloc(sizeof(*cycon))) == NULL)
		exit(-1);
	rt_parser_objtype_cycon_norm(cycon);
	rt_parser_objtype_cycon_setup(cycon);
	while (str[i] != '\0' && state == 0)
	{
		i = rt_parser_no_space(str, i);
		if (str[i] != '\0' && ((state = stock_cycon(cycon, str, &i)) < 0))
			exit(exit_error(state));
	}
	check_vec_dir(cycon->rot);
	rt_parser_check_var_max(&cycon->pc->refl, 1);
	rt_parser_check_var_max(&cycon->pc->opac, 1);
	rt_parser_check_var_max(&cycon->pc->height, 1000);
	rt_parser_check_var_max(&cycon->pc->radius, 1000);
	*addr = cycon;
	return (type);
}

char	rt_parser_objtype_plan(char *str, void **addr, char type)
{
	int			i;
	int			state;
	t_plan		*plan;

	state = 0;
	i = 0;
	if ((plan = (t_plan*)malloc(sizeof(*plan))) == NULL)
		exit(-1);
	rt_parser_objtype_plan_norm(plan);
	rt_parser_objtype_plan_setup(plan);
	while (str[i] != '\0' && state == 0)
	{
		i = rt_parser_no_space(str, i);
		if (str[i] != '\0' && ((state = stock_plan(plan, str, &i)) < 0))
			exit(exit_error(state));
	}
	check_vec_dir(plan->rot);
	rt_parser_check_var_max(&plan->pbasic->refl, 1);
	rt_parser_check_var_max(&plan->pbasic->opac, 1);
	*addr = plan;
	return (type);
}

char	rt_parser_objtype_disque(char *str, void **addr, char type)
{
	int			i;
	int			state;
	t_disque	*disq;

	state = 0;
	i = 0;
	if ((disq = (t_disque*)malloc(sizeof(*disq))) == NULL)
		exit(-1);
	rt_parser_objtype_disque_norm(disq);
	rt_parser_objtype_disque_setup(disq);
	while (str[i] != '\0' && state == 0)
	{
		i = rt_parser_no_space(str, i);
		if (str[i] != '\0' && ((state = stock_disque(disq, str, &i)) < 0))
			exit(exit_error(state));
	}
	check_vec_dir(disq->rot);
	rt_parser_check_var_max(&disq->pdisque->refl, 1);
	rt_parser_check_var_max(&disq->pdisque->opac, 1);
	rt_parser_check_var_max(&disq->pdisque->radius, 1000);
	*addr = disq;
	return (type);
}
