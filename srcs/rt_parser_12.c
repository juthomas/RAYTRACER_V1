/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parser_12.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juthomas <juthomas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/10 02:28:25 by juthomas          #+#    #+#             */
/*   Updated: 2018/04/10 02:28:38 by juthomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt.h"

void	rt_parser_check_var_max(float *var, float max)
{
	if (*var < 0)
		*var = 0;
	else if (*var > max)
		*var = max;
}
