/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic_management.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjobert <rjobert@student.42barcelo>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 17:27:28 by rjobert           #+#    #+#             */
/*   Updated: 2023/08/21 17:27:31 by rjobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fractol.h"

t_vars  *init_graph(char *s)
{
    t_data  img;
    t_vars  *frame;
    void    *mlx;
    void    *windw;

    frame = malloc(sizeof(t_vars));
    if (!frame)
        return (NULL);
    mlx = mlx_init();
    if (!mlx)
        return (NULL);
    frame->width = 1920;
    frame->height = 1080;
    windw = mlx_new_window(mlx, frame->width, frame->height, s);
    if (!windw)
        return (NULL);
    img.image = mlx_new_image(mlx, frame->width, frame->height);
    img.addr = mlx_get_data_addr(img.image, &img.bits_per_pxl, &img.line_len, &img.endian);
    frame->mlx = mlx;
    frame->windw = windw;
    frame->data = &img;
    return (frame);
}

void   graphic_maganement(t_vars *vars)
{
    mlx_hook(vars->windw, 2, 0, esc_handler, vars);
    mlx_hook(vars->windw, 17, 0, close_handler, vars);
    mlx_loop(vars->mlx);
}

int  esc_handler(int keycode, t_vars *vars)
{
    if (keycode == 53)
    {
        mlx_destroy_window(vars->mlx, vars->windw);
        exit (0);
    }
    else
        return (1);
}

int close_handler(t_vars *vars)
{
    mlx_destroy_window(vars->mlx, vars->windw);
    exit (0);
}
