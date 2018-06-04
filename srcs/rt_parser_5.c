/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parser_5.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juthomas <juthomas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/08 07:47:10 by juthomas          #+#    #+#             */
/*   Updated: 2018/04/10 02:23:48 by juthomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt.h"

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
	int			i;
	int			state;
	t_lspher	*spher;

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
	rt_parser_check_var_max(&spher->lpspher->emi, 3.8);
	*addr = spher;
	return (type);
}

void	rt_parser_objtype_camera(char *str, t_cam *cam)
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
	int			i;
	int			state;
	t_lproj		*proj;

	state = 0;
	i = 0;
	if ((proj = (t_lproj*)malloc(sizeof(*proj))) == NULL)
		exit(-1);
	rt_parser_objtype_lproj_norm(proj);
	rt_parser_objtype_lproj_setup(proj);
	while (str[i] != '\0' && state == 0)
	{
		i = rt_parser_no_space(str, i);
		if (str[i] != '\0' && ((state = stock_lproj(proj, str, &i)) < 0))
			exit(exit_error(state));
	}
	check_vec_dir(proj->dir);
	rt_parser_check_var_max(&proj->lpproj->emi, 3.8);
	*addr = proj;
	return (type);
}
