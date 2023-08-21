/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot_set.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjobert <rjobert@student.42barcelo>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 18:37:46 by rjobert           #+#    #+#             */
/*   Updated: 2023/08/21 18:37:48 by rjobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../include/fractol.h"

void    cartesian_mapping(t_vars *frame)
{       
    t_mdbrt *set = malloc(sizeof(t_mdbrt));
    if (!set)
        return ; //exit wrapping function here LATER ON
    
    set->MaxReal = 1;
    set->MinReal = -3;
    set->MinIm = -1;
    set->MaxIm = set->MinIm + (set->MaxReal - set->MinReal) * (frame->height / frame->width);
    frame->m_set = set;
}

