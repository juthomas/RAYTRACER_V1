/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parser_9.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juthomas <juthomas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/08 07:55:54 by juthomas          #+#    #+#             */
/*   Updated: 2018/04/08 23:59:36 by juthomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt.h"

t_cam	*rt_parser_camera_done(char *str, char type)
{
	t_cam	*cam;

	if ((cam = (t_cam*)malloc(sizeof(*cam))) == NULL)
		exit(-1);
	if (type == 'V')
		rt_parser_objtype_camera(&str[9], cam);
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
