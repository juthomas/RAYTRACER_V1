/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parser_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juthomas <juthomas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/08 07:45:55 by juthomas          #+#    #+#             */
/*   Updated: 2018/04/08 08:29:01 by juthomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt.h"

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

int		rt_parser_stock_color_norm(int *tmp, t_vec *vec,
		unsigned int color, char *str)
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
