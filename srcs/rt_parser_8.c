/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parser_8.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juthomas <juthomas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/08 07:55:28 by juthomas          #+#    #+#             */
/*   Updated: 2018/04/10 02:21:11 by juthomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt.h"

char	rt_parser_objtype_spher(char *str, void **addr, char type)
{
	int			i;
	int			state;
	t_spher		*spher;

	state = 0;
	i = 0;
	if ((spher = (t_spher*)malloc(sizeof(*spher))) == NULL)
		exit(-1);
	rt_parser_objtype_spher_norm(spher);
	rt_parser_objtype_spher_setup(spher);
	while (str[i] != '\0' && state == 0)
	{
		i = rt_parser_no_space(str, i);
		if (str[i] != '\0' && ((state = stock_spher(spher, str, &i)) < 0))
			exit(exit_error(state));
	}
	rt_parser_check_var_max(&spher->pspher->refl, 1);
	rt_parser_check_var_max(&spher->pspher->opac, 1);
	rt_parser_check_var_max(&spher->pspher->radius, 1000);
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
	t_type		*typ;
	t_lspher	*spher;
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
