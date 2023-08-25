/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjobert <rjobert@student.42barcelo>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 14:16:41 by rjobert           #+#    #+#             */
/*   Updated: 2023/08/21 14:16:48 by rjobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fractol.h"
void    fractal_setup(t_frame *frame, char **argv)
{
    t_fractal   *set;

    if (!argv[1] || argv[1][0] == '\0')
        fractol_exit(frame); // provide function for bad mem and not input isssue
    set = malloc(sizeof(t_fractal));
    if (!set)
        fractol_exit(frame); // provide function for bad mem and not input isssue
    if (ft_strncmp(argv[1], "Mandelbrot",10) == 0)
    {
        printf("THIS LINE OK\n");
        set->type = 1;
        printf("THIS LINE OK\n");
    }
    else if (ft_strncmp(argv[1], "Julia",5) == 0)
        set->type = 2;
    else
        fractol_exit(frame);
    if (set->type == 2)
    {   
        if (argv[3] && (ft_strncmp(argv[3], "1", 1) || ft_strncmp(argv[3], "2", 1)))
            set->julia_type = ft_atoi(argv[3]);
        else
            fractol_exit(frame);
    }
    frame->set = set;
    return ;
}

void fractol_exit(t_frame *frame)
{
    ft_putstr_fd("please enter the following argumant\n", STDOUT_FILENO);
    ft_putstr_fd("./fractol ['Mandelbrot','Julia']\n", STDOUT_FILENO);
    if (frame->img)
        free(frame->img);
    if (frame->set)
        free(frame->set);
    if (frame)
        free(frame);
    exit(0);
    //mlx_destroy_window(frame->mlx, frame->windw);
}

int main(int argc, char *argv[])
{
    t_frame  *frame;
    
    if (argc < 1 ||  !argv[0]) //useless but no compile with -W -W- W
        return (1);
    
    frame = init_graph(argv);
    complex_plan(frame);
    render_fractal(frame, 0);
    graphic_maganement(frame);
}