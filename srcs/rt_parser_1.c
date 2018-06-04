/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parser_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juthomas <juthomas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/08 07:49:14 by juthomas          #+#    #+#             */
/*   Updated: 2018/04/08 08:28:44 by juthomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt.h"

int		exit_error(int error)
{
	ft_putstr_fd("Parser :\n", 2);
	if (error == -1)
		ft_putstr_fd("Erreur avec les nombres\n", 2);
	else if (error == -2)
		ft_putstr_fd("Erreur avec l'orthographe des parametres\n", 2);
	else if (error == -3)
		ft_putstr_fd("Erreur d'argument\nEssaye avec <./rtv2 \"map\">\n", 2);
	else if (error == -4)
		ft_putstr_fd("Erreur de balise\n", 2);
	else if (error == -9)
		ft_putstr_fd("Erreur avec les nombres (Fov > 90)\n", 2);
	else
		ft_putstr_fd("Erreur non repertoriée\n", 2);
	return (error);
}

int		rt_parser_no_space(char *str, int i)
{
	while (str[i] != '\0' && (str[i] == ' ' || str[i] == '\t'))
		i++;
	return (i);
}

int		rt_parser_balise_name(char *str, int i, int *state)
{
	if (ft_strncmp(&str[i], "SCN", 3) == 0)
		*state = 4;
	else if (ft_strncmp(&str[i], "/", 1) == 0)
		*state = 0;
	else if (ft_strncmp(&str[i], "camera(s)", 9) == 0)
		*state = 1;
	else if (ft_strncmp(&str[i], "lightspot(s)", 12) == 0)
		*state = 2;
	else if (ft_strncmp(&str[i], "objet(s)", 8) == 0)
		*state = 3;
	else
		*state = -1;
	while (str[i] != '>' && str[i] != '\0')
		i++;
	return (i);
}

int		rt_parser_go_next_number(char *str, int i)
{
	int		tmp;

	tmp = i;
	while (((str[tmp] >= '0' && str[tmp] <= '9') || str[tmp] == '.'
				|| str[tmp] == '-'))
		tmp++;
	if (str[tmp] != ' ' && str[tmp] != '	' && str[tmp] != '}' && tmp == i)
		return (-1);
	while (str[tmp] == ' ' || str[tmp] == '	')
		tmp++;
	if (!((str[i] >= '0' && str[i] <= '9') || str[i] == '-' || str[i] == '}'))
		return (-1);
	return (tmp);
}

int		rt_parser_stock_vec(char *str, t_vec *vec, int *nb, int dec)
{
	int		i;
	int		nu_of_params;

	nu_of_params = 0;
	i = *nb + dec;
	while (str[i] == ' ' || str[i] == '	')
		i++;
	while (str[i] != '\0' && ((str[i] >= '0' && str[i] <= '9') || str[i] == '.'
				|| str[i] == ' ' || str[i] == '	' || str[i] == '-'))
	{
		if (nu_of_params == 0)
			vec->x = ft_adolphe(&str[i]);
		else if (nu_of_params == 1)
			vec->y = ft_adolphe(&str[i]);
		else if (nu_of_params == 2)
			vec->z = ft_adolphe(&str[i]);
		if ((i = rt_parser_go_next_number(str, i)) == -1)
			exit(exit_error(-1));
		nu_of_params++;
	}
	*nb = i + 1;
	if (str[i] != '}' || nu_of_params != 3)
		return (-1);
	return (0);
}
