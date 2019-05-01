/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apion <apion@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/27 18:06:53 by apion             #+#    #+#             */
/*   Updated: 2019/05/01 13:30:55 by apion            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "libft.h"
#include "ft_printf.h"
#include "output.h"

void		print_output(t_env *env)
{
	print_lines(env->lines);
	ft_putchar('\n');
	print_matrix(env);
	ft_printf("length of shortest path start->end: %d\n", env->end->dst_min_to_start);
}
