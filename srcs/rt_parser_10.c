/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parser_10.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juthomas <juthomas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/08 07:56:14 by juthomas          #+#    #+#             */
/*   Updated: 2018/04/09 01:13:59 by juthomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt.h"

void	rt_parser_main_setup(int argc, char **argv,
		t_parser *parser, t_win *win)
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

void	rt_parser_main_while(t_parser *parser, t_win *win)
{
	parser->i = 0;
	parser->i = rt_parser_no_space(parser->line, parser->i);
	if ((parser->state = rt_parser_state(parser->line, parser->state,
					parser->i)) == -1)
		exit(exit_error(-4));
	if (ft_strncmp(&parser->line[parser->i], "window:{", 8) == 0
			|| ft_strncmp(&parser->line[parser->i], "window:{", 8) == 0)
		rt_parser_stock_win(&parser->line[parser->i + 8], win);
}

t_list	*rt_parser_main(int argc, char **argv, t_cam **cam, t_win *win)
{
	t_parser	*parser;
	t_list		*list;

	if ((parser = (t_parser*)malloc(sizeof(t_parser))) == NULL)
		exit(-1);
	rt_parser_main_setup(argc, argv, parser, win);
	list = ft_lstnew(0, 0);
	while (get_next_line(parser->fd, &parser->line) == 1)
	{
		rt_parser_main_while(parser, win);
		if ((parser->state == 1) && ((parser->obj_name =
						rt_parser_camera(&parser->line[parser->i])) != 0))
			*cam = rt_parser_camera_done(&parser->line[parser->i],
					parser->obj_name);
		else if ((parser->state == 2) && ((parser->obj_name =
						rt_parser_objtype(&parser->line[parser->i])) != 0))
			ft_lstadd(&list, ft_lstnew2(rt_parser_lobjtype_done(
	&parser->line[parser->i], parser->obj_name), sizeof(t_type), &parser->vo));
		else if ((parser->state == 3) && ((parser->obj_name =
						rt_parser_objtype(&parser->line[parser->i])) != 0))
			ft_lstadd(&list, ft_lstnew2(rt_parser_objtype_done(
	&parser->line[parser->i], parser->obj_name), sizeof(t_type), &parser->vo));
		free(parser->line);
	}
	return (rt_parser_main_end(parser, list, win));
}
